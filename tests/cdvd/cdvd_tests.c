/* SPDX-License-Identifier: CC0-1.0 */
/* CDVD model tests on a synthetic data/ folder (no game data needed).
 *
 * The synthetic disc mirrors the real one's layout at a small scale (docs/CDVD.md):
 * layer 0 is a 30-sector volume, layer 1's volume starts at image sector 14 (30 - 16) with
 * 22 blocks, so layer1_start = 30 and the image has 36 sectors (LSNs 0..51).
 *
 *   image  LSN    content
 *   20-21  20-21  A.BIN (3000 bytes: last sector part-filled)
 *   22-23  22-23  B.BIN (4096 bytes)
 *   24     24     DUP.BIN, layer-0 copy
 *   25     25     (no file)
 *   26-29  26-29  TAIL.DAT; also reached as LSN 42-45 (layer-1 system area)
 *   14-29  30-45  layer-1 system area = layer-0 sectors 14..29
 *   30-31  46-47  layer-1 PVD/root (no file)
 *   32     48     L1ONLY.BIN
 *   33     49     DUP.BIN, layer-1 copy
 *   34-35  50-51  BIG1.BIN (layer 1)
 */
#include <stdint.h>
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

#include "cdvd.h"
#include "libcdvd.h"

/* Game-side names (libcdvd_game_names.c). */
int sceCdSearchFile_129ae0(sceCdlFILE *fp, const char *name);
int sceCdLayerSearchFile_1297e0(sceCdlFILE *fp, const char *name, int layer);
int sceCdRead_12a728(uint32_t lsn, uint32_t sectors, void *buf, sceCdRMode *mode);
int sceCdGetError_12aa98(void);
int sceCdReadDvdDualInfo_12acd0(int *on_dual, uint32_t *layer1_start);

static int g_fail;
#define CHECK(c)                                                          \
    do {                                                                  \
        if (!(c)) {                                                       \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); \
            ++g_fail;                                                     \
        }                                                                 \
    } while (0)

#define S 2048u

/* ---- quiet logging that counts warnings ---- */
static int g_warns;
static void quiet_log(void *ctx, int level, const char *msg) {
    (void)ctx;
    if (level >= CDVD_LOG_WARN) ++g_warns;
    if (getenv("CDVD_TEST_VERBOSE")) fprintf(stderr, "[log %d] %s\n", level, msg);
}

/* ---- fixture ---- */
static uint8_t content(int file, uint32_t off) { return (uint8_t)(file * 37 + off * 7 + (off >> 8)); }

typedef struct {
    const char *name;
    int id;
    uint32_t size;
} fdef;
static const fdef k_files[] = {
    {"A.BIN", 1, 3000},  {"B.BIN", 2, 4096},  {"DUP.BIN", 3, 2048},  {"TAIL.DAT", 4, 4 * S},
    {"L1ONLY.BIN", 5, 2048}, {"BIG1.BIN", 6, 2 * S}, {"EMPTY", 7, 0},
};

static void write_file(const char *dir, const char *name, int id, uint32_t size) {
    char p[512];
    FILE *f;
    snprintf(p, sizeof p, "%s/%s", dir, name);
    f = fopen(p, "wb");
    if (!f) {
        fprintf(stderr, "cannot write %s\n", p);
        exit(2);
    }
    for (uint32_t i = 0; i < size; ++i) fputc(content(id, i), f);
    fclose(f);
}

static void write_text(const char *dir, const char *name, const char *text) {
    char p[512];
    FILE *f;
    snprintf(p, sizeof p, "%s/%s", dir, name);
    f = fopen(p, "wb");
    if (!f) exit(2);
    fputs(text, f);
    fclose(f);
}

