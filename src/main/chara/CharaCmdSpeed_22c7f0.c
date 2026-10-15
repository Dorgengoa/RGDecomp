#include "types.h"

/* Stack locals are allocated in REVERSE declaration order, so the buffer that
   lands at sp+0x40 is declared LAST. */

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaGetSrtMatrix_2388c0(s32, void *);
extern f32 ScriptArgGetFloat_302cf0(s32);
extern void VecWeightedSum3_1cb860(void *, void *, void *, void *, f32, f32, f32);
extern void CharaSetVelocityFromVec_238790(s32, void *);

struct Obj0 {
    s32 m00;
};

struct Buf10 {
    u8 b[0x10];
};

struct Buf20 {
    u8 b[0x20];
};

s32 CharaCmdSpeed_22c7f0(struct Obj0 *p0, s32 p1, s32 argc)
{
    struct Buf20 sp70;
    struct Buf10 sp60;
    struct Buf10 sp50;
    struct Buf10 sp40;
    s32 r0;
    s32 o;
    f32 x;
    f32 y;
    f32 z;

    if (argc != 3) {
        return 1;
    }
    r0 = GetActionMgr_1fdb50();
    o = ActionMgrFindById_233b50(r0, p0->m00);
    if (o == 0) {
        return 1;
    }
    CharaGetSrtMatrix_2388c0(o, &sp50);
    x = ScriptArgGetFloat_302cf0(p1);
    y = ScriptArgGetFloat_302cf0(p1 + 5);
    z = ScriptArgGetFloat_302cf0(p1 + 0xA);
    VecWeightedSum3_1cb860(&sp40, &sp50, &sp60, &sp70, x, y, z);
    CharaSetVelocityFromVec_238790(o, &sp40);
    return 1;
}
