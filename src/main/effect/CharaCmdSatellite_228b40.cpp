#pragma opt_rebuildconditionals off
#pragma opt_propagation off
#include "types.h"

typedef unsigned __int128 u128;
typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } Vec4;
typedef struct { Vec4 a; Vec4 b; } Vec8;


typedef struct Obj {
    u8 pad0[0x10];
    u8 sub[0xA0];
    void *vptr;
    u8 padB4[8];
    s16 fBC;
    u8 padBE[0xF2];
    Vec4 f1B0;
    u8 pad1C0[0x470];
} Obj;
class VObj {
public:
    u8 pad[0xB0];
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19(f32, f32, f32);
    virtual void v20();
    virtual void v21();
    virtual void v22(f32);
};


typedef struct {
    u8 pad0[0xA44];
    s32 flags;
} Chr;

extern "C" {
s32 GetActionMgr_1fdb50(void);
Chr *ActionMgrFindById_233b50(s32, s32);
s32 ScriptArgGetInt_302d70(u8 *);
s32 ScriptArgGetStr_302cb0(u8 *);
s32 GetObjNodeByName_1ce3a0(s32, s32, s32);
void FrameCalcWorldMatrix_148ff0(s32, Vec8 *);
void MatToRotPos_1cade0(Vec4 *, Vec4 *, Vec8 *);
s32 GetEffectMgr_2d9040(void);
void EffectCreateByName_2e1020(Vec8 *, s32, s32, s32);
void EffectSetAutoRelease_2e1170(s32, Vec8 *, s32);
void EffectSetId_2e0100(s32, Vec8 *, s32);
void EffectSetPos_2e0bb0(s32, Vec8 *, Vec4 *);
void EffectSetRot_2e09f0(s32, Vec8 *, Vec4 *);
void ProjectileCtor_317eb0(Obj *, s32, s32, s32, f32);
s32 CharaGetBaseActionMode_213830(Chr *);
void ExecInfoInitFromChara_3a7830(u8 *, s32, u8, s32, s32);
void ExecInfoInitFromObj_3a7790(u8 *, s32, s32);
void CharaGetTargetPos_214a40(Chr *, Vec4 *);
void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
void VecCopy_1cbe30(Vec4 *, Vec8 *);
void VecScaleToLength_1cb510(Vec4 *, Vec8 *, f32);
void ProjectileCloneAndRegister_22e560(Obj *);
extern f32 D_0045B080[];
extern u8 D_00471AA0[];
}

extern "C" s32 CharaCmdSatellite_228b40(s32 *ids, u8 *msg, s32 type) {
    Vec8 v700;
    Vec8 v6E0;
    Vec4 v6D0;
    Vec4 v6C0;
    Vec8 buf;
    Obj obj;
    Vec4 v60;
    Chr *chr;
    s32 ent;
    s32 w;
    s32 id;
    s32 flag;
    u8 *sub;

    if (type != 4) {
        return 0;
    }
    chr = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *ids);
    if (chr == 0) {
        return 1;
    }
    w = ScriptArgGetInt_302d70(msg + 5);
    ent = GetObjNodeByName_1ce3a0(*ids, w, ScriptArgGetStr_302cb0(msg + 10));
    if (ent == 0) {
        return 1;
    }
    FrameCalcWorldMatrix_148ff0(ent, &v6E0);
    MatToRotPos_1cade0(&v6C0, &v6D0, &v6E0);
    w = GetEffectMgr_2d9040();
    EffectCreateByName_2e1020(&buf, w, ScriptArgGetStr_302cb0(msg + 15), -1);
    EffectSetAutoRelease_2e1170(w, &buf, 1);
    EffectSetId_2e0100(w, &buf, *ids);
    EffectSetPos_2e0bb0(w, &buf, &v6D0);
    EffectSetRot_2e09f0(w, &buf, &v6C0);
    ProjectileCtor_317eb0(&obj, 1, *ids, 5, 150.0f);
    id = *ids;
    sub = obj.sub;
    if (id >= 0 && id < 12) {
        {
            s32 r = CharaGetBaseActionMode_213830(chr);
            s32 v;
if (r == 3) v = 1; else v = 0;
            flag = (u8)v;
        }
        ExecInfoInitFromChara_3a7830(sub, *ids, flag, 0, ScriptArgGetStr_302cb0(msg));
    } else if (id >= 0x80 && id < 0x9C) {
        ExecInfoInitFromObj_3a7790(sub, *ids, ScriptArgGetStr_302cb0(msg));
    }
    if (chr->flags & 0x8000) {
        CharaGetTargetPos_214a40(chr, &v60);
        VecSub_1cbd00(&v60, &v60, &v6D0);
    } else {
        VecCopy_1cbe30(&v60, &v700);
    }
    VecScaleToLength_1cb510(&v60, &v700, 20.0f * D_0045B080[0]);
    obj.fBC = 1;
    ((VObj *)&obj)->v22(10.0f);
    ((VObj *)&obj)->v19(v700.b.x, v700.b.y, v700.b.z);
    *(u128 *)&obj.f1B0 = *(u128 *)&v60;
    ProjectileCloneAndRegister_22e560(&obj);
    obj.vptr = D_00471AA0;
    return 1;
}
