#include "types.h"
/* VU0 code as mwcc intrinsics (no inline-assembly blocks): vf0 = (0,0,0,1) bound under
 * vu0_mmi_reg_binding. The empty `if (o) { o = launder(o); }` before the last store emits no
 * code but keeps a basic-block boundary, reproducing the original scheduling. */
#pragma vu0_mmi_reg_binding on
extern unsigned __int128 vz177430 asm("vf0");

/* d = (0,0,0,1) */
#define SPL177430(p, T) if (p) { p = (T *)(s32)(u32)p; }

static inline void UnitVector_177430(void *d)
{
    *(unsigned __int128 *)d = vz177430;
}

extern u8 D_00470090[];
extern u8 D_00470340[];

typedef struct P177430 {
    f32 f0, f4, f8, fC, f10, f14, f18, f1C, f20, f24;
    s32 f28;
} P177430;

class B177430 {
public:
    u8 pad0[0xC0];
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3C(); virtual void v40();
    virtual void Init();
    virtual P177430 *Params();
    virtual void Setup();
    B177430() { Init(); }
};
class O177430 : public B177430 {
public:
    O177430();
    virtual void Init();
    virtual P177430 *Params();
    virtual void Setup();
    u8 padC4[0xD0 - 0xC4];
    u8 vD0[0x10];
    u8 vE0[0x10];
    u8 vF0[0x8];
    f32 fF8;
    u8 padFC[4];
    f32 f100;
    f32 f104;
    s32 f108;
    s32 f10C;
    s32 f110;
    u8 pad114[0x120 - 0x114];
    u8 v120[0x10];
    u8 pad130[0x158 - 0x130];
    s32 f158;
    u8 pad15C[0x184 - 0x15C];
    s32 f184;
};

O177430::O177430()
{
    O177430 *o = this;
    P177430 *p;

    o->f158 = 0;
    o->f184 = 0;
    p = o->Params();
    p->f0 = 100.0f;
    p->f4 = 160.0f;
    p->f8 = 18.0f;
    p->fC = 10.0f;
    p->f14 = 40.0f;
    p->f18 = -15.0f;
    p->f1C = 20.0f;
    p->f20 = -15.0f;
    p->f10 = p->f20;
    p->f24 = 25.0f;
    p->f28 = 0;
    UnitVector_177430(o->vD0);
    UnitVector_177430(o->vE0);
    UnitVector_177430(o->vF0);
    UnitVector_177430((u8 *)o + 0x50);
    UnitVector_177430((u8 *)o + 0x60);
    SPL177430(o, O177430)
    UnitVector_177430(o->v120);
    *(f32 *)((u8 *)o + 0x68) = 1.0f;
    o->fF8 = 1.0f;
    *(s32 *)((u8 *)o + 0x70) = 0;
    o->f108 = 1;
    o->f100 = 8.0f;
    o->f104 = 2.0f;
    o->f10C = 1;
    o->f110 = 0;
    o->Setup();
}
