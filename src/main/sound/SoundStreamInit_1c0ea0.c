#include "types.h"

typedef struct {
    u8 pad0[0x38];
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    u8 unk44;
    u8 pad48[0x64 - 0x48];
    s8 *unk64;
} Obj001C0EA0;

typedef struct {
    s32 status;
    void *func;
    s32 stack;
    s32 stack_size;
    s32 gp_reg;
    s32 prio;
    s32 cur_prio;
    s32 attr;
    s32 option;
} ThreadParam001C0EA0;

typedef struct {
    s32 count;
    s32 max_count;
    s32 init_count;
    s32 wait_threads;
    s32 attr;
    s32 option;
} SemaParam001C0EA0;

s32 CreateSema(SemaParam001C0EA0 *);                /* extern */
s32 CreateThread(ThreadParam001C0EA0 *);            /* extern */
void StartThread_1176e0(s32, Obj001C0EA0 *);              /* extern */
void RingBufInit_1c1710(void *, s32, s32);                /* extern */
extern s32 D_0047E220;
extern s32 D_00485170;
extern void SoundStreamThreadMain_1c1050(void);

s32 SoundStreamInit_1c0ea0(Obj001C0EA0 *arg0, s8 *arg1, u32 arg2) {
    ThreadParam001C0EA0 sp90;
    SemaParam001C0EA0 sp70;
    SemaParam001C0EA0 sp50;
    s32 temp_16;
    s32 temp_2;
    s32 temp_5;

    if (arg2 < 0x2B00U) {
        return 0;
    }
    arg0->unk64 = arg1;
    *arg1 = 0;
    temp_16 = ((s32)(arg1 + 0x100) + 0x3F) & ~0x3F;
    sp90.stack_size = 0x1000;
    sp90.gp_reg = (s32) &D_00485170;
    sp90.stack = temp_16;
    sp90.func = SoundStreamThreadMain_1c1050;
    sp90.prio = D_0047E220;
    temp_2 = CreateThread(&sp90);
    arg0->unk38 = temp_2;
    if (temp_2 < 0) {
        return 0;
    }
    temp_5 = ((s32)((s8 *)temp_16 + 0x1000) + 0x3F) & ~0x3F;
    RingBufInit_1c1710((u8 *) arg0 + 4, temp_5, ((s32) arg1 + (s32) arg2) - temp_5);
    if (arg0->unk40 <= 0) {
        sp70.init_count = 1;
        sp70.max_count = 1;
        sp70.option = 0;
        arg0->unk40 = CreateSema(&sp70);
    }
    if (arg0->unk3C <= 0) {
        sp50.max_count = 1;
        sp50.init_count = 0;
        sp50.option = 0;
        arg0->unk3C = CreateSema(&sp50);
    }
    StartThread_1176e0(arg0->unk38, arg0);
    arg0->unk44 = 0;
    return 1;
}
