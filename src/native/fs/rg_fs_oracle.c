/* SPDX-License-Identifier: CC0-1.0
 * rg_fs oracle: re-reads every native file read through the old CDVD sector model
 * (src/ps2/cdvd: MANIFEST.tsv -> LSN -> sectors) and compares the bytes.  Check
 * mode only (RG_FS_ORACLE=1, docs/NATIVE-FS.md "Oracle"); the default game path
 * never touches the sector model.  The comparison runs inside the read hook, on
 * the reading thread. */
#include "rg_fs_oracle.h"

#include "cdvd.h"
#include "rg_fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct {
    cdvd_disc *disc;
    uint64_t checked, bytes, mismatched, unmapped, skipped;
    int reported;
    uint8_t *tmp;
    size_t tmpn;
} O;

static void on_read(void *user, int h, const char *path, int64_t off, int64_t len, int64_t got,
                    const void *buf)
{
    cdvd_file_info fi;
    uint32_t lsn, first, count, unm = 0;
    int64_t skip;
    size_t need;
    (void)user;
    (void)h;
    if (!O.disc || !path || len <= 0 || got < 0)
        return;
    if (!cdvd_disc_find(O.disc, path, 0, &fi) && !cdvd_disc_find(O.disc, path, 1, &fi)) {
        O.skipped++; /* not a disc file (host-only) */
        return;
    }
    lsn = fi.lsn[0] != CDVD_NO_LSN ? fi.lsn[0] : fi.lsn[1];
    /* the sector model can only serve whole sectors inside the file's own sector run
     * (reads past it would continue into the next file, which the native read
     * zero-fills; the game's sector reads never go there) */
    first = (uint32_t)(off / 2048);
    skip = off - (int64_t)first * 2048;
    count = (uint32_t)((skip + len + 2047) / 2048);
    if ((uint64_t)first + count > (fi.size + 2047) / 2048) {
        uint64_t nsect = (fi.size + 2047) / 2048;
        if (first >= nsect) {
            O.skipped++;
            return;
        }
        count = (uint32_t)(nsect - first);
        if ((int64_t)count * 2048 - skip < len)
            len = (int64_t)count * 2048 - skip; /* compare the in-file part only */
    }
    need = (size_t)count * 2048;
    if (need > O.tmpn) {
        uint8_t *t = (uint8_t *)realloc(O.tmp, need);
        if (!t)
            return;
        O.tmp = t;
        O.tmpn = need;
    }
    if (cdvd_disc_read(O.disc, lsn + first, count, O.tmp, &unm) != CDVD_OK) {
        O.mismatched++;
        if (O.reported++ < 16)
            fprintf(stderr, "rg_fs oracle: %s +0x%llx: sector model read failed\n", path,
                    (unsigned long long)off);
        return;
    }
    O.unmapped += unm;
    O.checked++;
    O.bytes += (uint64_t)len;
    if (memcmp(O.tmp + skip, buf, (size_t)len) != 0) {
        int64_t i = 0;
        while (i < len && O.tmp[skip + i] == ((const uint8_t *)buf)[i])
            i++;
        O.mismatched++;
        if (O.reported++ < 16)
            fprintf(stderr,
                    "rg_fs oracle: MISMATCH %s +0x%llx len 0x%llx (LSN %u): first diff at +0x%llx\n",
                    path, (unsigned long long)off, (unsigned long long)len, lsn + first,
                    (unsigned long long)i);
    }
}

int rg_fs_oracle_start(const char *data_dir)
{
    char err[256];
    if (O.disc)
        return 1;
    O.disc = cdvd_disc_open(data_dir, err, sizeof err);
    if (!O.disc) {
        fprintf(stderr, "rg_fs oracle: cannot open the sector model: %s\n", err);
        return 0;
    }
    rg_fs_add_read_hook(on_read, NULL);
    fprintf(stderr, "rg_fs oracle: on (every read is compared with the CDVD sector model)\n");
    return 1;
}

void rg_fs_oracle_get(rg_fs_oracle_stats *out)
{
    out->checked = O.checked;
    out->bytes = O.bytes;
    out->mismatched = O.mismatched;
    out->skipped = O.skipped;
    out->unmapped_sectors = O.unmapped;
}

void rg_fs_oracle_stop(void)
{
    if (!O.disc)
        return;
    rg_fs_remove_read_hook(on_read, NULL);
    fprintf(stderr,
            "rg_fs oracle: %llu reads (%llu bytes) compared, %llu mismatched, %llu skipped, "
            "%llu unmapped sectors\n",
            (unsigned long long)O.checked, (unsigned long long)O.bytes,
            (unsigned long long)O.mismatched, (unsigned long long)O.skipped,
            (unsigned long long)O.unmapped);
    cdvd_disc_close(O.disc);
    free(O.tmp);
    memset(&O, 0, sizeof O);
}
