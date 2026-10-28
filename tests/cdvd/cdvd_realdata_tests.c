/* SPDX-License-Identifier: CC0-1.0 */
/* CDVD model against the real extraction. Skipped (exit 77) unless RG_DATA points at
 * the data/ folder rg-extract wrote. With RG_ISO also set to the disc image, every read
 * is compared with the image itself at image sector = LSN (layer 0) or LSN - 16
 * (layer 1), and the layer-1 PVD is checked to sit at LSN layer1_start + 16. */
#if !defined(_WIN32) && !defined(_FILE_OFFSET_BITS)
#define _FILE_OFFSET_BITS 64
#endif
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cdvd.h"
#include "libcdvd.h"

#define S 2048u
#define SKIP 77

static int g_fail;
#define CHECK(c)                                                          \
    do {                                                                  \
        if (!(c)) {                                                       \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); \
            ++g_fail;                                                     \
        }                                                                 \
    } while (0)

static const char *g_data;
static FILE *g_iso;

static int seek64(FILE *f, uint64_t off) {
#ifdef _WIN32
    return _fseeki64(f, (long long)off, SEEK_SET);
#else
    return fseeko(f, (off_t)off, SEEK_SET);
#endif
}

/* Bytes [off, off+n) of data/<path>, zero past its end. */
static int read_data_file(const char *path, uint64_t off, uint8_t *out, size_t n) {
    char p[1024];
    FILE *f;
    size_t got = 0;
    snprintf(p, sizeof p, "%s/%s", g_data, path);
    f = fopen(p, "rb");
    if (!f) return 0;
    if (seek64(f, off) == 0) got = fread(out, 1, n, f);
    fclose(f);
    memset(out + got, 0, n - got);
    return 1;
}

static int read_iso(uint32_t image_sector, uint8_t *out, uint32_t count) {
    return seek64(g_iso, (uint64_t)image_sector * S) == 0 && fread(out, 1, (size_t)count * S, g_iso) == (size_t)count * S;
}

/* Reads sectors [rel, rel+count) of a file through libcdvd and compares them with the
 * extracted file (and the image). */
static void check_file(const char *iso_name, int layer, uint32_t rel, uint32_t count, uint32_t expect_lsn) {
    sceCdlFILE f;
    sceCdRMode mode = {0, 0, SCECdSecS2048, 0};
    uint8_t *got = (uint8_t *)malloc((size_t)count * S), *want = (uint8_t *)malloc((size_t)count * S);
    cdvd_file_info fi;
    const char *mpath = NULL;
    uint64_t moff = 0;
    if (!got || !want) exit(2);
    if (!sceCdLayerSearchFile(&f, iso_name, layer)) {
        fprintf(stderr, "not found: %s on layer %d\n", iso_name, layer);
        ++g_fail;
        goto out;
    }
    if (expect_lsn) CHECK(f.lsn == expect_lsn);
    if ((uint64_t)rel * S >= f.size) rel = (f.size - 1) / S; /* clamp to the last sector */
    memset(got, 0xCC, (size_t)count * S);
    CHECK(sceCdRead(f.lsn + rel, count, got, &mode) == 1);
    CHECK(sceCdSync(0) == 0 && sceCdGetError() == SCECdErNO);
    CHECK(cdvd_disc_map(cdvd_drive_disc(), f.lsn + rel, &mpath, &moff));
    CHECK(cdvd_disc_find(cdvd_drive_disc(), iso_name, layer, &fi));
    if (mpath) {
        uint64_t off = (uint64_t)rel * S;
        size_t n = (size_t)count * S;
        CHECK(moff == off);
        /* Only the file's own sectors; a run past its end continues into whatever follows. */
        if (off + n > ((fi.size + S - 1) / S) * S) n = (size_t)(((fi.size + S - 1) / S) * S - off);
        CHECK(read_data_file(mpath, off, want, n));
        CHECK(memcmp(got, want, n) == 0);
        if (memcmp(got, want, n)) fprintf(stderr, "  mismatch: %s layer %d sector %u\n", iso_name, layer, rel);
    }
    if (g_iso) {
        uint32_t img = cdvd_lsn_to_image(cdvd_drive_disc(), f.lsn + rel);
        CHECK(img == (layer ? f.lsn + rel - 16 : f.lsn + rel));
        CHECK(read_iso(img, want, count));
        /* The image holds the disc's padding after a file's last byte; data/ does not. */
        if ((uint64_t)(rel + count) * S <= f.size) CHECK(memcmp(got, want, (size_t)count * S) == 0);
    }
    printf("ok  L%d %-28s lsn %8u  sectors %u+%u\n", layer, iso_name, (unsigned)f.lsn, (unsigned)rel, (unsigned)count);
out:
    free(got);
    free(want);
}

