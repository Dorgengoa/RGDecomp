/* SPDX-License-Identifier: CC0-1.0
 * rg_fs oracle (check mode): compares every native read with the CDVD sector model.
 * See rg_fs_oracle.c and docs/NATIVE-FS.md "Oracle". */
#ifndef RG_NATIVE_FS_ORACLE_H
#define RG_NATIVE_FS_ORACLE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rg_fs_oracle_stats {
    uint64_t checked, bytes, mismatched, skipped, unmapped_sectors;
} rg_fs_oracle_stats;

/* Opens data_dir/MANIFEST.tsv as the sector model and hooks rg_fs reads.  1 = on. */
int rg_fs_oracle_start(const char *data_dir);
void rg_fs_oracle_get(rg_fs_oracle_stats *out);
/* Prints the summary, unhooks, closes the model. */
void rg_fs_oracle_stop(void);

#ifdef __cplusplus
}
#endif
#endif
