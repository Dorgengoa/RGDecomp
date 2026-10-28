/* rgp:protos */
#define RGP_SELF_DoorGlareParamsInit_1ce8a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void * strcpy(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045B0A0[];
extern f32 D_0047D1CC;

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
    s32 m24;
    f32 m28;
    s32 m2C;
    s32 m30;
};

void * DoorGlareParamsInit_1ce8a0(struct Obj0 *p0)
{ void * rgp_v0 = 0;
    f32 t0;

    (rgp_v0 = strcpy(p0, D_0045B0A0));
    p0->m20 = 0x3F800000;
    t0 = D_0047D1CC;
    p0->m24 = 0;
    p0->m28 = t0;
    p0->m2C = 0;
    p0->m30 = 0;
return rgp_v0; }