int main(void) {
    const char *iso = getenv("RG_ISO");
    int dual = 0;
    uint32_t l1 = 0;
    sceCdlFILE f;
    uint8_t buf[S];

    g_data = getenv("RG_DATA");
    if (!g_data || !*g_data) {
        printf("RG_DATA not set: skipping the real-data CDVD checks\n");
        return SKIP;
    }
    if (iso && *iso) {
        g_iso = fopen(iso, "rb");
        if (!g_iso) fprintf(stderr, "warning: cannot open RG_ISO=%s; image checks skipped\n", iso);
    }
    if (!sceCdHleMount(g_data) || sceCdInit(SCECdINIT) != 1) {
        fprintf(stderr, "cannot mount %s\n", g_data);
        return 1;
    }
    CHECK(sceCdReadDvdDualInfo(&dual, &l1) == 1);
    CHECK(dual == 1 && l1 == 1646704); /* layer-0 sector count, Redump's layer break */
    CHECK(cdvd_disc_lsn_end(cdvd_drive_disc()) == 3402208u + 16u);

    /* SYSTEM.CNF names the boot ELF. */
    CHECK(sceCdSearchFile(&f, "\\SYSTEM.CNF;1") == 1 && f.size == 57);
    CHECK(sceCdRead(f.lsn, 1, buf, NULL) == 1 && sceCdSync(0) == 0);
    CHECK(memcmp(buf, "BOOT2 = cdrom0:\\SCUS_974.90;1", 29) == 0);

    check_file("\\SYSTEM.CNF;1", 0, 0, 1, 0);
    check_file("\\SCUS_974.90;1", 0, 0, 64, 0);
    /* On both layers: the layer-1 copy's LSN is its manifest LBA + 16. */
    check_file("\\BIN\\NORMAL.BIN;1", 0, 0, 16, 1001888);
    check_file("\\BIN\\NORMAL.BIN;1", 1, 0, 16, 2740017 + 16);
    check_file("\\BIN\\NORMAL.BIN;1", 1, 1000, 1, 2740017 + 16); /* last, part-filled sector */
    check_file("\\RGSYS.DAT;1", 1, 0, 1, 0);
    /* Layer 1 only, the archives the game opens with sceCdLayerSearchFile(.., 1). */
    check_file("\\DATA1_0.HD6;1", 1, 0, 8, 0);
    check_file("\\DATA1_0.DAT;1", 1, 0, 4, 0);
    check_file("\\DATA1_0.DAT;1", 1, 300000, 32, 0);
    check_file("\\DATA1_1.DAT;1", 1, 468000, 8, 0);
    check_file("\\MOVIE\\99\\STAFF_A.MVI;1", 1, 1000, 8, 0);
    /* The end of layer 0, around the layer break. */
    check_file("\\DATA0_0.DAT;1", 0, 0, 2, 0);
    check_file("\\DATA0_0.DAT;1", 0, 644666, 4, 0); /* its last 4 sectors */
    CHECK(sceCdLayerSearchFile(&f, "\\DATA1_0.DAT;1", 0) == 0); /* not on layer 0 */
    {
        /* Ten sectors across the layer break. DATA0_0.DAT ends at LSN 1646697; LSNs
         * 1646698..1646703 are in no file; LSNs 1646704.. are the layer-1 system area,
         * which the drive maps 16 sectors back onto layer 0: image 1646688.. = DATA0_0
         * sectors 644660.. */
        static uint8_t run[10 * S], want[2 * S], img[8 * S];
        int zero = 1;
        CHECK(sceCdRead(1646696, 10, run, NULL) == 1 && sceCdSync(0) == 0 && sceCdGetError() == 0);
        CHECK(read_data_file("DATA0_0.DAT", (uint64_t)644668 * S, want, 2 * S));
        CHECK(memcmp(run, want, 2 * S) == 0);
        for (size_t i = 2 * S; i < 8 * S; ++i) zero &= run[i] == 0;
        CHECK(zero);
        CHECK(read_data_file("DATA0_0.DAT", (uint64_t)644660 * S, want, 2 * S));
        CHECK(memcmp(run + 8 * S, want, 2 * S) == 0);
        if (g_iso) {
            CHECK(read_iso(1646696, img, 2)); /* below layer1_start: LSN = image sector */
            CHECK(memcmp(run, img, 2 * S) == 0);
            CHECK(read_iso(1646688, img, 2));
            CHECK(memcmp(run + 8 * S, img, 2 * S) == 0);
        }
        printf("ok  layer-break run LSN 1646696..1646705\n");
    }

    if (g_iso) {
        /* Independent check of the layer-1 rule: CDVDMAN reads the layer-1 PVD at LSN
         * layer1_start + 16; through the model that must be image sector 1646704, where
         * the image's second "CD001" volume descriptor is. */
        uint8_t pvd[S];
        uint32_t img = cdvd_lsn_to_image(cdvd_drive_disc(), l1 + 16);
        CHECK(img == 1646704);
        CHECK(read_iso(img, pvd, 1) && pvd[0] == 1 && memcmp(pvd + 1, "CD001", 5) == 0);
        /* The model serves such non-file sectors as zeros. */
        CHECK(sceCdRead(l1 + 16, 1, buf, NULL) == 1 && sceCdSync(0) == 0 && buf[0] == 0);
        fclose(g_iso);
    }
    sceCdHleUnmount();
    if (g_fail) {
        fprintf(stderr, "%d check(s) failed\n", g_fail);
        return 1;
    }
    printf("all real-data cdvd tests passed%s\n", iso && *iso ? " (with image checks)" : "");
    return 0;
}
