/* SPDX-License-Identifier: CC0-1.0
 * rg_fs: native host file service.  See rg_fs.h and docs/NATIVE-FS.md.
 * Written from scratch; no third-party code. */
#include "rg_fs.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
typedef SRWLOCK fs_mutex;
typedef CONDITION_VARIABLE fs_cond;
#define MU_INIT(m) InitializeSRWLock(m)
#define MU_LOCK(m) AcquireSRWLockExclusive(m)
#define MU_UNLOCK(m) ReleaseSRWLockExclusive(m)
#define CV_INIT(c) InitializeConditionVariable(c)
#define CV_WAIT(c, m) SleepConditionVariableSRW(c, m, INFINITE, 0)
#define CV_BCAST(c) WakeAllConditionVariable(c)
typedef HANDLE fs_thread;
#else
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
typedef pthread_mutex_t fs_mutex;
typedef pthread_cond_t fs_cond;
#define MU_INIT(m) pthread_mutex_init(m, NULL)
#define MU_LOCK(m) pthread_mutex_lock(m)
#define MU_UNLOCK(m) pthread_mutex_unlock(m)
#define CV_INIT(c) pthread_cond_init(c, NULL)
#define CV_WAIT(c, m) pthread_cond_wait(c, m)
#define CV_BCAST(c) pthread_cond_broadcast(c)
typedef pthread_t fs_thread;
#endif

#define FS_MAX_HOOKS 4
#define FS_MAX_REQ 256
#define FS_PATH 1024

typedef struct fs_ent {
    char *rel;    /* indexed path as on disc: "BIN/NORMAL.BIN" */
    char *key;    /* canonical upper-case key */
    char *host;   /* host path */
    int64_t size;
#ifdef _WIN32
    HANDLE fh;    /* INVALID_HANDLE_VALUE until first read */
#else
    int fd;       /* -1 until first read */
#endif
} fs_ent;

enum { RQ_FREE = 0, RQ_QUEUED, RQ_RUNNING, RQ_DONE };
typedef struct fs_req {
    int state, id, h;
    int64_t off, len, result;
    void *buf;
    rg_fs_done_fn cb;
    void *user;
    uint64_t seq;  /* FIFO order */
} fs_req;

static struct {
    int init;
    fs_mutex mu;      /* index, handles, stats, hooks */
    fs_mutex qmu;     /* request table */
    fs_cond qcv;
    int mounted;
    char root[FS_PATH];
    fs_ent *e;
    int n, cap;
    int *tab;         /* open-addressing hash of key -> index+1 */
    int tabn;
    struct { rg_fs_read_hook fn; void *user; } hooks[FS_MAX_HOOKS];
    rg_fs_stats st;
    fs_req req[FS_MAX_REQ];
    int next_id;
    uint64_t next_seq;
    int worker_on, worker_stop;
    fs_thread worker;
} F;

static void fs_init_once(void)
{
    /* first use is on the runtime's (single) init thread */
    if (F.init)
        return;
    MU_INIT(&F.mu);
    MU_INIT(&F.qmu);
    CV_INIT(&F.qcv);
    F.next_id = 1;
    F.init = 1;
}

static uint64_t now_ns(void)
{
#ifdef _WIN32
    static LARGE_INTEGER f;
    LARGE_INTEGER c;
    if (!f.QuadPart)
        QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&c);
    return (uint64_t)((double)c.QuadPart * 1e9 / (double)f.QuadPart);
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
#endif
}

/* ---- names ---- */

char *rg_fs_canon(const char *name, char *out, size_t outlen)
{
    const char *p = name, *colon;
    size_t n = 0;
    if (!out || !outlen)
        return out;
    out[0] = 0;
    if (!name)
        return out;
    /* "cdrom0:\X", "cddat:X": drop the device (a ':' before any separator) */
    colon = strchr(p, ':');
    if (colon) {
        const char *s;
        for (s = p; s < colon && *s != '/' && *s != '\\'; s++)
            ;
        if (s == colon)
            p = colon + 1;
    }
    for (; *p && n + 1 < outlen; p++) {
        char c = *p == '\\' ? '/' : *p;
        if (c == '/' && (n == 0 || out[n - 1] == '/'))
            continue; /* leading or doubled separator */
        out[n++] = (char)toupper((unsigned char)c);
    }
    out[n] = 0;
    /* ";1" version suffix */
    {
        char *semi = strrchr(out, ';');
        if (semi) {
            char *d = semi + 1;
            while (*d >= '0' && *d <= '9')
                d++;
            if (!*d)
                *semi = 0;
        }
    }
    n = strlen(out);
    while (n && out[n - 1] == '/')
        out[--n] = 0;
    return out;
}

