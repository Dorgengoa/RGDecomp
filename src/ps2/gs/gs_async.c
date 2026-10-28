/* SPDX-License-Identifier: CC0-1.0 */
/* Asynchronous GS (docs/PERF-3D.md "GS worker thread").
 *
 * With gs_async_start the GIF input (gs_gif_write, gs_gif_reset) is copied
 * into a single-producer ring and executed in order by a worker thread: the
 * GS model and the renderer hooks (src/gpu) then run beside the EE / VIF /
 * VU1 work that produces the packets.  Everything the EE side can observe
 * stays exactly as in the synchronous model:
 *
 *   - CSR, IMR and the other privileged registers are written and read on
 *     the calling thread.  The worker never touches them, because the only
 *     GIF writes that do (SIGNAL, FINISH, LABEL: events, SIGLBLID) are found
 *     by a scan of each packet as it is queued (a per-path GIFtag walk, PACKED
 *     A+D descriptors); such a packet drains the ring and runs synchronously.
 *   - Whatever reads state the worker owns waits for the ring to drain first:
 *     gs_read_fifo (local->host data), gs_path_idle, gs_read_display, a CSR
 *     write (RESET), the recorder, and the program before it touches the
 *     renderer or vram (gs_async_drain).
 *
 * The worker executes the same calls in the same order as the synchronous
 * model, so the GS state, vram and every renderer call are identical. */
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "gs_internal.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
typedef SRWLOCK gsa_mutex;
typedef CONDITION_VARIABLE gsa_cond;
#define MTX_INIT(m) InitializeSRWLock(m)
#define MTX_LOCK(m) AcquireSRWLockExclusive(m)
#define MTX_UNLOCK(m) ReleaseSRWLockExclusive(m)
#define COND_INIT(c) InitializeConditionVariable(c)
#define COND_WAIT(c, m) SleepConditionVariableSRW(c, m, INFINITE, 0)
#define COND_SIGNAL(c) WakeAllConditionVariable(c)
#else
#include <pthread.h>
typedef pthread_mutex_t gsa_mutex;
typedef pthread_cond_t gsa_cond;
#define MTX_INIT(m) pthread_mutex_init(m, NULL)
#define MTX_LOCK(m) pthread_mutex_lock(m)
#define MTX_UNLOCK(m) pthread_mutex_unlock(m)
#define COND_INIT(c) pthread_cond_init(c, NULL)
#define COND_WAIT(c, m) pthread_cond_wait(c, m)
#define COND_SIGNAL(c) pthread_cond_broadcast(c)
#endif

enum { GSA_RING = 64u << 20, GSA_CHUNK = 4u << 20 };
enum { GSA_GIF = 1, GSA_RESET = 2, GSA_PAD = 3, GSA_CALL = 4 };

/* GSA_CALL payload: the function, its user pointer, then the data */
typedef struct gsa_call {
    gs_async_fn fn;
    void *user;
    uint64_t pad;
} gsa_call;

typedef struct gsa_hdr {
    uint32_t kind, path, bytes, pad;   /* bytes of payload after the header */
} gsa_hdr;

/* producer-side GIFtag walk of one path (what gif_qword does, without
 * executing anything) */
typedef struct gsa_scan {
    int in_tag;
    uint32_t nloop, nreg, flg, reg_i;
    uint64_t regs;
} gsa_scan;

struct gs_async {
    gs_state *gs;
    uint8_t *ring;
    /* head: bytes written by the producer, tail: bytes executed by the
     * worker (both only grow; positions are mod GSA_RING).  The tail moves
     * after an entry has run, so tail == head means everything ran. */
    /* 8-aligned: the 64-bit atomics stay lock-free on i686 (the i386 ABI aligns uint64_t
     * members to 4, which makes GCC call libatomic on Linux) */
    _Alignas(8) volatile uint64_t head;
    _Alignas(8) volatile uint64_t tail;
    volatile int worker_sleeping, producer_waiting;
    /* SIGNAL / FINISH / LABEL writes queued since the last drain: CSR and
     * SIGLBLID reads must wait for them (gs__async_events_settle) */
    int ev_pending;
    int stop;
    gsa_mutex m;
    gsa_cond c_work, c_space;
    gsa_scan scan[4];
#ifdef _WIN32
    HANDLE th;
#else
    pthread_t th;
#endif
    uint64_t entries, bytes, drains, sync_packets;
    double wait_ms;            /* time the caller spent waiting for the worker */
};

