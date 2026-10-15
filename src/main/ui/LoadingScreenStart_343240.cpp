#pragma optimization_level 3
#pragma divbyzerocheck on
#include "types.h"

typedef struct Pair8 { s8 a; s8 b; } Pair8;
typedef struct Pair32 { s32 a; s32 b; } Pair32;

typedef struct Cfg {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    f32 m18;
    f32 m1C;
    f32 m20;
    f32 m24;
    f32 m28;
    s32 m2C;
    s32 m30;
    s8 m34[14][64];
    s32 m3B4[14];
    s32 m3EC[14];
    s32 m424;
    s32 m428;
    s32 m42C;
    s32 m430;
    f32 m434;
} Cfg;

typedef struct ThreadParam {
    s32 status;
    void *entry;
    void *stack;
    s32 stackSize;
    void *gp;
    s32 prio;
    s32 curPrio;
    s32 attr;
    s32 option;
} ThreadParam;

extern "C" {
extern s32 D_0047F650;
extern s32 D_0047F658;
extern s8 D_0047F65C;
extern s32 D_00482D70;
extern s32 D_00482D74;
extern s32 D_00482D7C;
extern s32 D_00482D80;
extern f32 D_00482D84;
extern s32 D_00482D88;
extern s32 D_00485170;
extern Cfg D_004E8960;
s32 CreateThread(ThreadParam *p);
s32 StartThread_1176e0(s32 tid, s32 arg);
void LoadingScreenLoadImages_3446c0(void);
void LoadingScreenThread_343510(void *arg);
}

extern "C" s32 LoadingScreenStart_343240(Cfg *cfg)
{
    ThreadParam tp;
    s32 tid;

    D_0047F658 = 0;
    cfg->m1C = 0.0f;
    cfg->m20 = 0.0f;
    cfg->m28 = 0.0f;
    cfg->m18 = 0.0f;
    cfg->m434 = 0.0f;
    cfg->m2C = 0;
    D_00482D84 = -1.0f;
    D_00482D88 = 0;
    D_00482D7C = 0;
    D_00482D80 = 0;
    D_004E8960 = *cfg;
    LoadingScreenLoadImages_3446c0();
    tp.stackSize = cfg->m08;
    tp.gp = &D_00485170;
    tp.entry = (void *)LoadingScreenThread_343510;
    tp.stack = (void *)cfg->m04;
    tp.prio = cfg->m00;
    tid = CreateThread(&tp);
    D_0047F650 = tid;
    D_00482D70 = 1;
    D_00482D74 = 0;
    if (tid <= 0) {
        return 0;
    }
    StartThread_1176e0(tid, 0);
    D_0047F65C = 1;
    if (D_004E8960.m424 > 0) {
        s32 x = 0x58;
        s32 w = 0x138 / D_004E8960.m424;
        s32 i;
        if (w > 0x20) {
            w = 0x20;
        }
        for (i = 0; i < D_004E8960.m424; i++) {
            s8 v = D_004E8960.m34[i][0];
            bool on = false;
            s32 step;
            if (v != 0 && v != 10) {
                on = true;
            }
            if (on) step = w; else step = w >> 1;
            D_004E8960.m3EC[i] = x;
            x += step;
        }
    }
    return 1;
}