static const char *k_manifest_v2 =
    "# rg-extract manifest v2\n"
    "# source_sha1\t0000000000000000000000000000000000000000\n"
    "# source_size\t73728\n"
    "# source_serial\tSLUS-12345\tVER 1.00\n"
    "# volume\t0\t0\t30\n"
    "# volume\t1\t14\t22\n"
    "path\tsize\tsha256\tlba\tcopies\n"
    "A.BIN\t3000\tx\t20\tL0:20\n"
    "B.BIN\t4096\tx\t22\tL0:22\n"
    "BIG1.BIN\t4096\tx\t34\tL1:34\n"
    "DUP.BIN\t2048\tx\t24\tL0:24,L1:33\n"
    "EMPTY\t0\tx\t-\tL0:-\n"
    "L1ONLY.BIN\t2048\tx\t32\tL1:32\n"
    "TAIL.DAT\t8192\tx\t26\tL0:26\n"
    "# section\tconverted\n"
    "path\tsize\tsha256\tsource\tkind\n"
    "converted/MOVIE/00/X.mpg\t10\tx\tMOVIE/00/X.MVI\tmovie-video\n";

static void make_fixture(const char *dir) {
    MKDIR(dir);
    for (size_t i = 0; i < sizeof k_files / sizeof k_files[0]; ++i)
        write_file(dir, k_files[i].name, k_files[i].id, k_files[i].size);
    write_text(dir, "MANIFEST.tsv", k_manifest_v2);
}

/* Expected bytes of sector `rel` of file `id` (zero past the end). */
static void expect_sector(uint8_t *out, int id, uint32_t size, uint32_t rel) {
    for (uint32_t i = 0; i < S; ++i) {
        uint32_t off = rel * S + i;
        out[i] = off < size ? content(id, off) : 0;
    }
}

static int is_zero(const uint8_t *p, size_t n) {
    for (size_t i = 0; i < n; ++i)
        if (p[i]) return 0;
    return 1;
}

/* ---- disc tests ---- */
static void test_geometry(cdvd_disc *d) {
    CHECK(cdvd_disc_dual(d) == 1);
    CHECK(cdvd_disc_layer1_start(d) == 30);
    CHECK(cdvd_disc_image_sectors(d) == 36);
    CHECK(cdvd_disc_lsn_end(d) == 52);
    CHECK(cdvd_lsn_to_image(d, 0) == 0);
    CHECK(cdvd_lsn_to_image(d, 29) == 29);
    CHECK(cdvd_lsn_to_image(d, 30) == 14); /* layer-1 volume sector 0 */
    CHECK(cdvd_lsn_to_image(d, 46) == 30); /* layer-1 PVD: layer1_start + 16 */
    CHECK(cdvd_lsn_to_image(d, 51) == 35);
    CHECK(cdvd_image_to_lsn(d, 33, 1) == 49);
    CHECK(cdvd_image_to_lsn(d, 24, 0) == 24);
    CHECK(cdvd_disc_file_count(d) == 7); /* the converted section is not on the disc */
}

static void test_find(cdvd_disc *d) {
    cdvd_file_info fi;
    CHECK(cdvd_disc_find(d, "\\A.BIN;1", 0, &fi) && fi.lsn[0] == 20 && fi.size == 3000);
    CHECK(cdvd_disc_find(d, "cdrom0:\\DUP.BIN;1", 1, &fi) && fi.lsn[1] == 49 && fi.image[1] == 33);
    CHECK(fi.lsn[0] == 24);
    CHECK(cdvd_disc_find(d, "DUP.BIN", 0, &fi));
    CHECK(!cdvd_disc_find(d, "\\L1ONLY.BIN;1", 0, &fi)); /* layer 0 has no copy */
    CHECK(cdvd_disc_find(d, "/l1only.bin", 1, &fi) && fi.lsn[1] == 48);
    CHECK(!cdvd_disc_find(d, "\\A.BIN;1", 1, &fi));
    CHECK(cdvd_disc_find(d, "\\EMPTY;1", 0, &fi) && fi.size == 0 && fi.lsn[0] == CDVD_NO_LSN);
    CHECK(!cdvd_disc_find(d, "\\NOPE.BIN;1", 0, &fi));
    CHECK(!cdvd_disc_find(d, "\\X.mpg", 0, &fi));
    CHECK(!cdvd_disc_find(d, "", 0, &fi));
}

