/* rgp:protos */
#define RGP_SELF_SysTickThreadStart_1c3470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Sema/ThreadParam layout matches sibling src/ax8/CdDiskWatchInit_17ff70.c. */
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

extern s32 CreateSema(Sema *p);
extern s32 CreateThread(ThreadParam *p);
extern void StartThread_1176e0(s32, s32);
extern s32 D_0047DF30;
extern s32 D_0047E248;
extern s32 D_0047E24C;
extern u8 D_00485170;
extern u8 D_004A3F80[];
/*rgp*/

void SysTickThreadStart_1c3470(void)
{
    Sema sp __attribute__((aligned(16)));
    ThreadParam tp __attribute__((aligned(16)));
    s32 tid;

    sp.m04 = 1;
    sp.m08 = 0;
    sp.m14 = 0;
    D_0047E248 = CreateSema(&sp);
    tp.pad20 = 0;
    tp.entry = (void *) SysTickThreadMain_1c33f0;
    tp.stack = D_004A3F80;
    tp.stackSize = 0x1000;
    tp.gp = &D_00485170;
    tp.arg = (void *) (D_0047DF30 - 2);
    tid = CreateThread(&tp);
    D_0047E24C = tid;
    StartThread_1176e0(tid, 0);
}