static uint32_t hash_key(const char *k)
{
    uint32_t h = 2166136261u;
    for (; *k; k++)
        h = (h ^ (uint8_t)*k) * 16777619u;
    return h;
}

static int find_locked(const char *key)
{
    uint32_t i;
    if (!F.tabn)
        return -1;
    for (i = hash_key(key) & (uint32_t)(F.tabn - 1);; i = (i + 1) & (uint32_t)(F.tabn - 1)) {
        int v = F.tab[i];
        if (!v)
            return -1;
        if (!strcmp(F.e[v - 1].key, key))
            return v - 1;
    }
}

static void rehash_locked(void)
{
    int i;
    free(F.tab);
    F.tabn = 64;
    while (F.tabn < F.n * 2 + 16)
        F.tabn <<= 1;
    F.tab = (int *)calloc((size_t)F.tabn, sizeof(int));
    for (i = 0; i < F.n; i++) {
        uint32_t j = hash_key(F.e[i].key) & (uint32_t)(F.tabn - 1);
        while (F.tab[j])
            j = (j + 1) & (uint32_t)(F.tabn - 1);
        F.tab[j] = i + 1;
    }
}

static char *xstrdup(const char *s)
{
    size_t n = strlen(s) + 1;
    char *d = (char *)malloc(n);
    if (d)
        memcpy(d, s, n);
    return d;
}

static void add_file(const char *rel, const char *host, int64_t size)
{
    char key[FS_PATH];
    fs_ent *x;
    rg_fs_canon(rel, key, sizeof key);
    if (F.n == F.cap) {
        int nc = F.cap ? F.cap * 2 : 256;
        fs_ent *ne = (fs_ent *)realloc(F.e, (size_t)nc * sizeof *ne);
        if (!ne)
            return;
        F.e = ne;
        F.cap = nc;
    }
    x = &F.e[F.n++];
    memset(x, 0, sizeof *x);
    x->rel = xstrdup(rel);
    x->key = xstrdup(key);
    x->host = xstrdup(host);
    x->size = size;
#ifdef _WIN32
    x->fh = INVALID_HANDLE_VALUE;
#else
    x->fd = -1;
#endif
}

static int skip_top(const char *rel_dir, const char *name, int is_dir)
{
    if (rel_dir[0])
        return 0;
    if (is_dir)
        return !strcmp(name, "converted");
    return !strcmp(name, "MANIFEST.tsv");
}

static void walk(const char *host_dir, const char *rel_dir, int depth)
{
    char hp[FS_PATH], rp[FS_PATH];
    if (depth > 16)
        return;
#ifdef _WIN32
    WIN32_FIND_DATAA fd;
    HANDLE fh;
    snprintf(hp, sizeof hp, "%s\\*", host_dir);
    fh = FindFirstFileA(hp, &fd);
    if (fh == INVALID_HANDLE_VALUE)
        return;
    do {
        int is_dir = (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        if (!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, ".."))
            continue;
        if (skip_top(rel_dir, fd.cFileName, is_dir))
            continue;
        snprintf(hp, sizeof hp, "%s\\%s", host_dir, fd.cFileName);
        snprintf(rp, sizeof rp, "%s%s%s", rel_dir, rel_dir[0] ? "/" : "", fd.cFileName);
        if (is_dir)
            walk(hp, rp, depth + 1);
        else
            add_file(rp, hp, (int64_t)(((uint64_t)fd.nFileSizeHigh << 32) | fd.nFileSizeLow));
    } while (FindNextFileA(fh, &fd));
    FindClose(fh);
#else
    DIR *d = opendir(host_dir);
    struct dirent *de;
    if (!d)
        return;
    while ((de = readdir(d)) != NULL) {
        struct stat sb;
        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            continue;
        snprintf(hp, sizeof hp, "%s/%s", host_dir, de->d_name);
        if (stat(hp, &sb) != 0)
            continue;
        if (skip_top(rel_dir, de->d_name, S_ISDIR(sb.st_mode)))
            continue;
        snprintf(rp, sizeof rp, "%s%s%s", rel_dir, rel_dir[0] ? "/" : "", de->d_name);
        if (S_ISDIR(sb.st_mode))
            walk(hp, rp, depth + 1);
        else if (S_ISREG(sb.st_mode))
            add_file(rp, hp, (int64_t)sb.st_size);
    }
    closedir(d);
#endif
}

