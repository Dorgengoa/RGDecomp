/* SPDX-License-Identifier: CC0-1.0 */
/* The libcdvd entry points under the names the decompiled game calls them by
 * (census/platform_sdk_surface.tsv, family libcdvd, boundary functions). Their asm
 * bodies are excluded from the build (PLAN.md transform 6) and bound here. sceCdSync and
 * sceCdDiskReady keep Sony's names in the game and are defined in libcdvd.c. */
#include "libcdvd.h"

void *sceCdPOffCallback_129690(void (*func)(void *), void *userdata) { return sceCdPOffCallback(func, userdata); }
int sceCdLayerSearchFile_1297e0(sceCdlFILE *fp, const char *name, int layer) {
    return sceCdLayerSearchFile(fp, name, layer);
}
int sceCdSearchFile_129ae0(sceCdlFILE *fp, const char *name) { return sceCdSearchFile(fp, name); }
/* The game passes three extra (unused) arguments: sceCdInit_12a008(0, p1, p2, p3). */
int sceCdInit_12a008(int mode) { return sceCdInit(mode); }
/* Disk-ready check over CDVDFSV 0x8000059C, used where sceCdDiskReady(0) would be. */
int CdDiskReadyNewMaybe_12a508(int mode) { return sceCdDiskReady(mode); }
int sceCdRead_12a728(uint32_t lsn, uint32_t sectors, void *buf, sceCdRMode *mode) {
    return sceCdRead(lsn, sectors, buf, mode);
}
int sceCdSeek_12a908(uint32_t lsn) { return sceCdSeek(lsn); }
int sceCdGetDiskType_12a9d8(void) { return sceCdGetDiskType(); }
int sceCdGetError_12aa98(void) { return sceCdGetError(); }
int sceCdChangeThreadPriority_12ab30(int priority) { return sceCdChangeThreadPriority(priority); }
int sceCdReadDvdDualInfo_12acd0(int *on_dual, uint32_t *layer1_start) {
    return sceCdReadDvdDualInfo(on_dual, layer1_start);
}
int sceCdMmode_12ada0(int media) { return sceCdMmode(media); }
int sceCdTrayReq_12ae98(int param, uint32_t *traychk) { return sceCdTrayReq(param, traychk); }
