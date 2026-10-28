/* SPDX-License-Identifier: CC0-1.0 */
/* EE libmc reimplemented over the mcserv HLE (src/ps2/padmc). docs/PADMC.md.
 *
 * Retail semantics kept (from the asm in game/src/main/{sdk,sys,thread}/sceMc*.c):
 * every operation is asynchronous and returns 0 when issued; at most one is in
 * flight (a lock semaphore, taken at issue and given back by sceMcSync when the
 * result is collected: a second issue before that returns -200); sceMcSync(0)
 * blocks, sceMcSync(1) polls (0 = still running, 1 = done, -1 = nothing issued)
 * and reports the function number in *cmd and the result in *result. sceMcInit
 * creates the two semaphores, sceMcEnd deletes them (their ids are visible to the
 * game, as on retail). Operations complete on the virtual clock: SIF RPC latency
 * plus the card time mcserv reports for the operation. */
#ifndef SCE_LIBMC_H
#define SCE_LIBMC_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct sceMcStDateTime {
    unsigned char Resv2, Sec, Min, Hour, Day, Month;
    unsigned short Year;
} sceMcStDateTime;

typedef struct sceMcTblGetDir {
    sceMcStDateTime _Create;
    sceMcStDateTime _Modify;
    unsigned int FileSizeByte;
    unsigned short AttrFile;
    unsigned short Reserve1;
    unsigned int Reserve2;
    unsigned int PdaAplNo;
    unsigned char EntryName[32];
} sceMcTblGetDir; /* 64 bytes */

/* sceMcSync *cmd values (libmc function numbers) */
#define sceMcFuncNoCardInfo 1
#define sceMcFuncNoOpen     2
#define sceMcFuncNoClose    3
#define sceMcFuncNoSeek     4
#define sceMcFuncNoRead     5
#define sceMcFuncNoWrite    6
#define sceMcFuncNoFlush    10
#define sceMcFuncNoMkdir    11
#define sceMcFuncNoChDir    12
#define sceMcFuncNoGetDir   13
#define sceMcFuncNoFileInfo 14
#define sceMcFuncNoDelete   15
#define sceMcFuncNoFormat   16
#define sceMcFuncNoUnformat 17
#define sceMcFuncNoEntSpace 18
#define sceMcFuncNoRename   19

/* sceMcSync return values */
#define sceMcExecIdle   (-1)
#define sceMcExecRun    0
#define sceMcExecFinish 1

/* issue-time errors */
#define sceMcErrNoInit   (-100) /* sceMcInit has not bound mcserv */
#define sceMcErrBusy     (-200) /* previous operation not yet collected by sceMcSync */
#define sceMcErrBadName  (-210)
#define sceMcErrRpc      (-91)
#define sceMcIniErrKernel (-101)
#define sceMcIniOldMcserv (-120)
#define sceMcIniOldMcman  (-121)

int sceMcInit(void);
int sceMcEnd(void);
int sceMcSync(int mode, int *cmd, int *result);
int sceMcGetInfo(int port, int slot, int *type, int *free, int *format);
int sceMcOpen(int port, int slot, const char *name, int mode);
int sceMcClose(int fd);
int sceMcSeek(int fd, int offset, int origin);
int sceMcRead(int fd, void *buff, int size);
int sceMcWrite(int fd, const void *buff, int size);
int sceMcFlush(int fd);
int sceMcMkdir(int port, int slot, const char *name);
int sceMcChdir(int port, int slot, const char *newDir, char *currentDir);
int sceMcGetDir(int port, int slot, const char *name, unsigned int mode, int maxent, sceMcTblGetDir *table);
int sceMcSetFileInfo(int port, int slot, const char *name, const sceMcTblGetDir *info, unsigned int valid);
int sceMcRename(int port, int slot, const char *oldName, const char *newName);
int sceMcDelete(int port, int slot, const char *name);
int sceMcFormat(int port, int slot);
int sceMcUnformat(int port, int slot);
int sceMcGetEntSpace(int port, int slot, const char *path);
int sceMcGetSlotMax(int port);

/* ---- port controls ------------------------------------------------------------ */
typedef struct rg_mc_config {
    uint32_t poll_cycles; /* virtual cycles sceMcSync(1) charges while busy (default 2000) */
    int timing;           /* 1 (default): complete after mcserv's card time; 0: at RPC latency */
} rg_mc_config;
void rg_mc_default_config(rg_mc_config *c);
void rg_mc_configure(const rg_mc_config *c);
/* mccard clock that follows the virtual clock: 2006-01-31 12:00:00 + ps2k_now(). */
struct mc_datetime;
void rg_mc_virtual_clock(void *user, struct mc_datetime *out);
/* Forget the libmc state (unbound, no semaphores, nothing pending), e.g. after a
 * new rg_sif_boot / ps2k_init. */
void rg_mc_reset(void);
/* For tests: lock/done sema ids (-1 when not initialised) and the pending cmd. */
void rg_mc_debug_state(int *lock_sema, int *done_sema, int *pending_cmd);

/* ---- game-tree names (census/platform_sdk_surface.tsv); sceMcMkdir keeps its name -- */
int sceMcInit_12c648(void);
int sceMcEnd_12c870(void);
int sceMcGetSlotMax_12c998(int port);
int sceMcOpen_12ca58(int port, int slot, const char *name, int mode);
int sceMcClose_12cbb8(int fd);
int sceMcSeek_12cc78(int fd, int offset, int origin);
int sceMcRead_12ce08(int fd, void *buff, int size);
int sceMcWrite_12cf20(int fd, const void *buff, int size);
int sceMcSync_12d098(int mode, int *cmd, int *result);
int sceMcGetInfo_12d1b8(int port, int slot, int *type, int *free, int *format);
int sceMcGetDir_12d3a8(int port, int slot, const char *name, unsigned int mode, int maxent, sceMcTblGetDir *table);
int sceMcChdir_12d588(int port, int slot, const char *newDir, char *currentDir);
int sceMcFormat_12d6c8(int port, int slot);
int sceMcDelete_12d798(int port, int slot, const char *name);
int sceMcFlush_12d8b8(int fd);
int sceMcSetFileInfo_12d978(int port, int slot, const char *name, const sceMcTblGetDir *info, unsigned int valid);
int sceMcRename_12db48(int port, int slot, const char *oldName, const char *newName);
int sceMcUnformat_12dca0(int port, int slot);
int sceMcGetEntSpace_12dd70(int port, int slot, const char *path);

#ifdef __cplusplus
}
#endif
#endif
