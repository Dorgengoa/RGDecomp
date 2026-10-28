/* SPDX-License-Identifier: CC0-1.0 */
/* Native fileio host files (docs/NATIVE-IOP.md): `cdrom0:\X;1` -> <cdrom_root>/X,
 * `host0:X` / bare names -> <host_root>/X (host_root defaults to cdrom_root),
 * other devices -ENODEV.  Results follow the FILEIO convention: fd >= 1, or a
 * negative errno (-ENOENT, -EBADF, -EMFILE, -EINVAL, -ENODEV).  SCE open flags
 * RDONLY/WRONLY/RDWR (1/2/3), APPEND 0x100, CREAT 0x200, TRUNC 0x400. */
#ifndef RG_NATIVE_IOP_FIO_H
#define RG_NATIVE_IOP_FIO_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif

void rg_fio_set_roots(const char *cdrom_root, const char *host_root); /* closes open files */
void rg_fio_reset(void);                                               /* close every file */
int rg_fio_map_path(const char *in, char *out, size_t outsz);          /* 0 ok, -1 device */
int rg_fio_open(const char *name, int flags);
int rg_fio_close(int fd);
int rg_fio_read(int fd, void *buf, int nbyte);
int rg_fio_write(int fd, const void *buf, int nbyte);
int rg_fio_lseek(int fd, int offset, int whence);

#ifdef __cplusplus
}
#endif
#endif
