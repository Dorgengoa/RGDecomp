/* SPDX-License-Identifier: CC0-1.0 */
/* Read-only access to the game's own archives for the sound tools and tests (not part
 * of the runtime HLE, which only sees what the game uploads):
 *   DATAx_y.HD6 index + DATAx_y.DAT data (HD6 record: one LE u64 =
 *     name-stream offset bits 0-17 | 2048-byte sector bits 18-37 | size/4 bits 38-63;
 *     names are VLQ token-id strings into a NUL-separated token table),
 *   .snd packs: entries { char name[0x40]; u32 header (0x50); u32 size; u32 next }
 *     holding NAME.hd, NAME.bd, NAME_nnn.sq, .cfg, .vol, .mid. */
#ifndef RG_SND_PACK_H
#define RG_SND_PACK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct snd_arc_file {
    char path[128];
    uint64_t offset;
    uint32_t size;
} snd_arc_file;

typedef struct snd_archive {
    char dat_path[512];
    snd_arc_file *files;
    int nfiles;
} snd_archive;

int snd_archive_open(snd_archive *a, const char *hd6_path, const char *dat_path); /* 0 ok */
void snd_archive_close(snd_archive *a);
/* Case-insensitive, '/' and '\\' equivalent. NULL if absent. */
const snd_arc_file *snd_archive_find(const snd_archive *a, const char *path);
/* malloc'd copy of the file (free() it), NULL on error. */
uint8_t *snd_archive_read(const snd_archive *a, const snd_arc_file *f);
/* Search DATA0_0, DATA0_1, DATA1_0, DATA1_1 under data_dir; returns malloc'd bytes. */
uint8_t *snd_data_load(const char *data_dir, const char *path, uint32_t *size);

typedef struct snd_pack_entry {
    char name[64];
    uint32_t offset, size; /* body inside the pack */
} snd_pack_entry;
/* List the entries of a .snd pack; returns the count (<= max). */
int snd_pack_list(const uint8_t *d, uint32_t size, snd_pack_entry *out, int max);
/* First entry whose name ends with `suffix` (case-insensitive), or NULL. */
const snd_pack_entry *snd_pack_find(const snd_pack_entry *e, int n, const char *suffix);

#ifdef __cplusplus
}
#endif
#endif
