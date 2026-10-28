/* SPDX-License-Identifier: CC0-1.0 */
/* libcdvd (EE) surface the game calls, reimplemented over the CDVD model in
 * src/ps2/cdvd (docs/CDVD.md). Names, structures and constants follow Sony's libcdvd;
 * the values were checked against ps2sdk's libcdvd-common.h (AFL, used as a reference
 * only; nothing is copied). */
#ifndef RG_SCE_LIBCDVD_H
#define RG_SCE_LIBCDVD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* File found by sceCdSearchFile. Sony's EE libcdvd copies 0x24 bytes (lsn, size,
 * name, date, flag) out of the CDVDFSV reply, so the structure is 36 bytes. */
typedef struct sceCdlFILE {
    uint32_t lsn;  /* first sector, in the LSN space sceCdRead takes */
    uint32_t size; /* bytes */
    char name[16]; /* "NAME.EXT;1" (truncated to 15 characters) */
    uint8_t date[8];
    uint32_t flag;
} sceCdlFILE;

typedef struct sceCdRMode {
    uint8_t trycount;
    uint8_t spindlctrl;
    uint8_t datapattern; /* SCECdSecS2048 only */
    uint8_t pad;
} sceCdRMode;

typedef void (*sceCdCBFunc)(int reason);

enum { SCECdSecS2048 = 0, SCECdSecS2328 = 1, SCECdSecS2340 = 2 };
enum { SCECdINIT = 0x00, SCECdINoD = 0x01, SCECdEXIT = 0x05 };
enum { SCECdMmodeCd = 1, SCECdMmodeDvd = 2 };
enum { SCECdNODISC = 0x00, SCECdPS2DVD = 0x14 };
enum { SCECdComplete = 0x02, SCECdNotReady = 0x06 };
enum { SCECdTrayOpen = 0, SCECdTrayClose = 1, SCECdTrayCheck = 2 };
enum {
    SCECdFuncRead = 1,
    SCECdFuncSeek = 4,
};
enum {
    SCECdErNO = 0x00,
    SCECdErABRT = 0x01,
    SCECdErNODISC = 0x12,
    SCECdErIPI = 0x20,
    SCECdErPRM = 0x22,
    SCECdErREAD = 0x30,
    SCECdErTRMOPN = 0x31,
};

/* ---- port-side setup (not Sony API) ---- */

/* Mounts the extracted data folder (holding MANIFEST.tsv) as the disc in the drive.
 * Returns 1 on success. sceCdInit mounts $RG_DATA, else "data", if nothing is mounted. */
int sceCdHleMount(const char *data_dir);
void sceCdHleUnmount(void);
/* Runs the callback registered with sceCdPOffCallback (host shutdown). */
void sceCdHlePowerOff(void);
/* Read observer (timing record, docs/TIMING-LOCKSTEP.md): called on every
 * sceCdRead (the game's sceCdRead_12a728 included) before the drive command is
 * issued.  NULL removes it.  One observer. */
typedef void (*sceCdHleReadHook)(void *user, uint32_t lsn, uint32_t sectors, void *buf, int pattern);
void sceCdHleSetReadHook(sceCdHleReadHook fn, void *user);

/* ---- libcdvd ---- */
int sceCdInit(int mode);
int sceCdMmode(int media);
int sceCdChangeThreadPriority(int priority);
int sceCdGetDiskType(void);
int sceCdDiskReady(int mode);
int sceCdTrayReq(int param, uint32_t *traychk);
int sceCdReadDvdDualInfo(int *on_dual, uint32_t *layer1_start);
int sceCdSearchFile(sceCdlFILE *fp, const char *name);
int sceCdLayerSearchFile(sceCdlFILE *fp, const char *name, int layer);
int sceCdRead(uint32_t lsn, uint32_t sectors, void *buf, sceCdRMode *mode);
int sceCdSeek(uint32_t lsn);
int sceCdSync(int mode);
int sceCdGetError(void);
int sceCdBreak(void);
sceCdCBFunc sceCdCallback(sceCdCBFunc func);
void *sceCdPOffCallback(void (*func)(void *), void *userdata);

#ifdef __cplusplus
}
#endif
#endif
