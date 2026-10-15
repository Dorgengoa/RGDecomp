#include "types.h"

typedef struct Sema {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
} Sema;

typedef struct ThreadParam {
    s32 m00;
    void *entry;
    void *stack;
    s32 stackSize;
    void *gp;
    void *arg;
    s32 pad18;
    s32 pad1C;
    s32 pad20;
    s32 pad24;
    s32 pad28;
    s32 pad2C;
} ThreadParam;

extern s32 D_00481218;
extern s32 D_00481220;
extern s32 D_00481224;
extern s32 D_00481228;
extern s32 D_0047E038;
extern s32 D_0047E034;
extern u8 D_0049C100[0x800];
extern s32 D_00485170;

extern void CdDiskWatchThread_17fdc0(void *arg);
extern void CdDiskWatchPowerOffCb_180050(void *arg);

extern s32 CreateSema(Sema *p);
extern s32 CreateThread(ThreadParam *p);
extern s32 DeleteSema(s32 id);
extern s32 StartThread_1176e0(s32 tid, s32 arg);
extern s32 sceCdPOffCallback_129690(void *func, s32 arg);

s32 CdDiskWatchInit_17ff70(void *a0)
{
    Sema sp;
    ThreadParam tp;
    s32 sid;
    s32 tid;

    if (D_00481218 != 0) {
        return 0;
    }
    sp.m04 = 1;
    sp.m08 = 0;
    sp.m14 = 0;
    sid = CreateSema(&sp);
    D_0047E038 = sid;
    if (sid < 0) {
        return 0;
    }
    tp.stackSize = 0x800;
    tp.arg = a0;
    tp.gp = &D_00485170;
    tp.entry = (void *)CdDiskWatchThread_17fdc0;
    tp.stack = D_0049C100;
    tid = CreateThread(&tp);
    D_0047E034 = tid;
    if (tid < 0) {
        DeleteSema(D_0047E038);
        return 0;
    }
    D_00481220 = 0;
    D_00481218 = 1;
    D_00481224 = 0;
    D_00481228 = 0;
    StartThread_1176e0(tid, 0);
    sceCdPOffCallback_129690((void *)CdDiskWatchPowerOffCb_180050, 0);
    return 1;
}