static void test_reads(cdvd_disc *d) {
    uint8_t buf[8 * S], want[S];
    uint32_t un = 99;
    const char *path;
    uint64_t off;

    /* Spanning two files: A (part-filled last sector) then B. */
    memset(buf, 0xCC, sizeof buf);
    CHECK(cdvd_disc_read(d, 20, 4, buf, &un) == CDVD_OK && un == 0);
    expect_sector(want, 1, 3000, 0);
    CHECK(!memcmp(buf, want, S));
    expect_sector(want, 1, 3000, 1);
    CHECK(!memcmp(buf + S, want, S));
    CHECK(is_zero(buf + S + (3000 - S), 2 * S - 3000));
    expect_sector(want, 2, 4096, 0);
    CHECK(!memcmp(buf + 2 * S, want, S));
    expect_sector(want, 2, 4096, 1);
    CHECK(!memcmp(buf + 3 * S, want, S));

    /* File, gap, file. */
    g_warns = 0;
    memset(buf, 0xCC, sizeof buf);
    CHECK(cdvd_disc_read(d, 24, 3, buf, &un) == CDVD_OK && un == 1);
    expect_sector(want, 3, 2048, 0);
    CHECK(!memcmp(buf, want, S));
    CHECK(is_zero(buf + S, S));
    expect_sector(want, 4, 4 * S, 0);
    CHECK(!memcmp(buf + 2 * S, want, S));
    CHECK(g_warns == 1);

    /* Across layer1_start: LSN 28,29 = TAIL 2,3; LSN 30,31 = image 14,15 (no file). */
    memset(buf, 0xCC, sizeof buf);
    CHECK(cdvd_disc_read(d, 28, 4, buf, &un) == CDVD_OK && un == 2);
    expect_sector(want, 4, 4 * S, 2);
    CHECK(!memcmp(buf, want, S));
    expect_sector(want, 4, 4 * S, 3);
    CHECK(!memcmp(buf + S, want, S));
    CHECK(is_zero(buf + 2 * S, 2 * S));

    /* The layer-1 system area reaches layer 0's last sectors: LSN 44,45 = image 28,29
     * (TAIL 2,3); 46,47 = layer-1 PVD/root (no file); 48 = L1ONLY; 49 = DUP (layer 1). */
    memset(buf, 0xCC, sizeof buf);
    CHECK(cdvd_disc_read(d, 44, 6, buf, &un) == CDVD_OK && un == 2);
    expect_sector(want, 4, 4 * S, 2);
    CHECK(!memcmp(buf, want, S));
    expect_sector(want, 4, 4 * S, 3);
    CHECK(!memcmp(buf + S, want, S));
    CHECK(is_zero(buf + 2 * S, 2 * S));
    expect_sector(want, 5, 2048, 0);
    CHECK(!memcmp(buf + 4 * S, want, S));
    expect_sector(want, 3, 2048, 0);
    CHECK(!memcmp(buf + 5 * S, want, S));

    /* End of disc. */
    CHECK(cdvd_disc_read(d, 50, 2, buf, &un) == CDVD_OK && un == 0);
    expect_sector(want, 6, 2 * S, 1);
    CHECK(!memcmp(buf + S, want, S));
    CHECK(cdvd_disc_read(d, 51, 2, buf, &un) == CDVD_E_RANGE);
    CHECK(cdvd_disc_read(d, 52, 1, buf, &un) == CDVD_E_RANGE);
    CHECK(cdvd_disc_read(d, 0xFFFFFFFFu, 1, buf, &un) == CDVD_E_RANGE);
    CHECK(cdvd_disc_read(d, 0, 0, buf, &un) == CDVD_OK);

    /* LSN -> (file, offset). */
    CHECK(cdvd_disc_map(d, 49, &path, &off) && !strcmp(path, "DUP.BIN") && off == 0);
    CHECK(cdvd_disc_map(d, 51, &path, &off) && !strcmp(path, "BIG1.BIN") && off == S);
    CHECK(cdvd_disc_map(d, 45, &path, &off) && !strcmp(path, "TAIL.DAT") && off == 3 * S);
    CHECK(!cdvd_disc_map(d, 47, &path, &off));
    CHECK(!cdvd_disc_map(d, 16, &path, &off));
    CHECK(!cdvd_disc_map(d, 52, &path, &off));
}