static double gsa_now_ms(void)
{
#ifdef _WIN32
    static LARGE_INTEGER f;
    LARGE_INTEGER c;
    if (!f.QuadPart) QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart * 1000.0 / (double)f.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1.0e6;
#endif
}

/* the pointee type carries the 8 alignment too: clang picks inline vs libatomic from the
 * pointer's type, not the field (i386 SysV: plain uint64_t is 4-aligned -> __atomic_load /
 * __atomic_store calls, undefined without libatomic; docs/LINUX.md) */
typedef volatile uint64_t gsa_u64 __attribute__((aligned(8)));
static uint64_t ld64(gsa_u64 *p) { return __atomic_load_n(p, __ATOMIC_SEQ_CST); }
static void st64(gsa_u64 *p, uint64_t v) { __atomic_store_n(p, v, __ATOMIC_SEQ_CST); }
static int ldi(volatile int *p) { return __atomic_load_n(p, __ATOMIC_SEQ_CST); }
static void sti(volatile int *p, int v) { __atomic_store_n(p, v, __ATOMIC_SEQ_CST); }

/* wake the producer if it waits for space or for the drain */
static void wake_producer(gs_async *a)
{
    if (ldi(&a->producer_waiting)) {
        MTX_LOCK(&a->m);
        COND_SIGNAL(&a->c_space);
        MTX_UNLOCK(&a->m);
    }
}

static void wake_worker(gs_async *a)
{
    if (ldi(&a->worker_sleeping)) {
        MTX_LOCK(&a->m);
        COND_SIGNAL(&a->c_work);
        MTX_UNLOCK(&a->m);
    }
}

/* the producer waits until cond() holds (the worker wakes it as the tail moves) */
static void producer_wait_tail(gs_async *a, uint64_t want_tail_at_least)
{
    if (ld64(&a->tail) >= want_tail_at_least) return;
    MTX_LOCK(&a->m);
    sti(&a->producer_waiting, 1);
    while (ld64(&a->tail) < want_tail_at_least) COND_WAIT(&a->c_space, &a->m);
    sti(&a->producer_waiting, 0);
    MTX_UNLOCK(&a->m);
}

#ifdef _WIN32
static DWORD WINAPI worker(LPVOID arg)
#else
static void *worker(void *arg)
#endif
{
    gs_async *a = (gs_async *)arg;
    uint64_t t = ld64(&a->tail), since = 0;
    for (;;) {
        uint64_t h = ld64(&a->head);
        if (h == t) {
            MTX_LOCK(&a->m);
            sti(&a->worker_sleeping, 1);
            while ((h = ld64(&a->head)) == t && !a->stop) COND_WAIT(&a->c_work, &a->m);
            sti(&a->worker_sleeping, 0);
            int done = h == t && a->stop;
            MTX_UNLOCK(&a->m);
            if (done) break;
        }
        while (t != h) {
            gsa_hdr *e = (gsa_hdr *)(a->ring + (t % GSA_RING));
            if (e->kind == GSA_GIF) gs__gif_write_now(a->gs, (int)e->path, e + 1, e->bytes / 16u);
            else if (e->kind == GSA_RESET) gs__gif_reset_now(a->gs);
            else if (e->kind == GSA_CALL) {
                const gsa_call *c = (const gsa_call *)(e + 1);
                c->fn(c->user, a->gs, c + 1);
            }
            t += sizeof(gsa_hdr) + e->bytes;
            /* publish progress now and then (and at the end) so the producer
             * can refill the space */
            since += sizeof(gsa_hdr) + e->bytes;
            if (since >= (256u << 10)) {
                st64(&a->tail, t);
                since = 0;
                wake_producer(a);
            }
        }
        st64(&a->tail, t);
        since = 0;
        wake_producer(a);
    }
#ifdef _WIN32
    return 0;
#else
    return NULL;
#endif
}

int gs_async_start(gs_state *gs)
{
    if (!gs || gs->async) return 0;
    gs_async *a = (gs_async *)calloc(1, sizeof *a);
    if (!a) return -1;
    a->ring = (uint8_t *)malloc(GSA_RING);
    if (!a->ring) { free(a); return -1; }
    a->gs = gs;
    MTX_INIT(&a->m);
    COND_INIT(&a->c_work);
    COND_INIT(&a->c_space);
#ifdef _WIN32
    a->th = CreateThread(NULL, 1u << 20, worker, a, 0, NULL);
    if (!a->th) { free(a->ring); free(a); return -1; }
#else
    if (pthread_create(&a->th, NULL, worker, a) != 0) { free(a->ring); free(a); return -1; }
#endif
    /* the scan starts from the paths' current state */
    for (int p = 1; p <= 3; p++) {
        const gs_gif_path *g = &gs->path[p];
        a->scan[p].in_tag = g->in_tag;
        a->scan[p].nloop = g->nloop;
        a->scan[p].nreg = g->nreg;
        a->scan[p].flg = g->flg;
        a->scan[p].reg_i = g->reg_i;
        a->scan[p].regs = g->regs;
    }
    gs->async = a;
    return 0;
}

