#include "types.h"

extern s32 ModelMeshMode1InitMaybe_164b10(void *, void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0046FFE0[];
extern u8 D_00470000[];
extern u8 D_00470070[];
extern u8 D_004701C0[];
extern u8 D_004709C8[];
extern u8 D_00470E60[];
extern u8 D_00470EA0[];

struct Obj0;

struct Obj0 {
    void *m00;
    s32 m04;
    s32 m08;
    u8 pad00C[0x54];
    void *m60;
    u8 pad064[0x4C];
    void *mB0;
};

struct Obj0 *EffQuadResCtor_1a8110(struct Obj0 *p0)
{
    s32 r0;

    p0->m00 = D_004709C8;
    p0->m00 = D_00470EA0;
    p0->m08 = 0;
    p0->m04 = 0;
    p0->m00 = D_00470E60;
    p0->m60 = D_00470070;
    p0->m60 = D_004701C0;
    p0->mB0 = D_00470000;
    p0->mB0 = D_0046FFE0;
    r0 = ModelMeshMode1InitMaybe_164b10((struct Obj0 *)((u8 *)p0 + 0x10), D_004701C0, D_00470070);
    return p0;
}