static void close_all_locked(void)
{
    int i;
    for (i = 0; i < F.n; i++) {
#ifdef _WIN32
        if (F.e[i].fh != INVALID_HANDLE_VALUE)
            CloseHandle(F.e[i].fh);
#else
        if (F.e[i].fd >= 0)
            close(F.e[i].fd);
#endif
        free(F.e[i].rel);
        free(F.e[i].key);
        free(F.e[i].host);
    }
    free(F.e);
    free(F.tab);
    F.e = NULL;
    F.tab = NULL;
    F.n = F.cap = F.tabn = 0;
}

static void worker_stop(void);

int rg_fs_mount(const char *data_dir)
{
    fs_init_once();
    rg_fs_unmount();
    if (!data_dir || !*data_dir)
        return -1;
    MU_LOCK(&F.mu);
    snprintf(F.root, sizeof F.root, "%s", data_dir);
    {
        size_t n = strlen(F.root);
        while (n > 1 && (F.root[n - 1] == '/' || F.root[n - 1] == '\\'))
            F.root[--n] = 0;
    }
    walk(F.root, "", 0);
    if (F.n) {
        rehash_locked();
        F.mounted = 1;
    }
    F.st.files = (uint32_t)F.n;
    MU_UNLOCK(&F.mu);
    return F.n ? F.n : -1;
}

void rg_fs_unmount(void)
{
    fs_init_once();
    worker_stop();
    MU_LOCK(&F.mu);
    close_all_locked();
    F.mounted = 0;
    F.root[0] = 0;
    MU_UNLOCK(&F.mu);
}

int rg_fs_mounted(void) { return F.init && F.mounted; }
const char *rg_fs_root(void) { return F.root; }

int rg_fs_open(const char *name)
{
    char key[FS_PATH];
    int i;
    fs_init_once();
    rg_fs_canon(name, key, sizeof key);
    MU_LOCK(&F.mu);
    i = F.mounted ? find_locked(key) : -1;
    if (i >= 0)
        F.st.opens++;
    else
        F.st.open_misses++;
    MU_UNLOCK(&F.mu);
    return i;
}

int rg_fs_open_or_die(const char *name, const char *who)
{
    int h = rg_fs_open(name);
    if (h < 0) {
        fprintf(stderr, "%s: '%s' is not in the data folder '%s' (run rg-extract)\n",
                who ? who : "rg_fs", name ? name : "(null)", F.root);
        fflush(stderr);
        abort();
    }
    return h;
}

int64_t rg_fs_size(int h)
{
    if (!F.init || h < 0 || h >= F.n)
        return -1;
    return F.e[h].size;
}

const char *rg_fs_name(int h)
{
    if (!F.init || h < 0 || h >= F.n)
        return NULL;
    return F.e[h].rel;
}

/* ---- reads ---- */

