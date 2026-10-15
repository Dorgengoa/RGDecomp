#include "types.h"

/* EffModelObjDrawModelMaybe_2dd2d0 -- 136 B, TWO entries.  The polymorphic sub-object lives at
 * +0x1A0 and its own vptr at +0x1B0 within it (vtable read at o+0x350). */

struct SubB2DD { u8 pad[0x1B0]; };
class Sub2DD : public SubB2DD {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15(f32);
};

struct Out2DD { u8 pad000[0x1A0]; Sub2DD m1A0; };

extern "C" void ModelSetScale_150ff0(void *, void *);
extern "C" void ModelSetPos_151110(void *, void *);
extern "C" void ModelSetRot_151080(void *, void *);
extern "C" s32 GetCurrentScene_1f5be0(void);
extern "C" f32 GameSceneGetTimeStep_1ceba0(s32);

extern "C" void EffModelObjDrawModelMaybe_2dd2d0(Out2DD *o) { o->m1A0.v7(); }

extern "C" void func_002DD2D0_e1(Out2DD *o)
{
    ModelSetScale_150ff0(&o->m1A0, (u8 *)o + 0x60);
    ModelSetPos_151110(&o->m1A0, (u8 *)o + 0x40);
    ModelSetRot_151080(&o->m1A0, (u8 *)o + 0x50);
    o->m1A0.v15(GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0()));
}
