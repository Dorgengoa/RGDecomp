/* SPDX-License-Identifier: CC0-1.0
 *
 * EE kernel API with the SDK names the game calls (census:
 * platform_ee_syscalls.tsv, platform_sdk_surface.tsv, family libkernl).
 * Written from scratch over src/ps2/kernel (ps2k); see docs/KERNEL.md.
 *
 * Struct layouts follow the SDK (all fields 32-bit):
 *   ThreadParam: status entry stack stackSize gpReg initPriority
 *                currentPriority attr option waitType waitId wakeupCount
 *   SemaParam:   currentCount maxCount initCount numWaitThreads attr option
 * The game's own per-file copies of these structs use the same offsets.
 *
 * NOTE (i686 Windows): CreateThread/ExitThread/TerminateThread/SuspendThread/
 * ResumeThread share names with Win32 API functions.  They do not collide on
 * i686 because Win32 imports are stdcall-decorated (_CreateThread@24) while
 * these are cdecl (_CreateThread), but a translation unit must not include
 * both this header and <windows.h>.  On x64 they WOULD collide (P7 issue).
 */
#ifndef SCE_EEKERNEL_H
#define SCE_EEKERNEL_H

#if defined(_WIN64)
/* x64 (docs/X64-PLAN.md): kernel32's undecorated exports would collide; the game side
 * gets the same renames from include/port/x64.h.  SCE_P32: the SDK structs live in
 * game memory with 4-byte pointers (the ptr32 stage's RG_P32). */
#define CreateThread    rg_ee_CreateThread
#define ExitThread      rg_ee_ExitThread
#define TerminateThread rg_ee_TerminateThread
#define SuspendThread   rg_ee_SuspendThread
#define ResumeThread    rg_ee_ResumeThread
#define SCE_P32 __ptr32 __uptr
#else
#define SCE_P32
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct ThreadParam {
    int          status;
    void * SCE_P32 entry;
    void * SCE_P32 stack;
    int          stackSize;
    void * SCE_P32 gpReg;
    int          initPriority;
    int          currentPriority;
    unsigned int attr;
    unsigned int option;
    int          waitType;
    int          waitId;
    int          wakeupCount;
};

struct SemaParam {
    int          currentCount;
    int          maxCount;
    int          initCount;
    int          numWaitThreads;
    unsigned int attr;
    unsigned int option;
};

#define THS_RUN         0x01
#define THS_READY       0x02
#define THS_WAIT        0x04
#define THS_SUSPEND     0x08
#define THS_WAITSUSPEND 0x0C
#define THS_DORMANT     0x10
#define TSW_SLEEP       1
#define TSW_SEMA        2
#define TH_SELF         0

#define INTC_GS           0
#define INTC_SBUS         1
#define INTC_VBLANK_S     2
#define INTC_VBLANK_E     3
#define INTC_VIF0         4
#define INTC_VIF1         5
#define INTC_VU0          6
#define INTC_VU1          7
#define INTC_IPU          8
#define INTC_TIM0         9
#define INTC_TIM1         10
#define INTC_TIM2         11
#define INTC_TIM3         12
#define INTC_SFIFO        13
#define INTC_VU0WD        14

#define DMAC_VIF0     0
#define DMAC_VIF1     1
#define DMAC_GIF      2
#define DMAC_FROM_IPU 3
#define DMAC_TO_IPU   4
#define DMAC_SIF0     5
#define DMAC_SIF1     6
#define DMAC_SIF2     7
#define DMAC_FROM_SPR 8
#define DMAC_TO_SPR   9

/* threads */
int  CreateThread(struct ThreadParam *param);
int  DeleteThread(int thread_id);
int  StartThread(int thread_id, void *arg);
void ExitThread(void);
void ExitDeleteThread(void);
int  TerminateThread(int thread_id);
int  iTerminateThread(int thread_id);
int  ChangeThreadPriority(int thread_id, int priority);
int  iChangeThreadPriority(int thread_id, int priority);
int  RotateThreadReadyQueue(int priority);
int  iRotateThreadReadyQueue(int priority);
int  ReleaseWaitThread(int thread_id);
int  iReleaseWaitThread(int thread_id);
int  GetThreadId(void);
int  ReferThreadStatus(int thread_id, struct ThreadParam *info);
int  iReferThreadStatus(int thread_id, struct ThreadParam *info);
int  SleepThread(void);
int  WakeupThread(int thread_id);
int  iWakeupThread(int thread_id);
int  CancelWakeupThread(int thread_id);
int  iCancelWakeupThread(int thread_id);
int  SuspendThread(int thread_id);
int  iSuspendThread(int thread_id);
int  ResumeThread(int thread_id);
int  iResumeThread(int thread_id);
int  DelayThread(int usec);

/* semaphores */
int CreateSema(struct SemaParam *param);
int DeleteSema(int sema_id);
int iDeleteSema(int sema_id);
int SignalSema(int sema_id);
int iSignalSema(int sema_id);
int WaitSema(int sema_id);
int PollSema(int sema_id);
int iPollSema(int sema_id);
int ReferSemaStatus(int sema_id, struct SemaParam *info);
int iReferSemaStatus(int sema_id, struct SemaParam *info);

/* interrupts */
int AddIntcHandler(int cause, int (*handler)(int), int next);
int AddIntcHandler2(int cause, int (*handler)(int, void *, void *), int next, void *arg);
int RemoveIntcHandler(int cause, int handler_id);
int AddDmacHandler(int channel, int (*handler)(int), int next);
int AddDmacHandler2(int channel, int (*handler)(int, void *, void *), int next, void *arg);
int RemoveDmacHandler(int channel, int handler_id);
int EnableIntc(int cause);
int DisableIntc(int cause);
int iEnableIntc(int cause);
int iDisableIntc(int cause);
int EnableDmac(int channel);
int DisableDmac(int channel);
int iEnableDmac(int channel);
int iDisableDmac(int channel);
int DIntr(void); /* returns 1 if interrupts were enabled */
int EIntr(void); /* returns 1 if interrupts were enabled */

/* alarms (time in hsync units) */
int SetAlarm(unsigned short time, void (*handler)(int, unsigned short, void *), void *arg);
int iSetAlarm(unsigned short time, void (*handler)(int, unsigned short, void *), void *arg);
int ReleaseAlarm(int alarm_id);
int iReleaseAlarm(int alarm_id);

/* cache (no-ops: host memory is coherent) */
void FlushCache(int mode);
void iFlushCache(int mode);
void SyncDCache(void *start, void *end);
void iSyncDCache(void *start, void *end);
void InvalidDCache(void *start, void *end);
void iInvalidDCache(void *start, void *end);

/* Game-tree symbol names for the asm-bodied libkernl units (PLAN.md
 * transform 6 binds these to the implementations above). */
int StartThread_1176e0(int thread_id, void *arg);
int DelayThread_117618(int usec);
int EnableIntc_1170e8(int cause);
int DisableIntc_117080(int cause);
int EnableDmac_1171b8(int channel);
int DisableDmac_117150(int channel);
int DisableIntr_120660(void);
int EnableIntr_1206b0(void);
int CpuIntrDisabled_117070(void); /* 1 iff COP0 Status.IE == 0 (handler context) */

#ifdef __cplusplus
}
#endif
#endif
