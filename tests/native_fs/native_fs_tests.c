/* SPDX-License-Identifier: CC0-1.0
 * Native file service tests (docs/NATIVE-FS.md "Tests").
 *   native-fs-tests <scratch dir>     synthetic data folder (always)
 *   native-fs-realdata-tests          RG_DATA: every disc file read natively and
 *                                     compared with the CDVD sector model (oracle);
 *                                     exit 77 without RG_DATA
 */
#include "rg_fs.h"
#include "rg_fs_oracle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#define MKDIR(p) _mkdir(p)
#else
#include <sys/stat.h>
#define MKDIR(p) mkdir(p, 0777)
#endif

static int fails;
#define CHECK(c)                                                         \
    do {                                                                 \
        if (!(c)) {                                                      \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); \
            fails++;                                                     \
        }                                                                \
    } while (0)

static void put(const char *dir, const char *rel, int size, int seed)
{
    char p[1024];
    FILE *f;
    int i;
    snprintf(p, sizeof p, "%s/%s", dir, rel);
    f = fopen(p, "wb");
    if (!f) {
        fprintf(stderr, "cannot write %s\n", p);
        exit(2);
    }
    for (i = 0; i < size; i++)
        fputc((i * 7 + seed) & 0xFF, f);
    fclose(f);
}

static int pat(int64_t i, int seed) { return (int)((i * 7 + seed) & 0xFF); }

static int cb_count;
static int64_t cb_last;
static void on_done(void *user, int req, int64_t result)
{
    (void)req;
    cb_count++;
    cb_last = result;
    if (user)
        (*(int *)user)++;
}

static int hook_count;
static char hook_path[256];
static void on_hook(void *user, int h, const char *path, int64_t off, int64_t len, int64_t got,
                    const void *buf)
{
    (void)user, (void)h, (void)off, (void)len, (void)got, (void)buf;
    hook_count++;
    snprintf(hook_path, sizeof hook_path, "%s", path ? path : "");
}

static int synthetic(const char *dir)
{
    char p[1024], c[256];
    unsigned char buf[8192];
    int h, h2, i, ok;
    int64_t r;
    MKDIR(dir);
    snprintf(p, sizeof p, "%s/BIN", dir), MKDIR(p);
    snprintf(p, sizeof p, "%s/MOVIE", dir), MKDIR(p);
    snprintf(p, sizeof p, "%s/MOVIE/99", dir), MKDIR(p);
    snprintf(p, sizeof p, "%s/converted", dir), MKDIR(p);
    put(dir, "BIN/NORMAL.BIN", 5000, 1);
    put(dir, "DATA0_0.HD6", 3000, 2);
    put(dir, "MOVIE/99/STAFF_A.MVI", 70000, 3);
    put(dir, "converted/STAFF_A.yuv", 10, 4);
    put(dir, "MANIFEST.tsv", 10, 5);

    /* names */
    CHECK(!strcmp(rg_fs_canon("cdrom0:\\BIN\\NORMAL.BIN;1", c, sizeof c), "BIN/NORMAL.BIN"));
    CHECK(!strcmp(rg_fs_canon("\\data0_0.hd6;1", c, sizeof c), "DATA0_0.HD6"));
    CHECK(!strcmp(rg_fs_canon("cddat://movie//99/x.mvi", c, sizeof c), "MOVIE/99/X.MVI"));
    CHECK(!strcmp(rg_fs_canon("a/b;x", c, sizeof c), "A/B;X")); /* not a version */

    CHECK(rg_fs_open("BIN/NORMAL.BIN") == -1); /* nothing mounted */
    CHECK(rg_fs_mount(dir) == 3);              /* converted/ and MANIFEST.tsv skipped */
    CHECK(rg_fs_mounted());
    h = rg_fs_open("cdrom0:\\BIN\\NORMAL.BIN;1");
    CHECK(h >= 0);
    CHECK(rg_fs_open("\\bin\\normal.bin") == h);
    CHECK(rg_fs_open("BIN/NORMAL.BIN") == h);
    CHECK(rg_fs_open("host0:BIN/NORMAL.BIN") == h);
    CHECK(rg_fs_open("BIN/NORMAL.BI") == -1);
    CHECK(rg_fs_open("converted/STAFF_A.yuv") == -1);
    CHECK(rg_fs_open("MANIFEST.tsv") == -1);
    CHECK(rg_fs_size(h) == 5000);
    CHECK(rg_fs_name(h) && !strcmp(rg_fs_name(h), "BIN/NORMAL.BIN"));
    CHECK(rg_fs_size(-1) == -1 && rg_fs_size(99) == -1);

    /* sync reads */
    CHECK(rg_fs_add_read_hook(on_hook, NULL) == 0);
    memset(buf, 0xEE, sizeof buf);
    r = rg_fs_read_fill(h, 100, buf, 1000);
    CHECK(r == 1000);
    for (ok = 1, i = 0; i < 1000; i++)
        ok &= buf[i] == pat(100 + i, 1);
    CHECK(ok);
    CHECK(buf[1000] == 0xEE); /* nothing written past len */
    CHECK(hook_count == 1 && !strcmp(hook_path, "BIN/NORMAL.BIN"));
    /* across EOF: the in-file part, then zeros up to len (a whole 2048 block) */
    memset(buf, 0xEE, sizeof buf);
    r = rg_fs_read_fill(h, 4096, buf, 2048);
    CHECK(r == 904);
    for (ok = 1, i = 0; i < 904; i++)
        ok &= buf[i] == pat(4096 + i, 1);
    for (i = 904; i < 2048; i++)
        ok &= buf[i] == 0;
    CHECK(ok);
    /* past EOF: zeros */
    memset(buf, 0xEE, sizeof buf);
    CHECK(rg_fs_read_fill(h, 6000, buf, 100) == 0);
    for (ok = 1, i = 0; i < 100; i++)
        ok &= buf[i] == 0;
    CHECK(ok);
    /* bad handle: -1, zero-filled */
    memset(buf, 0xEE, sizeof buf);
    CHECK(rg_fs_read_fill(42, 0, buf, 16) == -1);
    CHECK(buf[0] == 0 && buf[15] == 0);
    rg_fs_remove_read_hook(on_hook, NULL);
    hook_count = 0;
    CHECK(rg_fs_read_fill(h, 0, buf, 1) == 1 && hook_count == 0);

    /* async: completion is visible only when the caller polls / pumps */
    h2 = rg_fs_open("MOVIE/99/STAFF_A.MVI");
    CHECK(h2 >= 0);
    {
        static unsigned char big[70000 + 4096];
        int mine = 0, id, id2, n;
        int64_t res = 0;
        cb_count = 0;
        memset(big, 0xEE, sizeof big);
        id = rg_fs_read_async(h2, 0, big, 71680, on_done, &mine);
        CHECK(id > 0);
        while (rg_fs_pending())
            ; /* the worker finishes ... */
        CHECK(cb_count == 0);         /* ... but nothing is delivered yet */
        CHECK(rg_fs_poll(id, &res) == 1 && res == 70000);
        CHECK(cb_count == 1 && mine == 1 && cb_last == 70000);
        CHECK(rg_fs_poll(id, &res) == -1); /* released */
        for (ok = 1, i = 0; i < 70000; i++)
            ok &= big[i] == pat(i, 3);
        for (i = 70000; i < 71680; i++)
            ok &= big[i] == 0;
        CHECK(ok && big[71680] == 0xEE);
        /* wait */
        id = rg_fs_read_async(h, 10, buf, 20, on_done, NULL);
        CHECK(rg_fs_wait(id) == 20 && cb_count == 2);
        CHECK(buf[0] == pat(10, 1));
        /* pump delivers in submission order */
        id = rg_fs_read_async(h, 0, buf, 10, NULL, NULL);
        id2 = rg_fs_read_async(h2, 0, buf + 100, 10, on_done, NULL);
        CHECK(id > 0 && id2 > 0 && id2 != id);
        while (rg_fs_pending())
            ;
        n = rg_fs_pump();
        CHECK(n == 2 && cb_count == 3);
        CHECK(rg_fs_poll(id2, NULL) == -1);
        CHECK(rg_fs_read_async(99, 0, buf, 1, NULL, NULL) == -1);
        CHECK(rg_fs_wait(12345678) == -1);
    }
    {
        rg_fs_stats st;
        rg_fs_get_stats(&st);
        CHECK(st.files == 3);
        CHECK(st.async_reads == 4);
        CHECK(st.errors >= 1);
    }
    rg_fs_unmount();
    CHECK(!rg_fs_mounted());
    CHECK(rg_fs_open("BIN/NORMAL.BIN") == -1);
    return fails;
}

