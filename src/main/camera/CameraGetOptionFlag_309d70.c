#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern void * ObjRecGetLiveObject_1c3bc0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x274];
    s32 m274;
};

s32 CameraGetOptionFlag_309d70(void)
{
    s32 r0;
    struct Obj0 *r1;
    s32 t0;

    r0 = GetCurrentScene_1f5be0();
    r1 = ObjRecGetLiveObject_1c3bc0(r0, 1);
    if (r1 == 0) {
        return 0;
    }
    t0 = r1->m274;
    return t0;
}