void gs_async_drain(gs_state *gs)
{
    gs_async *a = gs ? gs->async : NULL;
    if (!a) return;
    uint64_t h = ld64(&a->head);
    if (ld64(&a->tail) != h) {
        a->drains++;
        double t0 = gsa_now_ms();
        producer_wait_tail(a, h);
        a->wait_ms += gsa_now_ms() - t0;
    }
    a->ev_pending = 0;
}

/* before a read of CSR / SIGLBLID or a write of IMR: the queued event
 * writes must have run */
void gs__async_events_settle(gs_state *gs)
{
    if (gs->async && gs->async->ev_pending) gs_async_drain(gs);
}

void gs_async_stop(gs_state *gs)
{
    gs_async *a = gs ? gs->async : NULL;
    if (!a) return;
    gs_async_drain(gs);
    MTX_LOCK(&a->m);
    a->stop = 1;
    COND_SIGNAL(&a->c_work);
    MTX_UNLOCK(&a->m);
#ifdef _WIN32
    WaitForSingleObject(a->th, INFINITE);
    CloseHandle(a->th);
#else
    pthread_join(a->th, NULL);
#endif
    gs->async = NULL;
    free(a->ring);
    free(a);
}

int gs_async_on(const gs_state *gs) { return gs && gs->async; }

double gs_async_wait_ms(const gs_state *gs) { return gs && gs->async ? gs->async->wait_ms : 0.0; }

void gs_async_stats(const gs_state *gs, uint64_t out[4])
{
    const gs_async *a = gs ? gs->async : NULL;
    out[0] = a ? a->entries : 0;
    out[1] = a ? a->bytes : 0;
    out[2] = a ? a->drains : 0;
    out[3] = a ? a->sync_packets : 0;
}

/* Does this data (the next qwords of path p's stream) write SIGNAL, FINISH
 * or LABEL?  Advances the path's scan state either way. */
static int scan_events(gsa_scan *s, const uint8_t *q, uint32_t nqw)
{
    int hit = 0;
    uint32_t i = 0;
    while (i < nqw) {
        const uint8_t *w = q + 16u * i;
        if (!s->in_tag) {
            uint64_t lo, hi;
            memcpy(&lo, w, 8);
            memcpy(&hi, w + 8, 8);
            s->nloop = (uint32_t)(lo & 0x7FFF);
            s->flg = (uint32_t)((lo >> 58) & 3);
            s->nreg = (uint32_t)((lo >> 60) & 15);
            if (s->nreg == 0) s->nreg = 16;
            s->regs = hi;
            s->reg_i = 0;
            s->in_tag = 1;
            i++;
        } else if (s->flg >= 2) {
            /* IMAGE: nloop qwords of data */
            uint32_t k = nqw - i < s->nloop ? nqw - i : s->nloop;
            s->nloop -= k;
            i += k;
        } else if (s->flg == 0) {
            /* PACKED: one descriptor per qword; only A+D can address SIGNAL,
             * FINISH and LABEL */
            if (((s->regs >> (4 * s->reg_i)) & 15u) == 0xE) {
                uint8_t addr = w[8];
                if (addr >= 0x60 && addr <= 0x62) hit |= 1 << (addr - 0x60);
            }
            if (++s->reg_i == s->nreg) { s->reg_i = 0; s->nloop--; }
            i++;
        } else {
            /* REGLIST: two descriptors per qword, A+D is a no-op there */
            for (int h = 0; h < 2 && s->nloop; h++)
                if (++s->reg_i == s->nreg) { s->reg_i = 0; s->nloop--; }
            i++;
        }
        if (s->in_tag && s->nloop == 0) s->in_tag = 0;
    }
    return hit;
}