static void test_manifest_variants(const char *base) {
    char dir[512], err[256];
    cdvd_disc *d;
    cdvd_file_info fi;
    uint8_t buf[S];

    /* v1, single layer, no volume lines. */
    snprintf(dir, sizeof dir, "%s_v1", base);
    MKDIR(dir);
    write_file(dir, "A.BIN", 1, 3000);
    write_text(dir, "MANIFEST.tsv",
               "# rg-extract manifest v1\n# source_sha1\tab\n# source_size\t61440\n"
               "path\tsize\tsha256\tlba\tcopies\nA.BIN\t3000\tx\t20\tL0:20\n");
    d = cdvd_disc_open(dir, err, sizeof err);
    CHECK(d != NULL);
    if (d) {
        CHECK(!cdvd_disc_dual(d) && cdvd_disc_layer1_start(d) == 0 && cdvd_disc_lsn_end(d) == 30);
        CHECK(cdvd_disc_find(d, "\\A.BIN;1", 1, &fi) && fi.lsn[0] == 20); /* layer ignored */
        CHECK(cdvd_lsn_to_image(d, 29) == 29);
        CHECK(cdvd_disc_read(d, 21, 1, buf, NULL) == CDVD_OK);
        cdvd_disc_close(d);
    }

    /* v1 with layer-1 copies but no geometry and an unknown image: refused. */
    write_text(dir, "MANIFEST.tsv",
               "# rg-extract manifest v1\n# source_sha1\tab\n"
               "path\tsize\tsha256\tlba\tcopies\nA.BIN\t3000\tx\t20\tL1:20\n");
    err[0] = 0;
    d = cdvd_disc_open(dir, err, sizeof err);
    CHECK(d == NULL && strstr(err, "geometry"));

    /* v1 of the known disc: geometry from the built-in table. */
    write_text(dir, "MANIFEST.tsv",
               "# rg-extract manifest v1\n# source_sha1\t87377e721be58e8b6a5a7501721563500d237df7\n"
               "# source_size\t6967721984\n"
               "path\tsize\tsha256\tlba\tcopies\nA.BIN\t3000\tx\t1700000\tL1:1700000\n");
    d = cdvd_disc_open(dir, err, sizeof err);
    CHECK(d != NULL);
    if (d) {
        CHECK(cdvd_disc_dual(d) && cdvd_disc_layer1_start(d) == 1646704 && cdvd_disc_lsn_end(d) == 3402224);
        CHECK(cdvd_disc_find(d, "\\A.BIN;1", 1, &fi) && fi.lsn[1] == 1700016);
        CHECK(cdvd_disc_read(d, 1700017, 1, buf, NULL) == CDVD_OK);
        cdvd_disc_close(d);
    }

    /* Overlapping files, missing data file, garbage. */
    write_text(dir, "MANIFEST.tsv",
               "# rg-extract manifest v2\npath\tsize\tsha256\tlba\tcopies\n"
               "A.BIN\t3000\tx\t20\tL0:20\nB.BIN\t10\tx\t21\tL0:21\n");
    CHECK(cdvd_disc_open(dir, err, sizeof err) == NULL && strstr(err, "overlap"));
    write_text(dir, "MANIFEST.tsv",
               "# rg-extract manifest v2\n# source_size\t61440\npath\tsize\tsha256\tlba\tcopies\n"
               "MISSING.BIN\t10\tx\t21\tL0:21\n");
    d = cdvd_disc_open(dir, err, sizeof err);
    CHECK(d != NULL);
    if (d) {
        CHECK(cdvd_disc_read(d, 21, 1, buf, NULL) == CDVD_E_IO);
        cdvd_disc_close(d);
    }
    write_text(dir, "MANIFEST.tsv", "hello\n");
    CHECK(cdvd_disc_open(dir, err, sizeof err) == NULL);
    snprintf(dir, sizeof dir, "%s_none", base);
    CHECK(cdvd_disc_open(dir, err, sizeof err) == NULL && strstr(err, "MANIFEST.tsv"));
}

