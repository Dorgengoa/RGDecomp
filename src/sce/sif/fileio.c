/* SPDX-License-Identifier: CC0-1.0 */
/* libkernl fileio (sceOpen/sceClose/sceRead/sceWrite/sceLseek/sceFsReset) over the
 * FILEIO HLE server 0x80000001. The request layout is the port's own (iop_fio_req,
 * src/ps2/iop/iop.h): both ends are host code. Reads arrive by SIF0 write straight
 * into the caller's EE buffer, as the retail server's DMA does. */
#include <string.h>

#include "iop.h"
#include "libsif.h"
#include "sif.h"
#include "sif_internal.h"
#include "rg_iop_fio.h" /* RG_IOP=native: the host files directly (docs/NATIVE-IOP.md) */

#define FIO_SID 0x80000001u

#if RG_IOP_ORACLE /* RG_NATIVE_ONLY: no FILEIO client (docs/NATIVE-ONLY.md) */
static int g_fio_inited;
static iop_fio_req g_req;

void fio_reset_client(void) { g_fio_inited = 0; }

static int fio_init(void)
{
    if (g_fio_inited)
        return 0;
    sif_ee_ensure_boot();
    uint32_t tok;
    if (sif_rpc_bind(FIO_SID, &tok) < 0)
        return -1;
    int32_t r = 0;
    uint32_t init[4] = {0, 0, 0, 0}; /* g_req may already hold the caller's request */
    sif_ee_rpc_sync(FIO_SID, IOP_FIO_INIT, init, 16, &r, 4);
    g_fio_inited = 1;
    return 0;
}

static int fio_call(uint32_t fno, uint32_t ssize)
{
    int32_t r = -1;
    if (fio_init() < 0)
        return -1;
    if (sif_ee_rpc_sync(FIO_SID, fno, &g_req, ssize, &r, 4) < 0)
        return -1;
    return r;
}
#endif

int sceOpen(const char *name, int flags, ...)
{
    RG_IOP_API("sceOpen");
    if (rg_iop_native())
        return rg_fio_open(name, flags);
#if RG_IOP_ORACLE
    memset(&g_req, 0, sizeof g_req);
    g_req.a = flags;
    if (name)
        strncpy(g_req.name, name, sizeof g_req.name - 1);
    return fio_call(IOP_FIO_OPEN, (uint32_t)sizeof g_req);
#endif
}

int sceClose(int fd)
{
    RG_IOP_API("sceClose");
    if (rg_iop_native())
        return rg_fio_close(fd);
#if RG_IOP_ORACLE
    memset(&g_req, 0, 16);
    g_req.fd = fd;
    return fio_call(IOP_FIO_CLOSE, 16);
#endif
}

int sceRead(int fd, void *buf, int nbyte)
{
    RG_IOP_API("sceRead");
    if (rg_iop_native())
        return rg_fio_read(fd, buf, nbyte);
#if RG_IOP_ORACLE
    memset(&g_req, 0, 16);
    g_req.fd = fd;
    g_req.a = nbyte;
    g_req.ee_buf = (uint32_t)(uintptr_t)buf;
    return fio_call(IOP_FIO_READ, 16);
#endif
}

int sceWrite(int fd, const void *buf, int nbyte)
{
    RG_IOP_API("sceWrite");
    if (rg_iop_native())
        return rg_fio_write(fd, buf, nbyte);
#if RG_IOP_ORACLE
    memset(&g_req, 0, 16);
    g_req.fd = fd;
    g_req.a = nbyte;
    g_req.ee_buf = (uint32_t)(uintptr_t)buf;
    return fio_call(IOP_FIO_WRITE, 16);
#endif
}

int sceLseek(int fd, int offset, int whence)
{
    RG_IOP_API("sceLseek");
    if (rg_iop_native())
        return rg_fio_lseek(fd, offset, whence);
#if RG_IOP_ORACLE
    memset(&g_req, 0, 16);
    g_req.fd = fd;
    g_req.a = offset;
    g_req.b = whence;
    return fio_call(IOP_FIO_LSEEK, 16);
#endif
}

int sceFsReset(void)
{
    RG_IOP_API("sceFsReset");
#if RG_IOP_ORACLE
    g_fio_inited = 0;
#endif
    return 0;
}
