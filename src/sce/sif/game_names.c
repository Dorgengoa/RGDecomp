/* SPDX-License-Identifier: CC0-1.0 */
/* The SIF/fileio/libsdr entry points under the names the decompiled game calls them
 * by (census/platform_sdk_surface.tsv, boundary rows of libkernl sifrpc/iopheap/
 * loadfile/iopcontrol/fileio and libsdr). Their asm bodies are excluded from the
 * build (PLAN.md transform 6) and bound here. Functions the game calls by their Sony
 * names (sceSifBindRpc, sceSifCallRpc, sceSifSetDma, sceSifDmaStat,
 * sceSifInitIopHeap, sceSifAllocIopHeap, sceFsReset) are defined in sif_ee.c and
 * fileio.c directly. */
#include <stdarg.h>

#include "libsif.h"

void sceSifInitRpc_119b60(unsigned int mode) { sceSifInitRpc(mode); }
int sceSifFreeSysMemory_11ea40(void *addr) { return sceSifFreeIopHeap(addr); }
int sceSifLoadModule_11f7a0(const char *path, int argsz, const char *args) { return sceSifLoadModule(path, argsz, args); }
int sceSifSyncIop_11fc80(void) { return sceSifSyncIop(); }
int sceSifRebootIop_11fcd0(const char *img) { return sceSifRebootIop(img); }
int sceOpen_11b928(const char *name, int flags) { return sceOpen(name, flags); }
int sceClose_11bbb8(int fd) { return sceClose(fd); }
int sceLseek_11bd30(int fd, int offset, int whence) { return sceLseek(fd, offset, whence); }
int sceRead_11bf70(int fd, void *buf, int nbyte) { return sceRead(fd, buf, nbyte); }
int sceWrite_11c1e0(int fd, const void *buf, int nbyte) { return sceWrite(fd, buf, nbyte); }
int sceSdRemoteInit_122890(int unused) { return sceSdRemoteInit(unused); }
int sceSdRemoteCallbackInit_122d70(int priority) { return sceSdRemoteCallbackInit(priority); }
void sceSdRemoteCallbackQuit_122e70(void) { sceSdRemoteCallbackQuit(); }

/* Variadic forwarder: sceSdRemote reads at most six words after `command`. */
int sceSdRemote_1229e8(int sync, int command, ...)
{
    va_list ap;
    unsigned a[6];
    va_start(ap, command);
    for (int i = 0; i < 6; i++)
        a[i] = va_arg(ap, unsigned);
    va_end(ap);
    return sceSdRemote(sync, command, a[0], a[1], a[2], a[3], a[4], a[5]);
}
