#include "types.h"

extern void * GetGameData_1fede0(void);
extern void PlayerControlUpdateMaybe_1fc4a0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B2570[];

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x18E];
    s16 m18E;
};

void TaskCharaControl_1fae30(void)
{
    struct Obj0 *r0;
    s16 t1;

    r0 = GetGameData_1fede0();
    t1 = r0->m18->m18E;
    PlayerControlUpdateMaybe_1fc4a0(D_004B2570, t1);
}
