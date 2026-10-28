/* rgp:protos */
#line 1
#pragma opt_rebuildconditionals off
#pragma opt_propagation off
#include "types.h"

typedef rg_u128 u128;
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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v19(f32 a0, f32 a1, f32 a2) { VCM(void, (void *, f32, f32, f32), 0x54, a0, a1, a2); }
    
    
    void v22(f32 a0) { VCM(void, (void *, f32), 0x60, a0); }
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
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Vec8)) + (0x20 + sizeof(Vec8)) + (0x40) + (0x30)]; typedef char rgp_blk1_chk0[(0x0) + sizeof(Vec8) <= (0x20) && (0x0) >= 0 ? 1 : -1];
    
    Vec4 v6D0 __attribute__((aligned(16)));
    Vec4 v6C0 __attribute__((aligned(16)));
    Vec8 buf __attribute__((aligned(16)));
    Obj obj __attribute__((aligned(16)));
    Vec4 v60 __attribute__((aligned(16)));
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
    FrameCalcWorldMatrix_148ff0(ent, &(*(Vec8 *)(rgp_blk1 + 0x0)));
    MatToRotPos_1cade0(&v6C0, &v6D0, &(*(Vec8 *)(rgp_blk1 + 0x0)));
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
            s32 r = ((short)CharaGetBaseActionMode_213830(chr));
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
        VecCopy_1cbe30(&v60, &(*(Vec8 *)(rgp_blk1 + 0x20)));
    }
    VecScaleToLength_1cb510(&v60, &(*(Vec8 *)(rgp_blk1 + 0x20)), 20.0f * D_0045B080[0]);
    obj.fBC = 1;
    ((VObj *)&obj)->v22(10.0f);
    ((VObj *)&obj)->v19((*(Vec8 *)(rgp_blk1 + 0x20)).b.x, (*(Vec8 *)(rgp_blk1 + 0x20)).b.y, (*(Vec8 *)(rgp_blk1 + 0x20)).b.z);
    *(u128 *)&obj.f1B0 = *(u128 *)&v60;
    ProjectileCloneAndRegister_22e560(&obj);
    obj.vptr = D_00471AA0;
    return 1;
}