/* ---- libcdvd + drive tests ---- */
static int g_cb_reason, g_cb_count;
static void cb(int reason) {
    g_cb_reason = reason;
    ++g_cb_count;
}

static int g_hook_calls;
static uint64_t g_hook_due;
static void wait_hook(void *ctx, uint64_t due) {
    (void)ctx;
    ++g_hook_calls;
    g_hook_due = due;
    cdvd_poll(due + 5); /* the kernel would run other threads until then */
}

static void test_libcdvd(const char *dir) {
    sceCdlFILE f;
    sceCdRMode mode = {0, 0, SCECdSecS2048, 0};
    uint8_t buf[4 * S], want[S];
    int dual = -1;
    uint32_t l1 = 0, tray = 7;
    uint64_t due = 0, t0;
    cdvd_timing tm = {1000, 370};

    CHECK(sceCdGetDiskType() == SCECdNODISC);
    CHECK(sceCdHleMount(dir) == 1);
    CHECK(sceCdInit(SCECdINIT) == 1);
    CHECK(sceCdMmode(SCECdMmodeDvd) == 1);
    CHECK(sceCdGetDiskType() == SCECdPS2DVD);
    CHECK(sceCdDiskReady(0) == SCECdComplete);
    CHECK(sceCdTrayReq(SCECdTrayCheck, &tray) == 1 && tray == 0);
    CHECK(sceCdReadDvdDualInfo_12acd0(&dual, &l1) == 1 && dual == 1 && l1 == 30);
    CHECK(sizeof(sceCdlFILE) == 0x24);
    cdvd_drive_set_timing(&tm);

    /* Search: layer 0 and layer 1 copies of the same file. */
    CHECK(sceCdSearchFile(&f, "\\DUP.BIN;1") == 1 && f.lsn == 24 && f.size == 2048);
    CHECK(!strcmp(f.name, "DUP.BIN;1"));
    CHECK(sceCdLayerSearchFile_1297e0(&f, "\\DUP.BIN;1", 1) == 1 && f.lsn == 49);
    CHECK(sceCdSearchFile_129ae0(&f, "\\L1ONLY.BIN;1") == 0);
    CHECK(sceCdLayerSearchFile(&f, "\\EMPTY;1", 0) == 1 && f.size == 0);
    CHECK(sceCdLayerSearchFile(&f, "\\BIG1.BIN;1", 1) == 1 && f.lsn == 50 && f.size == 4096);

    /* Asynchronous read: nothing lands before completion; a second command is refused. */
    sceCdCallback(cb);
    g_cb_count = 0;
    memset(buf, 0xCC, sizeof buf);
    t0 = cdvd_now();
    CHECK(sceCdRead_12a728(f.lsn, 2, buf, &mode) == 1);
    CHECK(sceCdSync(1) == 1);
    CHECK(sceCdRead(20, 1, buf, &mode) == 0);
    CHECK(sceCdSeek(20) == 0);
    CHECK(cdvd_next_event(&due) && due == t0 + 1000 + 2 * 370);
    cdvd_poll(due - 1);
    CHECK(sceCdSync(1) == 1 && buf[0] == 0xCC && g_cb_count == 0);
    cdvd_poll(due);
    CHECK(sceCdSync(1) == 0 && !cdvd_next_event(&due));
    CHECK(g_cb_count == 1 && g_cb_reason == SCECdFuncRead);
    CHECK(sceCdGetError_12aa98() == SCECdErNO);
    expect_sector(want, 6, 2 * S, 0);
    CHECK(!memcmp(buf, want, S));
    expect_sector(want, 6, 2 * S, 1);
    CHECK(!memcmp(buf + S, want, S));
    CHECK(buf[2 * S] == 0xCC); /* nothing past the request */

    /* Blocking sync without a kernel: the drive's clock jumps to completion. */
    t0 = cdvd_now();
    CHECK(sceCdRead(48, 2, buf, &mode) == 1);
    CHECK(sceCdSync(0) == 0 && sceCdGetError() == SCECdErNO);
    CHECK(cdvd_now() == t0 + 1000 + 2 * 370);
    expect_sector(want, 5, 2048, 0);
    CHECK(!memcmp(buf, want, S));

    /* Blocking sync with a kernel wait hook. */
    cdvd_drive_set_wait_hook(wait_hook, NULL);
    g_hook_calls = 0;
    t0 = cdvd_now();
    CHECK(sceCdRead(20, 1, buf, NULL) == 1);
    CHECK(sceCdSync(0) == 0 && g_hook_calls == 1 && g_hook_due == t0 + 1370);
    CHECK(cdvd_now() == t0 + 1375);
    expect_sector(want, 1, 3000, 0);
    CHECK(!memcmp(buf, want, S));
    cdvd_drive_set_wait_hook(NULL, NULL);

    /* Errors: past the end (accepted, completes with SCECdErIPI, no data). */
    memset(buf, 0xCC, sizeof buf);
    CHECK(sceCdRead(51, 2, buf, &mode) == 1);
    CHECK(sceCdSync(0) == 0 && sceCdGetError() == SCECdErIPI && buf[0] == 0xCC);
    mode.datapattern = SCECdSecS2328;
    CHECK(sceCdRead(20, 1, buf, &mode) == 1);
    CHECK(sceCdSync(0) == 0 && sceCdGetError() == SCECdErPRM);
    mode.datapattern = SCECdSecS2048;
    CHECK(sceCdRead(20, 1, buf, &mode) == 1 && sceCdBreak() == 1);
    CHECK(sceCdSync(1) == 0 && sceCdGetError() == SCECdErABRT && buf[0] == 0xCC);
    g_cb_count = 0;
    CHECK(sceCdSeek(49) == 1 && sceCdSync(0) == 0 && sceCdGetError() == SCECdErNO);
    CHECK(g_cb_count == 1 && g_cb_reason == SCECdFuncSeek);

    /* A search while a read is pending lets the read finish first. */
    CHECK(sceCdRead(22, 1, buf, &mode) == 1);
    CHECK(sceCdSearchFile(&f, "\\B.BIN;1") == 1 && sceCdSync(1) == 0);
    expect_sector(want, 2, 4096, 0);
    CHECK(!memcmp(buf, want, S));

    CHECK(sceCdCallback(NULL) == cb);
    CHECK(sceCdInit(SCECdEXIT) == 1);
    sceCdHleUnmount();
    CHECK(sceCdGetDiskType() == SCECdNODISC);
    CHECK(sceCdRead(20, 1, buf, &mode) == 1 && sceCdSync(0) == 0 && sceCdGetError() == SCECdErNODISC);
}

int main(int argc, char **argv) {
    const char *dir = argc > 1 ? argv[1] : "cdvd_fixture";
    char err[256];
    cdvd_disc *d;

    cdvd_set_log(quiet_log, NULL);
    make_fixture(dir);
    d = cdvd_disc_open(dir, err, sizeof err);
    if (!d) {
        fprintf(stderr, "cannot open fixture: %s\n", err);
        return 1;
    }
    test_geometry(d);
    test_find(d);
    test_reads(d);
    cdvd_disc_close(d);
    test_manifest_variants(dir);
    test_libcdvd(dir);
    if (g_fail) {
        fprintf(stderr, "%d check(s) failed\n", g_fail);
        return 1;
    }
    printf("all cdvd tests passed\n");
    return 0;
}
