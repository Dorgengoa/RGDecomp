/* SPDX-License-Identifier: CC0-1.0 */
/* EE-side SIF SDK surface (sifcmd, sifrpc, SIF DMA, iopheap, loadfile, iopcontrol,
 * fileio, libsdr sdremote) over the SIF core in src/ps2/sif and the HLE IOP servers
 * in src/ps2/iop. Names and signatures follow census/platform_sdk_surface.tsv and
 * the game's declarations; struct layouts follow the SDK (32-bit fields, i686).
 * Written from scratch; see docs/SIF.md. */
#ifndef SCE_LIBSIF_H
#define SCE_LIBSIF_H

#include <stdint.h>
/* x64 (docs/X64-PLAN.md): SDK structs live in game memory with 4-byte pointers */
#ifndef SCE_P32
#if defined(_WIN64)
#define SCE_P32 __ptr32 __uptr
#else
#define SCE_P32
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ---- structs (SDK layout) ------------------------------------------------- */
typedef struct sceSifDmaData {
    unsigned int data; /* EE address */
    unsigned int addr; /* IOP address */
    unsigned int size;
    unsigned int mode;
} sceSifDmaData;

typedef void (*sceSifEndFunc)(void *);
typedef void *(*sceSifRpcFunc)(unsigned int fno, void *data, int size);
typedef void (*sceSifCmdHandler)(void *pkt, void *data);

typedef struct sceSifRpcData {
    void * SCE_P32 paddr;
    unsigned int pid;
    int tid;
    unsigned int mode;
} sceSifRpcData;

struct sceSifServeData;
typedef struct sceSifClientData {
    sceSifRpcData rpcd;            /* 0x00 */
    unsigned int command;          /* 0x10 */
    void * SCE_P32 buff;           /* 0x14 server receive buffer (IOP address) */
    void * SCE_P32 cbuff;          /* 0x18 */
    sceSifEndFunc SCE_P32 func;    /* 0x1C */
    void * SCE_P32 para;           /* 0x20 */
    struct sceSifServeData * SCE_P32 serve; /* 0x24 non-NULL once bound (the game polls it) */
} sceSifClientData;

typedef struct sceSifServeData {
    unsigned int command;          /* sid */
    sceSifRpcFunc SCE_P32 func;
    void * SCE_P32 buff;
    int size;
    sceSifRpcFunc SCE_P32 cfunc;
    void * SCE_P32 cbuff;
    int csize;
    sceSifClientData * SCE_P32 client;
    void * SCE_P32 paddr;
    unsigned int fno;
    void * SCE_P32 receive;
    int rsize;
    int rmode;
    unsigned int rid;
    struct sceSifServeData * SCE_P32 link;
    struct sceSifServeData * SCE_P32 next;
    struct sceSifQueueData * SCE_P32 base;
} sceSifServeData;

typedef struct sceSifQueueData {
    int key;     /* thread id */
    int active;
    struct sceSifServeData * SCE_P32 link;
    struct sceSifServeData * SCE_P32 start;
    struct sceSifServeData * SCE_P32 end;
    struct sceSifQueueData * SCE_P32 next;
} sceSifQueueData;

#define SIF_RPCM_NOWAIT 0x01
#define SIF_RPCM_NOWBDC 0x02

/* ---- port setup ------------------------------------------------------------ */
typedef struct rg_sif_boot_config {
    const char *cdrom_root;       /* FILEIO "cdrom0:\" root; NULL -> env RG_DATA or "data" */
    const char *host_root;        /* "host0:" root; NULL -> cdrom_root */
    int install_sound_placeholders; /* default 1 */
    uint64_t rpc_latency, dma_setup, dma_cycles_per_qword, boot_latency; /* cycles, default 0 */
    int use_kernel;               /* 1 (default): deliver completions through ps2k DMAC SIF0 */
} rg_sif_boot_config;
void rg_sif_default_boot_config(rg_sif_boot_config *cfg);
/* Reset SIF + IOP, register the HLE servers, wire the kernel hooks. Call after
 * ps2k_init (or let the first sceSifInitRpc/sceSifInitCmd do it with defaults). */
int rg_sif_boot(const rg_sif_boot_config *cfg);
int rg_sif_booted(void);

/* ---- sifcmd -------------------------------------------------------------------- */
void sceSifInitCmd(void);
void sceSifExitCmd(void);
void sceSifAddCmdHandler(unsigned int cid, sceSifCmdHandler handler, void *data);
void sceSifRemoveCmdHandler(unsigned int cid);
unsigned int sceSifSendCmd(unsigned int cid, void *packet, int packet_size, void *src_extra, void *dest_extra,
                           int size_extra);
unsigned int isceSifSendCmd(unsigned int cid, void *packet, int packet_size, void *src_extra, void *dest_extra,
                            int size_extra);
unsigned int sceSifGetSreg(int reg);
unsigned int sceSifSetSreg(int reg, unsigned int value);
void sceSifWriteBackDCache(void *ptr, int size);