static void push(gs_async *a, uint32_t kind, uint32_t path, const void *data, uint32_t bytes)
{
    uint32_t need = (uint32_t)sizeof(gsa_hdr) + bytes;
    uint64_t h = ld64(&a->head);
    /* an entry never wraps: pad to the ring's end first */
    uint32_t pos = (uint32_t)(h % GSA_RING);
    if (pos + need > GSA_RING) {
        uint32_t pad = GSA_RING - pos;
        if (h + pad > GSA_RING) producer_wait_tail(a, h + pad - GSA_RING);
        gsa_hdr *e = (gsa_hdr *)(a->ring + pos);
        e->kind = GSA_PAD;
        e->path = 0;
        e->bytes = pad - (uint32_t)sizeof(gsa_hdr);
        h += pad;
        st64(&a->head, h);
        wake_worker(a);
        pos = 0;
    }
    if (h + need > GSA_RING) producer_wait_tail(a, h + need - GSA_RING);
    gsa_hdr *e = (gsa_hdr *)(a->ring + pos);
    e->kind = kind;
    e->path = path;
    e->bytes = bytes;
    if (bytes) memcpy(e + 1, data, bytes);
    st64(&a->head, h + need);
    wake_worker(a);
    a->entries++;
    a->bytes += bytes;
}

/* ---- the public entry points (gs.h) ---- */

void gs_gif_write(gs_state *gs, int path, const void *qwords, uint32_t nqw)
{
    gs_async *a = gs->async;
    if (!a || path < 1 || path > 3 || nqw == 0) {
        gs_async_drain(gs);
        gs__gif_write_now(gs, path, qwords, nqw);
        return;
    }
    int hit = scan_events(&a->scan[path], (const uint8_t *)qwords, nqw);
    /* an unmasked SIGNAL / FINISH interrupt must reach the INTC from here,
     * after everything before it (and the recorder sees every input in
     * order): run synchronously.  Masked events only change CSR / SIGLBLID,
     * which the reads wait for (gs__async_events_settle). */
    uint32_t imr = (uint32_t)gs->preg[16 + 1];
    int irq = ((hit & 1) && !(imr & (GS_CSR_SIGNAL << 8))) || ((hit & 2) && !(imr & (GS_CSR_FINISH << 8)));
    if (irq || gs->rec) {
        gs_async_drain(gs);
        if (hit) a->sync_packets++;
        gs__gif_write_now(gs, path, qwords, nqw);
        return;
    }
    if (hit) a->ev_pending = 1;
    const uint8_t *q = (const uint8_t *)qwords;
    while (nqw) {
        uint32_t k = nqw > GSA_CHUNK / 16u ? GSA_CHUNK / 16u : nqw;
        push(a, GSA_GIF, (uint32_t)path, q, k * 16u);
        q += 16u * k;
        nqw -= k;
    }
}

void gs_gif_reset(gs_state *gs)
{
    gs_async *a = gs->async;
    if (a) memset(a->scan, 0, sizeof a->scan);
    if (!a || gs->rec) {
        gs_async_drain(gs);
        gs__gif_reset_now(gs);
        return;
    }
    push(a, GSA_RESET, 0, NULL, 0);
}

void gs_async_call(gs_state *gs, gs_async_fn fn, void *user, const void *data, uint32_t bytes)
{
    gs_async *a = gs ? gs->async : NULL;
    if (!a) {
        fn(user, gs, data);
        return;
    }
    /* one ring entry: header, gsa_call, data (16-byte multiple) */
    uint32_t n = (uint32_t)sizeof(gsa_call) + ((bytes + 15u) & ~15u);
    uint8_t stackbuf[512];
    uint8_t *buf = n <= sizeof stackbuf ? stackbuf : (uint8_t *)malloc(n);
    if (!buf) {
        gs_async_drain(gs);
        fn(user, gs, data);
        return;
    }
    gsa_call c = { fn, user, 0 };
    memset(buf, 0, n);
    memcpy(buf, &c, sizeof c);
    if (bytes) memcpy(buf + sizeof c, data, bytes);
    push(a, GSA_CALL, 0, buf, n);
    if (buf != stackbuf) free(buf);
}

uint64_t gs_async_mark(const gs_state *gs)
{
    const gs_async *a = gs ? gs->async : NULL;
    return a ? ld64((volatile uint64_t *)&a->head) : 0;
}

void gs_async_wait_mark(gs_state *gs, uint64_t mark)
{
    gs_async *a = gs ? gs->async : NULL;
    if (!a || ld64(&a->tail) >= mark) return;
    double t0 = gsa_now_ms();
    producer_wait_tail(a, mark);
    a->wait_ms += gsa_now_ms() - t0;
}

/* after a synchronous reset of the paths (CSR.RESET): the scan restarts */
void gs__async_rescan(gs_state *gs)
{
    if (gs->async) memset(gs->async->scan, 0, sizeof gs->async->scan);
}
