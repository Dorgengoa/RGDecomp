#include "types.h"
//PRAGMA

typedef rg_u128 u128;

struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

struct Mat3 {
    Vec a;
    Vec b;
    Vec c;
    Vec d;
};

union QV {
    u128 q;
    Vec v;
};

struct ObjBase {
    u8 pad0[0xB0];
};

class Obj : public ObjBase {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f54(f32 a0, f32 a1, f32 a2) { VCM(void, (void *, f32, f32, f32), 0x54, a0, a1, a2); }
    
    
    void f60(f32 a0) { VCM(void, (void *, f32), 0x60, a0); }
};

struct ObjData {
    u8 pad0[0xB0];
    void *vt;
    u8 padB4[8];
    s16 xBC;
    u8 padBE[0xF2];
    u128 x1B0;
    s32 x1C0;
    f32 x1C4;
    f32 x1C8;
    u8 pad1CC[0x464];
};

extern "C" {
f32 RandFloat_13c010(void);
void FrameCalcWorldMatrix_148ff0(s32, Vec *);
void VecLinearCombine_1cb8b0(u128 *, Vec *, Vec *, f32, f32);
void MatMulVec4_1cb940(Vec *, Vec *, Vec *);
void VecNormalize_1cbb80(Vec *, Vec *);
s32 GetObjNodeByName_1ce3a0(s32, s32, s32);
s32 GetActionMgr_1fdb50(void);
void ProjectileCloneAndRegister_22e560(ObjData *);
s32 ActionMgrFindById_233b50(s32, s32);
f32 GetScaledGravity_23b170(void);
s32 ScriptArgGetStr_302cb0(s32);
s32 ScriptArgGetInt_302d70(s32);
s32 GetSphereModel_313e00(void);
void ProjectileCtor_317eb0(ObjData *, s32, s32, s32, f32);

extern u8 D_00471AA0[];
extern f32 D_0047D278;
extern f32 D_0047DB7C;
extern f32 D_0047E6D0;
extern f32 D_0047E6D4;
extern f32 D_0047E6D8;
extern f32 D_0047E6DC;
}

extern "C" s32 CharaCmdJoCartridgeEject_229520(s32 *arg0, s32 arg1, s32 arg2)
{
    //DECLS
    Mat3 m __attribute__((aligned(16)));
    Vec p __attribute__((aligned(16)));
    QV q __attribute__((aligned(16)));
    ObjData obj __attribute__((aligned(16)));
    s32 a;
    s32 h;
    f32 r;
    //ENDDECLS

    if (arg2 < 2) {
        return 0;
    }
    if (ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *arg0) == 0) {
        return 1;
    }
    a = ScriptArgGetInt_302d70(arg1);
    h = GetObjNodeByName_1ce3a0(*arg0, a, ScriptArgGetStr_302cb0(arg1 + 5));
    if (h == 0) {
        return 1;
    }
    FrameCalcWorldMatrix_148ff0(h, &m.a);
    p.x = D_0047E6D0;
    p.y = D_0047E6D4;
    p.z = D_0047E6D8;
    p.w = D_0047E6DC;
    MatMulVec4_1cb940(&p, &m.a, &p);
    m.c.y = 0.0f;
    VecNormalize_1cbb80(&m.c, &m.c);
    m.a.x = m.c.z;
    m.a.y = 0.0f;
    m.a.z = -m.c.x;
    m.a.w = 0.0f;
    m.b.x = 0.0f;
    m.b.y = 1.0f;
    m.b.z = 0.0f;
    m.b.w = 0.0f;
    r = (RandFloat_13c010() - D_0047D278) / 2.0f;
    VecLinearCombine_1cb8b0(&q.q, &m.c, &m.b, r, (1.0f + RandFloat_13c010()) / 8.0f);
    q.v.y += 2.5f;
    ProjectileCtor_317eb0(&obj, 0, 0, 4, 60.0f);
    obj.x1C0 = GetSphereModel_313e00();
    obj.xBC = 3;
    ((Obj *)&obj)->f60(0.25f);
    ((Obj *)&obj)->f54(p.x, p.y, p.z);
    obj.x1B0 = q.q;
    obj.x1C4 = GetScaledGravity_23b170();
    obj.x1C8 = D_0047DB7C * (1.0f + RandFloat_13c010());
    ProjectileCloneAndRegister_22e560(&obj);
    obj.vt = D_00471AA0;
    return 1;
}