/* ---- SIF DMA / registers (syscalls) --------------------------------------------- */
unsigned int sceSifSetDma(sceSifDmaData *sdd, int len);
unsigned int isceSifSetDma(sceSifDmaData *sdd, int len);
int sceSifDmaStat(unsigned int id);
int isceSifDmaStat(unsigned int id);
void sceSifSetDChain(void);
void isceSifSetDChain(void);
void sceSifStopDma(void);
int sceSifGetReg(unsigned int reg);
int sceSifSetReg(unsigned int reg, int value);

/* ---- sifrpc ---------------------------------------------------------------------- */
void sceSifInitRpc(unsigned int mode);
void sceSifExitRpc(void);
int sceSifBindRpc(sceSifClientData *cd, unsigned int sid, unsigned int mode);
int sceSifCallRpc(sceSifClientData *cd, unsigned int fno, unsigned int mode, void *send, int ssize, void *recv,
                  int rsize, sceSifEndFunc end, void *endpara);
int sceSifCheckStatRpc(sceSifRpcData *rd);
void sceSifSetRpcQueue(sceSifQueueData *qd, int thread_id);
void sceSifRegisterRpc(sceSifServeData *sd, unsigned int sid, sceSifRpcFunc func, void *buff, sceSifRpcFunc cfunc,
                       void *cbuff, sceSifQueueData *qd);
sceSifServeData *sceSifRemoveRpc(sceSifServeData *sd, sceSifQueueData *qd);
sceSifQueueData *sceSifRemoveRpcQueue(sceSifQueueData *qd);
sceSifServeData *sceSifGetNextRequest(sceSifQueueData *qd);
void sceSifExecRequest(sceSifServeData *sd);
void sceSifRpcLoop(sceSifQueueData *qd); /* never returns */

/* ---- iopheap --------------------------------------------------------------------- */
int sceSifInitIopHeap(void);
void *sceSifAllocIopHeap(unsigned int size);
int sceSifFreeIopHeap(void *addr);
void *sceSifAllocSysMemory(int type, unsigned int size, void *addr);
int sceSifFreeSysMemory(void *addr);
unsigned int sceSifQueryMemSize(void);
unsigned int sceSifQueryMaxFreeMemSize(void);
unsigned int sceSifQueryTotalFreeMemSize(void);

/* ---- loadfile / iopcontrol ---------------------------------------------------------- */
int sceSifLoadFileReset(void);
int sceSifLoadModule(const char *path, int argsz, const char *args);
int sceSifLoadStartModule(const char *path, int argsz, const char *args, int *result);
int sceSifRebootIop(const char *img);
int sceSifResetIop(const char *arg, int mode);
int sceSifSyncIop(void);
int sceSifIsAliveIop(void);

/* ---- fileio ------------------------------------------------------------------------ */
#define SCE_RDONLY 0x0001
#define SCE_WRONLY 0x0002
#define SCE_RDWR   0x0003
#define SCE_APPEND 0x0100
#define SCE_CREAT  0x0200
#define SCE_TRUNC  0x0400
#define SCE_SEEK_SET 0
#define SCE_SEEK_CUR 1
#define SCE_SEEK_END 2
int sceOpen(const char *name, int flags, ...);
int sceClose(int fd);
int sceRead(int fd, void *buf, int nbyte);
int sceWrite(int fd, const void *buf, int nbyte);
int sceLseek(int fd, int offset, int whence);
int sceFsReset(void);

/* ---- libsdr (sdremote) ---------------------------------------------------------------- */
typedef int (*sceSdTransIntrHandler)(int core, void *common);
typedef int (*sceSdSpu2IntrHandler)(int core_bits, void *common);
int sceSdRemoteInit(int unused);
int sceSdRemote(int sync, int command, ...);
int sceSdRemoteCallbackInit(int priority);
void sceSdRemoteCallbackQuit(void);

/* ---- game-tree names (census boundary symbols; asm bodies excluded, bound here) ------ */
void sceSifInitRpc_119b60(unsigned int mode);
int sceSifFreeSysMemory_11ea40(void *addr);
int sceSifLoadModule_11f7a0(const char *path, int argsz, const char *args);
int sceSifSyncIop_11fc80(void);
int sceSifRebootIop_11fcd0(const char *img);
int sceOpen_11b928(const char *name, int flags);
int sceClose_11bbb8(int fd);
int sceLseek_11bd30(int fd, int offset, int whence);
int sceRead_11bf70(int fd, void *buf, int nbyte);
int sceWrite_11c1e0(int fd, const void *buf, int nbyte);
int sceSdRemoteInit_122890(int unused);
int sceSdRemote_1229e8(int sync, int command, ...);
int sceSdRemoteCallbackInit_122d70(int priority);
void sceSdRemoteCallbackQuit_122e70(void);

#ifdef __cplusplus
}
#endif
#endif
