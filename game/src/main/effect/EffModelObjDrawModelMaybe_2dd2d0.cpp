/* rgp:protos */
#line 1
#include "types.h"

/* EffModelObjDrawModelMaybe_2dd2d0 -- 136 B, TWO entries.  The polymorphic sub-object lives at
 * +0x1A0 and its own vptr at +0x1B0 within it (vtable read at o+0x350). */

struct SubB2DD { u8 pad[0x1B0]; };
class Sub2DD : public SubB2DD {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    int v7() { return VCM0(int, 0x24); }
    
    
    
    
    
    
    
    void v15(f32 a0) { VCM(void, (void *, f32), 0x44, a0); }
};

struct Out2DD { u8 pad000[0x1A0]; Sub2DD m1A0; };

extern "C" void ModelSetScale_150ff0(void *, void *);
extern "C" void ModelSetPos_151110(void *, void *);
extern "C" void ModelSetRot_151080(void *, void *);
extern "C" s32 GetCurrentScene_1f5be0(void);
extern "C" f32 GameSceneGetTimeStep_1ceba0(s32);

extern "C" int EffModelObjDrawModelMaybe_2dd2d0(Out2DD *o) { int rgp_v0; rgp_v0 = o->m1A0.v7(); return rgp_v0; }

extern "C" void func_002DD2D0_e1(Out2DD *o)
{
    ModelSetScale_150ff0(&o->m1A0, (u8 *)o + 0x60);
    ModelSetPos_151110(&o->m1A0, (u8 *)o + 0x40);
    ModelSetRot_151080(&o->m1A0, (u8 *)o + 0x50);
    o->m1A0.v15(GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0()));
}
