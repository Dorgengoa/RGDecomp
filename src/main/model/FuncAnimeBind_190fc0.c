/* PARKED s15i: ~14 unknown-typed ("?") externs each taking an output-struct
 * pointer of unknown shape (FrameGetScale_14a1c0/1f0/220, FUN_0018656x family) plus
 * an s128 local and a nested struct read (arg0->unk0->unk80); 0 round trips
 * spent. Needs several call sites cross-referenced to pin the output struct
 * shape before writing C. Not attempted. */
/* s49m: MATCH */
#include "types.h"

typedef unsigned __int128 u128;
typedef struct { f32 x, y, z, w; } V4;

extern s32 NodeObjFindChildByName_195040(s32, char *);
extern s32 ModelFindFrameIndexByName_151220(s32, char *);
extern s32 ModelGetFrame_1511f0(s32, s32);
extern void ModelFrameGetPos_14a220(s32, V4 *);
extern void FrameGetRot_14a1f0(s32, V4 *);
extern void FrameGetScale_14a1c0(s32, V4 *);
extern void NodeGetTranslation_186650(s32, V4 *);
extern void NodeGetRotation_1865e0(s32, V4 *);
extern void NodeGetScale_186560(s32, V4 *);
extern void NodeSetTranslation_1866b0(u8 *, V4 *);
extern void NodeSetRotation_186620(u8 *, V4 *);
extern void NodeSetScale_1865b0(u8 *, V4 *);
extern void VecAdd_13be20(V4 *, void *, void *);
extern void VecScale_13be00(V4 *, V4 *, f32);
extern void FuncAnimeApplyValue_191270(s32 *, V4 *);

s32 FuncAnimeBind_190fc0(s32 *arg0, u8 *arg1, s32 arg2)
{
    V4 spA0;
    V4 sp90;
    V4 sp80;
    V4 sp70;
    char *p;
    char *q;
    s32 a;
    s32 b;
    s32 h;
    s32 x;
    u8 *o;

    if (*(s32 *)(arg1 + 0x40) != 5) {
        return 0;
    }
    if (arg2 == 0) {
        return 0;
    }
    arg0[1] = 0;
    arg0[2] = 0;
    arg0[3] = 0;
    arg0[0] = 0;
    arg0[5] = 0;
    arg0[4] = 0;
    arg0[0] = (s32)arg1;
    a = 0;
    p = *(char **)(arg1 + 0x64);
    q = *(char **)(arg1 + 0x68);
    b = 0;
    if (p != NULL && *p != 0 && arg2 != 0) {
        a = NodeObjFindChildByName_195040(arg2, p);
    }
    if (q != NULL && *q != 0 && a != 0 && (h = *(s32 *)(a + 0x6C)) != 0) {
        b = ModelGetFrame_1511f0(h, ModelFindFrameIndexByName_151220(h, q));
    }
    arg0[1] = b;
    arg0[2] = a;
    arg0[3] = arg2;
    if (arg0[1] != 0) {
        ModelFrameGetPos_14a220(arg0[1], &spA0);
        FrameGetRot_14a1f0(arg0[1], &sp90);
        FrameGetScale_14a1c0(arg0[1], &sp80);
    } else {
        x = arg0[3];
        if (x == 0) {
            x = arg0[2];
        }
        if (x != 0) {
            NodeGetTranslation_186650(x, &spA0);
            NodeGetRotation_1865e0(x, &sp90);
            NodeGetScale_186560(x, &sp80);
        }
    }
    NodeSetTranslation_1866b0((u8 *)arg0[0], &spA0);
    NodeSetRotation_186620((u8 *)arg0[0], &sp90);
    NodeSetScale_1865b0((u8 *)arg0[0], &sp80);
    *(u128 *)&sp70 = *(u128 *)((u8 *)arg0[0] + 0x80);
    o = (u8 *)arg0[0];
    if (*(s8 *)(o + 0x6D) == 0xB) {
        VecAdd_13be20(&sp70, o + 0x80, o + 0xA0);
        VecScale_13be00(&sp70, &sp70, 0.5f);
    }
    *(u128 *)(arg0 + 0xC) = 0;
    FuncAnimeApplyValue_191270(arg0, &sp70);
    return 1;
}
