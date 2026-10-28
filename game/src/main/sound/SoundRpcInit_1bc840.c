/* rgp:protos */
#define RGP_SELF_SoundRpcInit_1bc840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 count;
    s32 max;
    s32 init;
    s32 x0C;
    s32 x10;
    s32 x14;
} SemaParam;

typedef struct {
    s32 status;
    void *func;
    void *stack;
    s32 size;
    void *gp;
    s32 prio;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
} ThreadParam;

extern s32 AddIntcHandler(s32, void *, s32);
extern s32 CreateSema(SemaParam *);
extern s32 CreateThread(ThreadParam *);
extern void DisableIntc_117080(s32);
extern void EnableIntc_1170e8(s32);
extern void StartThread_1176e0(s32, s32);
extern void sceSifInitRpc_119b60(s32);
extern void sceCdChangeThreadPriority_12ab30(s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 sceSifBindRpc(void *, s32, s32);
extern s32 D_0047E210;
extern s32 D_0047E214;
extern s32 D_0047E218;
extern s32 D_0047E21C;
extern s32 D_004814D8;
extern s32 D_004814DC;
extern s32 D_004814F0[4] __attribute__((section(".sdata")));
extern s32 D_0048150C;
extern u8 D_00485170;
extern u8 D_004A25C0[];
extern s32 D_004A25E4[];
extern u8 D_004A2AC0[];
/*rgp*/
/*rgp*/

s32 SoundRpcInit_1bc840(s32 arg0)
{
    SemaParam sp __attribute__((aligned(16)));
    ThreadParam tp __attribute__((aligned(16)));
    s32 i;
    s32 p;

    sceSifInitRpc_119b60(0);
    do {
        if (sceSifBindRpc(D_004A25C0, 0x123456, 0) < 0) {
            return 0;
        }
    } while (D_004A25E4[0] == 0);
    sp.max = 1;
    sp.init = 0;
    sp.x14 = 0;
    D_0047E214 = CreateSema(&sp);
    sp.init = 1;
    D_0047E218 = CreateSema(&sp);
    if (D_0047E214 < 0 || D_0047E218 < 0) {
        SoundRpcShutdown_1bc760();
        return 0;
    }
    tp.size = 0x1000;
    tp.gp = &D_00485170;
    tp.func = SoundStreamSlotThreadMain_1bc520;
    tp.stack = D_004A2AC0;
    tp.prio = arg0 - 5;
    D_0047E21C = CreateThread(&tp);
    if (D_0047E21C < 0) {
        SoundRpcShutdown_1bc760();
        return 0;
    }
    StartThread_1176e0(D_0047E21C, 0);
    D_004814D8 = IopHeapAllocLocked_1c22d0(0x1004);
    D_004814DC = (D_004814D8 + 3) & ~3;
    DisableIntc_117080(3);
    D_0047E210 = AddIntcHandler(3, SoundVblankIntrHandler_1bd6f0, -1);
    EnableIntc_1170e8(3);
    SoundRpcCall_1bc5e0(0x8000, 3, 1, 0x1000, 3);
    SoundStreamSysInitMaybe_1bf790(arg0);
    sceCdChangeThreadPriority_12ab30(0x22);
    i = 0;
    do {
        D_004814F0[i] = 0;
        i++;
    } while (i < 4);
    D_0048150C = 0;
    return 1;
}