/* the host file of h, opened on first use (under F.mu) */
static int host_open(int h)
{
    fs_ent *x = &F.e[h];
#ifdef _WIN32
    if (x->fh == INVALID_HANDLE_VALUE)
        x->fh = CreateFileA(x->host, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    return x->fh != INVALID_HANDLE_VALUE;
#else
    if (x->fd < 0)
        x->fd = open(x->host, O_RDONLY);
    return x->fd >= 0;
#endif
}

/* positional read; returns bytes read (short only at EOF) or -1 */
static int64_t host_pread(int h, int64_t off, void *buf, int64_t len)
{
    fs_ent *x = &F.e[h];
    int64_t done = 0;
    while (done < len) {
        int64_t want = len - done;
#ifdef _WIN32
        OVERLAPPED ov;
        DWORD got = 0;
        uint64_t o = (uint64_t)(off + done);
        if (want > 0x40000000)
            want = 0x40000000;
        memset(&ov, 0, sizeof ov);
        ov.Offset = (DWORD)o;
        ov.OffsetHigh = (DWORD)(o >> 32);
        if (!ReadFile(x->fh, (char *)buf + done, (DWORD)want, &got, &ov)) {
            if (GetLastError() == ERROR_HANDLE_EOF)
                break;
            return -1;
        }
#else
        ssize_t got;
        if (want > 0x40000000)
            want = 0x40000000;
        got = pread(x->fd, (char *)buf + done, (size_t)want, (off_t)(off + done));
        if (got < 0)
            return -1;
#endif
        if (got == 0)
            break;
        done += (int64_t)got;
    }
    return done;
}

/* the read itself, no hooks; buf fully written */
static int64_t do_read(int h, int64_t off, void *buf, int64_t len)
{
    int64_t want, got;
    uint64_t t0;
    int ok;
    if (!buf || len < 0)
        return -1;
    MU_LOCK(&F.mu);
    ok = F.mounted && h >= 0 && h < F.n && host_open(h);
    MU_UNLOCK(&F.mu);
    if (!ok || off < 0) {
        if (buf && len > 0)
            memset(buf, 0, (size_t)len);
        MU_LOCK(&F.mu);
        F.st.errors++;
        MU_UNLOCK(&F.mu);
        return -1;
    }
    t0 = now_ns();
    want = F.e[h].size - off;
    if (want < 0)
        want = 0;
    if (want > len)
        want = len;
    got = want ? host_pread(h, off, buf, want) : 0;
    if (got < 0) {
        memset(buf, 0, (size_t)len);
    } else if (got < len) {
        memset((char *)buf + got, 0, (size_t)(len - got));
    }
    MU_LOCK(&F.mu);
    F.st.reads++;
    F.st.read_ns += now_ns() - t0;
    if (got < 0)
        F.st.errors++;
    else
        F.st.bytes += (uint64_t)got;
    MU_UNLOCK(&F.mu);
    return got;
}

static void run_hooks(int h, int64_t off, int64_t len, int64_t got, const void *buf)
{
    int i;
    struct { rg_fs_read_hook fn; void *user; } hk[FS_MAX_HOOKS];
    MU_LOCK(&F.mu);
    memcpy(hk, F.hooks, sizeof hk);
    MU_UNLOCK(&F.mu);
    for (i = 0; i < FS_MAX_HOOKS; i++)
        if (hk[i].fn)
            hk[i].fn(hk[i].user, h, rg_fs_name(h), off, len, got, buf);
}

int64_t rg_fs_read_fill(int h, int64_t off, void *buf, int64_t len)
{
    int64_t got;
    fs_init_once();
    got = do_read(h, off, buf, len);
    run_hooks(h, off, len, got, buf);
    return got;
}

/* ---- async ---- */

#ifdef _WIN32
static DWORD WINAPI worker_main(LPVOID arg)
#else
static void *worker_main(void *arg)
#endif
{
    (void)arg;
    MU_LOCK(&F.qmu);
    for (;;) {
        fs_req *best = NULL;
        int i;
        if (F.worker_stop)
            break;
        for (i = 0; i < FS_MAX_REQ; i++)
            if (F.req[i].state == RQ_QUEUED && (!best || F.req[i].seq < best->seq))
                best = &F.req[i];
        if (!best) {
            CV_WAIT(&F.qcv, &F.qmu);
            continue;
        }
        best->state = RQ_RUNNING;
        MU_UNLOCK(&F.qmu);
        {
            int64_t r = do_read(best->h, best->off, best->buf, best->len);
            MU_LOCK(&F.qmu);
            best->result = r;
            best->state = RQ_DONE;
        }
        CV_BCAST(&F.qcv);
    }
    MU_UNLOCK(&F.qmu);
#ifdef _WIN32
    return 0;
#else
    return NULL;
#endif
}

static int worker_start_locked(void)
{
    if (F.worker_on)
        return 1;
    F.worker_stop = 0;
#ifdef _WIN32
    F.worker = CreateThread(NULL, 0, worker_main, NULL, 0, NULL);
    if (!F.worker)
        return 0;
#else
    if (pthread_create(&F.worker, NULL, worker_main, NULL) != 0)
        return 0;
#endif
    F.worker_on = 1;
    return 1;
}

static void worker_stop(void)
{
    int i;
    if (!F.worker_on)
        return;
    MU_LOCK(&F.qmu);
    /* finish what is running; drop what is queued */
    for (i = 0; i < FS_MAX_REQ; i++)
        if (F.req[i].state == RQ_QUEUED)
            F.req[i].state = RQ_FREE;
    F.worker_stop = 1;
    CV_BCAST(&F.qcv);
    MU_UNLOCK(&F.qmu);
#ifdef _WIN32
    WaitForSingleObject(F.worker, INFINITE);
    CloseHandle(F.worker);
#else
    pthread_join(F.worker, NULL);
#endif
    MU_LOCK(&F.qmu);
    F.worker_on = 0;
    memset(F.req, 0, sizeof F.req);
    MU_UNLOCK(&F.qmu);
}

int rg_fs_read_async(int h, int64_t off, void *buf, int64_t len, rg_fs_done_fn cb, void *user)
{
    int i, id = -1;
    fs_init_once();
    if (!F.mounted || h < 0 || h >= F.n || !buf || len < 0 || off < 0)
        return -1;
    MU_LOCK(&F.qmu);
    if (worker_start_locked()) {
        for (i = 0; i < FS_MAX_REQ; i++) {
            if (F.req[i].state == RQ_FREE) {
                fs_req *r = &F.req[i];
                id = F.next_id;
                F.next_id = F.next_id >= 0x7FFFFFFF ? 1 : F.next_id + 1;
                r->id = id;
                r->h = h;
                r->off = off;
                r->len = len;
                r->buf = buf;
                r->cb = cb;
                r->user = user;
                r->result = 0;
                r->seq = F.next_seq++;
                r->state = RQ_QUEUED;
                break;
            }
        }
    }
    if (id > 0)
        CV_BCAST(&F.qcv);
    MU_UNLOCK(&F.qmu);
    if (id > 0) {
        MU_LOCK(&F.mu);
        F.st.async_reads++;
        MU_UNLOCK(&F.mu);
    }
    return id;
}

static fs_req *find_req_locked(int id)
{
    int i;
    if (id <= 0)
        return NULL;
    for (i = 0; i < FS_MAX_REQ; i++)
        if (F.req[i].state != RQ_FREE && F.req[i].id == id)
            return &F.req[i];
    return NULL;
}

/* called with qmu held on a DONE request: release it, then deliver unlocked */
static int64_t deliver(fs_req *r)
{
    fs_req c = *r;
    memset(r, 0, sizeof *r);
    MU_UNLOCK(&F.qmu);
    run_hooks(c.h, c.off, c.len, c.result, c.buf);
    if (c.cb)
        c.cb(c.user, c.id, c.result);
    MU_LOCK(&F.qmu);
    return c.result;
}

int rg_fs_poll(int req, int64_t *result)
{
    fs_req *r;
    int ret;
    fs_init_once();
    MU_LOCK(&F.qmu);
    r = find_req_locked(req);
    if (!r) {
        ret = -1;
    } else if (r->state != RQ_DONE) {
        ret = 0;
    } else {
        int64_t v = deliver(r);
        if (result)
            *result = v;
        ret = 1;
    }
    MU_UNLOCK(&F.qmu);
    return ret;
}

int64_t rg_fs_wait(int req)
{
    fs_req *r;
    int64_t v = -1;
    fs_init_once();
    MU_LOCK(&F.qmu);
    while ((r = find_req_locked(req)) != NULL && r->state != RQ_DONE)
        CV_WAIT(&F.qcv, &F.qmu);
    if (r)
        v = deliver(r);
    MU_UNLOCK(&F.qmu);
    return v;
}

int rg_fs_pump(void)
{
    int n = 0;
    fs_init_once();
    MU_LOCK(&F.qmu);
    for (;;) {
        fs_req *best = NULL;
        int i;
        for (i = 0; i < FS_MAX_REQ; i++)
            if (F.req[i].state == RQ_DONE && (!best || F.req[i].seq < best->seq))
                best = &F.req[i];
        if (!best)
            break;
        deliver(best);
        n++;
    }
    MU_UNLOCK(&F.qmu);
    return n;
}

int rg_fs_pending(void)
{
    int i, n = 0;
    fs_init_once();
    MU_LOCK(&F.qmu);
    for (i = 0; i < FS_MAX_REQ; i++)
        n += F.req[i].state == RQ_QUEUED || F.req[i].state == RQ_RUNNING;
    MU_UNLOCK(&F.qmu);
    return n;
}

/* ---- observers, stats ---- */

int rg_fs_add_read_hook(rg_fs_read_hook fn, void *user)
{
    int i, ok = -1;
    fs_init_once();
    MU_LOCK(&F.mu);
    for (i = 0; i < FS_MAX_HOOKS; i++) {
        if (!F.hooks[i].fn) {
            F.hooks[i].fn = fn;
            F.hooks[i].user = user;
            ok = 0;
            break;
        }
    }
    MU_UNLOCK(&F.mu);
    return ok;
}

void rg_fs_remove_read_hook(rg_fs_read_hook fn, void *user)
{
    int i;
    fs_init_once();
    MU_LOCK(&F.mu);
    for (i = 0; i < FS_MAX_HOOKS; i++)
        if (F.hooks[i].fn == fn && F.hooks[i].user == user)
            F.hooks[i].fn = NULL, F.hooks[i].user = NULL;
    MU_UNLOCK(&F.mu);
}

void rg_fs_get_stats(rg_fs_stats *out)
{
    fs_init_once();
    MU_LOCK(&F.mu);
    *out = F.st;
    MU_UNLOCK(&F.mu);
}