/* ---- real data: every disc file through the oracle ---- */
static int realdata(void)
{
    const char *dir = getenv("RG_DATA");
    char man[1024], line[2048];
    FILE *f;
    static unsigned char buf[0x40000];
    int files = 0;
    rg_fs_oracle_stats os;
    if (!dir || !*dir) {
        fprintf(stderr, "RG_DATA not set: skipped\n");
        return 77;
    }
    CHECK(rg_fs_mount(dir) > 100);
    CHECK(rg_fs_oracle_start(dir));
    snprintf(man, sizeof man, "%s/MANIFEST.tsv", dir);
    f = fopen(man, "r");
    CHECK(f != NULL);
    while (f && fgets(line, sizeof line, f)) {
        char *tab;
        long long size;
        int h;
        if (line[0] == '#') {
            if (!strncmp(line, "# section", 9))
                break;
            continue;
        }
        if (!strncmp(line, "path\t", 5))
            continue;
        tab = strchr(line, '\t');
        if (!tab)
            continue;
        *tab = 0;
        size = atoll(tab + 1);
        h = rg_fs_open(line);
        CHECK(h >= 0);
        if (h < 0)
            continue;
        CHECK(rg_fs_size(h) == size);
        /* first 256 KB, a block in the middle, and the last (partial) block */
        rg_fs_read_fill(h, 0, buf, size < (long long)sizeof buf ? ((size + 2047) & ~2047LL) : (long long)sizeof buf);
        if (size > 0x100000)
            rg_fs_read_fill(h, (size / 2) & ~2047LL, buf, 0x10000);
        if (size > 0)
            CHECK(rg_fs_read_fill(h, (size - 1) & ~2047LL, buf, 2048) == size - ((size - 1) & ~2047LL));
        files++;
    }
    if (f)
        fclose(f);
    rg_fs_oracle_get(&os);
    fprintf(stderr, "%d files; oracle: %llu reads, %llu MB compared, %llu mismatched, %llu skipped\n",
            files, (unsigned long long)os.checked, (unsigned long long)(os.bytes >> 20),
            (unsigned long long)os.mismatched, (unsigned long long)os.skipped);
    CHECK(files > 100);
    CHECK(os.checked >= (uint64_t)files);
    CHECK(os.mismatched == 0);
    rg_fs_oracle_stop();
    rg_fs_unmount();
    return fails;
}

int main(int argc, char **argv)
{
    int r;
    if (argc > 1 && !strcmp(argv[1], "--realdata"))
        r = realdata();
    else
        r = synthetic(argc > 1 ? argv[1] : "native_fs_fixture");
    if (r == 77)
        return 77;
    fprintf(stderr, "%s\n", fails ? "FAIL" : "PASS");
    return fails ? 1 : 0;
}
