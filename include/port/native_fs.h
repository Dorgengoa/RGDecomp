/* SPDX-License-Identifier: CC0-1.0
 * Game-side view of the native file service (src/native/fs/rg_fs.h,
 * docs/NATIVE-FS.md), for the overrides of the game's file layer.  Plain C types
 * only, so it can be included next to the game's types.h. */
#ifndef RG_PORT_NATIVE_FS_H
#define RG_PORT_NATIVE_FS_H

#ifdef __cplusplus
extern "C" {
#endif

int rg_fs_open(const char *name);
int rg_fs_open_or_die(const char *name, const char *who);
long long rg_fs_size(int h);
const char *rg_fs_name(int h);
long long rg_fs_read_fill(int h, long long off, void *buf, long long len);

#ifdef __cplusplus
}
#endif
#endif
