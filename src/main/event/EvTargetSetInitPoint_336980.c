#include "types.h"

extern void EvTargetSetReset_336bb0(void *);
extern void TargetRefSetPoint_2e6710(void *, f32, f32, f32, f32);
extern void TargetRefSetMapNode_2e6370(void *, s32, s32, f32);
extern void TargetRefSetMapObj_2e6470(void *, s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x108];
    f32 m108;
    f32 m10C;
    f32 m110;
    s16 m114;
};

void EvTargetSetInitPoint_336980(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7, f32 fa0, f32 fa1, f32 fa2, f32 fa3, f32 fa4, f32 fa5, f32 fa6)
{
    EvTargetSetReset_336bb0(p0);
    p0->m114 = p1;
    TargetRefSetPoint_2e6710(p0, fa0, fa1, fa2, fa3);
    TargetRefSetMapNode_2e6370((struct Obj0 *)((u8 *)p0 + 0x30), p2, p3, 0.0f);
    TargetRefSetMapObj_2e6470((struct Obj0 *)((u8 *)p0 + 0x60), p4, p5, 0.0f);
    TargetRefSetMapObj_2e6470((struct Obj0 *)((u8 *)p0 + 0x90), p6, p7, 0.0f);
    p0->m108 = fa4;
    p0->m10C = fa5;
    p0->m110 = fa6;
}
