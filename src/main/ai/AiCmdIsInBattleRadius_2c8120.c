#include "types.h"

typedef unsigned __int128 u128;

extern f32 VecDistance_13d3d0(u128 *, u8 *);
extern void FrameGetWorldPos_148f30(s32, u128 *);
extern s32 ModelGetRootFrame_1511a0(u8 *);
extern u8 *ObjRecGetLiveObject_1c4a90(s32, s32);
extern u8 *GetGameData_1fede0(void);
extern void GameFlowGetBattleCenter_283390(u8 *);
extern void ScriptSlotStoreIntRef_2cc900(s32, s32);
extern f32 ScriptSlotGetFloat_2cc9a0(s32);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s32 D_004DB920[];

static inline void clr(void *p, s32 n)
{
    u8 *q;
    s32 c;
    c = n;
    q = (u8 *)p;
    if (q != NULL) {
        do {
            *q++ = 0;
        } while (--c);
    }
}

s32 AiCmdIsInBattleRadius_2c8120(s32 arg0, s32 arg1)
{
    u8 sp70[0x10];
    u128 sp60;
    s32 keep;
    s32 r;
    f32 f21;
    f32 f20;
    u8 *h;
    u8 *p;
    u8 *q;

    if (arg1 < 2 || arg1 > 3) {
        return 0;
    }
    keep = 1;
    clr(sp70, 0x10);
    GameFlowGetBattleCenter_283390(sp70);
    h = ObjRecGetLiveObject_1c4a90(D_004DB920[0], ScriptSlotGetInt_2cc9c0(arg0 + 8));
    if (h != NULL) {
        clr(&sp60, 0x10);
        r = ModelGetRootFrame_1511a0(h);
        if (r != 0) {
            FrameGetWorldPos_148f30(r, &sp60);
        } else {
            sp60 = *(u128 *)(h + 0x180);
        }
        h = GetGameData_1fede0();
        f21 = 600.0f;
        p = *(u8 **)(*(u8 **)(h + 0x20) + 0x238);
        q = p ? *(u8 **)(p + 0x18) : NULL;
        if (q != NULL) {
            f21 = *(f32 *)(q + 0x20);
            if (f21 <= 0.0f) {
                f21 = -1.0f;
            }
            keep = 1;
        }
        f20 = 1.0f;
        if (arg1 >= 3) {
            f20 = ScriptSlotGetFloat_2cc9a0(arg0 + 0x10);
        }
        if (0.0f < f21 && f21 * f20 < VecDistance_13d3d0(&sp60, sp70)) {
            keep = 0;
        }
    }
    ScriptSlotStoreIntRef_2cc900(arg0, keep);
    return 1;
}
