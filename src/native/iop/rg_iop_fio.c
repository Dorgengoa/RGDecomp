/* SPDX-License-Identifier: CC0-1.0 */
/* Native libkernl fileio host files (docs/NATIVE-IOP.md): the device mapping and the
 * stdio calls FILEIO 0x80000001 made on the IOP, as a plain host service.  The native
 * sceOpen/... (src/sce/sif/fileio.c, RG_IOP=native) call it directly; the FILEIO HLE
 * server (src/ps2/iop/iop_hle.c, the oracle) calls the same functions, so both paths
 * map names and flags identically. */
#include "rg_iop.h"
#include "rg_iop_fio.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _WIN32
#include <dirent.h>
#include <strings.h>
#include <sys/stat.h>
#endif

#define FIO_MAX 32
static struct {
    char cdrom_root[512];
    char host_root[512];
    int roots_set;
    FILE *f[FIO_MAX];
} F;

/* SCE open flags */
#define SCE_RDONLY 0x0001
#define SCE_WRONLY 0x0002
#define SCE_RDWR   0x0003
#define SCE_APPEND 0x0100
#define SCE_CREAT  0x0200
#define SCE_TRUNC  0x0400

/* PS2 names are case-insensitive (ISO 9660 / host0: on Windows); Linux file systems
 * are not.  When the exact path is missing, resolve each component by a
 * case-insensitive directory scan (docs/LINUX.md).  Windows: plain fopen. */
#ifdef _WIN32
static FILE *fopen_ci(const char *path, const char *mode) { return fopen(path, mode); }
#else
static int resolve_ci(const char *path, char *out, size_t cap)
{
    size_t n = 0;
    const char *p = path;
    if (*p == '/') {
        out[n++] = '/';
        while (*p == '/')
            p++;
    }
    out[n] = 0;
    while (*p) {
        const char *e = strchr(p, '/');
        size_t len = e ? (size_t)(e - p) : strlen(p);
        if (n + len + 2 > cap)
            return -1;
        memcpy(out + n, p, len);
        out[n + len] = 0;
        struct stat st;
        if (stat(out, &st) != 0) {
            char saved = out[n];
            out[n] = 0;
            DIR *d = opendir(n ? out : ".");
            out[n] = saved;
            int found = 0;
            if (d) {
                struct dirent *de;
                while ((de = readdir(d)) != NULL)
                    if (strlen(de->d_name) == len && strncasecmp(de->d_name, p, len) == 0) {
                        memcpy(out + n, de->d_name, len);
                        found = 1;
                        break;
                    }
                closedir(d);
            }
            if (!found) {
                size_t rest = strlen(p);
                if (n + rest + 1 > cap)
                    return -1;
                memcpy(out + n, p, rest + 1);
                return 0;
            }
        }
        n += len;
        if (!e)
            break;
        out[n++] = '/';
        out[n] = 0;
        p = e;
        while (*p == '/')
            p++;
    }
    out[n] = 0;
    return 0;
}

static FILE *fopen_ci(const char *path, const char *mode)
{
    FILE *f = fopen(path, mode);
    char fixed[1024];
    if (!f && errno == ENOENT && resolve_ci(path, fixed, sizeof fixed) == 0 && strcmp(fixed, path) != 0)
        f = fopen(fixed, mode);
    return f;
}
#endif

void rg_fio_set_roots(const char *cdrom_root, const char *host_root)
{
    rg_fio_reset();
    snprintf(F.cdrom_root, sizeof F.cdrom_root, "%s", cdrom_root ? cdrom_root : "data");
    snprintf(F.host_root, sizeof F.host_root, "%s", host_root ? host_root : F.cdrom_root);
    F.roots_set = 1;
}

void rg_fio_reset(void)
{
    for (int i = 0; i < FIO_MAX; i++)
        if (F.f[i]) {
            fclose(F.f[i]);
            F.f[i] = NULL;
        }
}

int rg_fio_map_path(const char *in, char *out, size_t outsz)
{
    if (!F.roots_set)
        rg_fio_set_roots(getenv("RG_DATA"), NULL);
    const char *colon = strchr(in, ':');
    const char *root;
    const char *rest;
    if (!colon) {
        root = F.host_root;
        rest = in;
    } else {
        size_t dl = (size_t)(colon - in);
        if (dl >= 5 && strncmp(in, "cdrom", 5) == 0)
            root = F.cdrom_root;
        else if (dl >= 4 && strncmp(in, "host", 4) == 0)
            root = F.host_root;
        else
            return -1;
        rest = colon + 1;
    }
    while (*rest == '\\' || *rest == '/')
        rest++;
    size_t n = (size_t)snprintf(out, outsz, "%s/", root);
    for (; *rest && n + 1 < outsz; rest++) {
        if (*rest == ';')
            break; /* ISO version suffix */
        out[n++] = (*rest == '\\') ? '/' : *rest;
    }
    out[n] = 0;
    return 0;
}

static FILE *fd_file(int fd) { return (fd >= 0 && fd < FIO_MAX) ? F.f[fd] : NULL; }

int rg_fio_open(const char *name, int flags)
{
    char path[1024];
    if (!name || rg_fio_map_path(name, path, sizeof path) < 0)
        return -ENODEV;
    const char *mode = "rb";
    int acc = flags & 3;
    if (acc == SCE_WRONLY || acc == SCE_RDWR) {
        if (flags & SCE_TRUNC)
            mode = acc == SCE_RDWR ? "w+b" : "wb";
        else if (flags & SCE_APPEND)
            mode = "ab";
        else
            mode = "r+b";
    }
    FILE *nf = fopen_ci(path, mode);
    if (!nf && (flags & SCE_CREAT) && acc != SCE_RDONLY)
        nf = fopen_ci(path, "w+b");
    if (!nf)
        return -ENOENT;
    for (int i = 1; i < FIO_MAX; i++)
        if (!F.f[i]) {
            F.f[i] = nf;
            return i;
        }
    fclose(nf);
    return -EMFILE;
}

int rg_fio_close(int fd)
{
    FILE *f = fd_file(fd);
    if (!f)
        return -EBADF;
    fclose(f);
    F.f[fd] = NULL;
    return 0;
}

int rg_fio_read(int fd, void *buf, int nbyte)
{
    FILE *f = fd_file(fd);
    if (!f)
        return -EBADF;
    if (nbyte <= 0 || !buf)
        return 0;
    return (int)fread(buf, 1, (size_t)nbyte, f);
}

int rg_fio_write(int fd, const void *buf, int nbyte)
{
    FILE *f = fd_file(fd);
    if (!f)
        return -EBADF;
    if (nbyte <= 0 || !buf)
        return 0;
    return (int)fwrite(buf, 1, (size_t)nbyte, f);
}

int rg_fio_lseek(int fd, int offset, int whence)
{
    FILE *f = fd_file(fd);
    if (!f)
        return -EBADF;
    if (fseek(f, offset, whence == 2 ? SEEK_END : whence == 1 ? SEEK_CUR : SEEK_SET) != 0)
        return -EINVAL;
    return (int)ftell(f);
}
