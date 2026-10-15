#pragma opt_rebuildconditionals off
#pragma opt_propagation off
#include "types.h"

typedef unsigned __int128 u128;
typedef struct Vec { f32 x, y, z, w; } Vec;
struct PadB0 { u8 pad[0xB0]; };
class VC : public PadB0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void v54(f32, f32, f32);
    virtual void d20();
    virtual void d21();
    virtual void v60(f32);
};

typedef struct Big {
    u8 pad0[0x10];
    u8 m10[0x90];
    s32 mA0;
    u8 padA4[0xC];
    void *vptr;
    u8 padB4[8];
    s16 mBC;
    u8 padBE[0xF2];
    u128 m1B0;
    u8 pad1C0[0x470];
} Big;

extern "C" {
void FrameCalcWorldMatrix_148ff0(s32, Vec *);
void MatToRotPos_1cade0(Vec *, Vec *, Vec *);
void VecScaleToLength_1cb510(Vec *, Vec *, f32);
void MatMulPoint_1cb8e0(Vec *, Vec *, Vec *);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
void VecCopy_1cbe30(Vec *, Vec *);
s32 GetObjNodeByName_1ce3a0(s32, s32, s32);
s32 GetActionMgr_1fdb50(void);
s32 CharaGetBaseActionMode_213830(u8 *);
void CharaGetTargetPos_214a40(u8 *, Vec *);
void ProjectileCloneAndRegister_22e560(Big *);
u8 *ActionMgrFindById_233b50(s32, s32);
s32 ScriptArgGetStr_302cb0(u8 *);
f32 ScriptArgGetFloat_302cf0(u8 *);
s32 ScriptArgGetInt_302d70(u8 *);
void ProjectileCtor_317eb0(Big *, s32, s32, s32, f32);
void ExecInfoInitFromObj_3a7790(void *, s32, s32);
void ExecInfoInitFromChara_3a7830(void *, s32, u8, s32, s32);
extern u8 D_00471AA0[0x400];
extern f32 D_0047E6C0;
extern f32 D_0047E6C4;
extern f32 D_0047E6C8;
extern f32 D_0047E6CC;

s32 CharaCmdJoBulletFire_229760(s32 *arg0, u8 *arg1, s32 arg2)
{
    Vec pos;
    Vec mat[3];
    Vec dir;
    Vec tmp;
    Vec col;
    Big obj;
    Vec v;
    u8 *ent;
    s32 w;
    s32 sel;
    s32 h;
    s32 flag;
    s32 t;
    u8 *sub;
    s32 id;

    if (arg2 < 5) return 0;
    ent = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0);
    if (ent == 0) return 1;
    w = ScriptArgGetInt_302d70(arg1);
    h = GetObjNodeByName_1ce3a0(*arg0, w, ScriptArgGetStr_302cb0(arg1 + 5));
    if (h == 0) return 1;
    FrameCalcWorldMatrix_148ff0(h, mat);
    sel = 2;
    col.x = D_0047E6C0;
    col.y = D_0047E6C4;
    col.z = D_0047E6C8;
    col.w = D_0047E6CC;
    if (arg2 > 5) sel = ScriptArgGetInt_302d70(arg1 + 0x19) % 3;
    if (arg2 > 6) col.x = ScriptArgGetFloat_302cf0(arg1 + 0x1E);
    if (arg2 > 7) col.y = ScriptArgGetFloat_302cf0(arg1 + 0x23);
    if (arg2 > 8) col.z = ScriptArgGetFloat_302cf0(arg1 + 0x28);
    MatMulPoint_1cb8e0(&pos, mat, &col);
    MatToRotPos_1cade0(&tmp, &dir, mat);
    ProjectileCtor_317eb0(&obj, 1, *arg0, 5, 150.0f);
    id = *arg0;
    sub = obj.m10;
    if (id >= 0 && id < 12) {
        {
            s32 r = CharaGetBaseActionMode_213830(ent);
            s32 v;
if (r == 3) v = 1; else v = 0;
            flag = (u8)v;
        }
        ExecInfoInitFromChara_3a7830(sub, *arg0, flag, 0, ScriptArgGetStr_302cb0(arg1 + 0xA));
    } else if (id >= 0x80 && id < 0x9C) {
        ExecInfoInitFromObj_3a7790(sub, *arg0, ScriptArgGetStr_302cb0(arg1 + 0xA));
    }
    if (*(s32 *)(ent + 0xA44) & 0x8000) {
        CharaGetTargetPos_214a40(ent, &v);
        VecSub_1cbd00(&v, &v, &dir);
    } else {
        VecCopy_1cbe30(&v, &mat[sel]);
    }
    VecScaleToLength_1cb510(&v, &v, ScriptArgGetFloat_302cf0(arg1 + 0x14));
    obj.mBC = 1;
    ((VC *)&obj)->v60(ScriptArgGetFloat_302cf0(arg1 + 0xF));
    ((VC *)&obj)->v54(pos.x, pos.y, pos.z);
    obj.m1B0 = *(u128 *)&v;
    switch (*arg0) {
    case 0: obj.mA0 = 0x65; break;
    case 3: obj.mA0 = 0xA1; break;
    case 4: obj.mA0 = 0x79; break;
    }
    ProjectileCloneAndRegister_22e560(&obj);
    obj.vptr = D_00471AA0;
    return 1;
}
}
