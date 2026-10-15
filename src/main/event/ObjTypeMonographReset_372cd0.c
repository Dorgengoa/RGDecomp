#include "types.h"

extern void EvObjReset_2f9eb0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xE0];
    s32 mE0;
    s32 mE4;
    s32 mE8;
    s32 mEC;
    s32 mF0;
    s32 mF4;
    s32 mF8;
    s32 mFC;
    s32 m100;
    s32 m104;
};

void ObjTypeMonographReset_372cd0(struct Obj0 *p0)
{
    EvObjReset_2f9eb0(p0);
    p0->mE0 = 0;
    p0->mE4 = 0;
    p0->mE8 = 0;
    p0->mEC = 0;
    p0->mF0 = 0;
    p0->mF4 = 0;
    p0->mF8 = 0;
    p0->mFC = 0;
    p0->m100 = 0;
    p0->m104 = 0xBF800000;
}
