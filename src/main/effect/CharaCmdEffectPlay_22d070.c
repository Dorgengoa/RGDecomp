#include "types.h"

typedef unsigned __int128 u128;

/* argc guard is `!= 8 && != 9`: both beq's jump INTO the body, the
   fall-through is the failure return.  Stack locals are allocated in REVERSE
   declaration order, so `st` is the 0x110 slot and `m70` the 0x70 slot.
   The 16-byte clear of `vb` is the guarded inline byte loop idiom. */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct {
    V4 r[4];
} Mtx;

struct Obj0 {
    s32 m00;
};

struct Rec {
    u8 pad[0x180];
    u128 m180;
    u128 m190;
};

extern s32 GetCurrentScene_1f5be0(void);
extern struct Rec *ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern s32 ScriptArgGetInt_302d70(s32);
extern f32 ScriptArgGetFloat_302cf0(s32);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectCreateByName_2e1020(f32 *, s32, s32, s16);
extern void EffectSetAutoRelease_2e1170(s32, f32 *, s32);
extern void EffectSetId_2e0100(s32, f32 *, s32);
extern void EffectSetName_2e01c0(s32, f32 *, s32);
extern void EffectSetPos_2e0bb0(s32, f32 *, V4 *);
extern void EffectSetRot_2e09f0(s32, f32 *, V4 *);
extern void EffectSetScaleXyz_2e0c90(s32, f32 *, f32, f32, f32);
extern void MatFromRotPos_1caf90(Mtx *, V4 *, V4 *);
extern void MatMul_1cb700(Mtx *, Mtx *, Mtx *);
extern void MatToRotPos_1cade0(V4 *, V4 *, Mtx *);

extern f32 D_0047E6B0;
extern f32 D_0047E6B4;
extern f32 D_0047E6B8;
extern f32 D_0047E6BC;

s32 CharaCmdEffectPlay_22d070(struct Obj0 *p0, s32 p1, s32 argc)
{
    f32 st[8];
    V4 va;
    V4 vb;
    Mtx mb;
    Mtx ma;
    s32 r0;
    struct Rec *rec;
    s32 a;
    s32 b;
    s32 obj;
    s32 n;
    u8 *q;
    u32 cnt;

    if (argc != 8 && argc != 9) {
        return 0;
    }
    r0 = GetCurrentScene_1f5be0();
    rec = ObjRecGetLiveObject_1c4a90(r0, p0->m00);
    if (rec == 0) {
        return 1;
    }
    a = ScriptArgGetStr_302cb0(p1);
    b = 0;
    if (argc == 9) {
        b = ScriptArgGetStr_302cb0(p1 + 5);
        p1 += 5;
    }
    obj = GetEffectMgr_2d9040();
    n = ScriptArgGetInt_302d70(p1 + 5);
    EffectCreateByName_2e1020(st, obj, a, n);
    EffectSetAutoRelease_2e1170(obj, st, 1);
    EffectSetId_2e0100(obj, st, p0->m00);
    EffectSetName_2e01c0(obj, st, b);
    va.x = D_0047E6B0;
    va.y = D_0047E6B4;
    va.z = D_0047E6B8;
    va.w = D_0047E6BC;
    va.x = ScriptArgGetFloat_302cf0(p1 + 0xA);
    va.y = ScriptArgGetFloat_302cf0(p1 + 0xF);
    va.z = ScriptArgGetFloat_302cf0(p1 + 0x14);
    q = (u8 *)&vb;
    cnt = 0x10;
    if (q != 0) {
        do {
            *q = 0;
            cnt--;
            q++;
        } while (cnt != 0);
    }
    vb.x = ScriptArgGetFloat_302cf0(p1 + 0x19);
    vb.y = ScriptArgGetFloat_302cf0(p1 + 0x1E);
    vb.z = ScriptArgGetFloat_302cf0(p1 + 0x23);
    MatFromRotPos_1caf90(&mb, &vb, &va);
    /* lq/sq: a 4-float struct copies member-wise (lwc1/swc1 x4), a u128 copies
       as one qword - 12 words of difference on this unit. */
    *(u128 *)&va = rec->m180;
    *(u128 *)&vb = rec->m190;
    MatFromRotPos_1caf90(&ma, &vb, &va);
    MatMul_1cb700(&mb, &ma, &mb);
    MatToRotPos_1cade0(&vb, &va, &mb);
    EffectSetPos_2e0bb0(obj, st, &va);
    EffectSetRot_2e09f0(obj, st, &vb);
    EffectSetScaleXyz_2e0c90(obj, st, 1.0f, 1.0f, 1.0f);
    return 1;
}
