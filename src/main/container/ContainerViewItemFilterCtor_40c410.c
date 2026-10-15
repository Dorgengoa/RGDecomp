#include "types.h"

extern s32 ContainerViewItemFilterInit_40c380(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472250[];
extern u8 D_004792E0[];
extern u8 D_00479410[];

struct Obj0;

struct Obj0 {
    void *m00;
};

struct Obj0 *ContainerViewItemFilterCtor_40c410(struct Obj0 *p0)
{
    s32 r0;

    p0->m00 = D_00472250;
    p0->m00 = D_00479410;
    p0->m00 = D_004792E0;
    r0 = ContainerViewItemFilterInit_40c380();
    return p0;
}
