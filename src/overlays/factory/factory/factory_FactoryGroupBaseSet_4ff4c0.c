#include "types.h"

/* factory.bin overlay, 0x004FF4C0 -- construct one placement record: run the
 * base setup, then fill the four fields.  108 bytes, 28 instructions, no
 * conditional branches.
 *
 * * One of a three-member forwarder family found by ranking the OPEN population
 * against ITSELF: `004FF3D0` calls this one through a thunk and `004FF450`
 * calls `004FF3D0` and returns its first argument.  All three take the same
 * five parameters and all three park every one of them in a callee-saved
 * register across the leading call, which is what makes them 0x60 frames.
 */

typedef struct Rec {
    s32 f00;
    s16 f04;
    s16 f06;
    s16 f08;
} Rec;

extern void factory_FactoryGroupBaseReset_4ff530(void);

void factory_FactoryGroupBaseSet_4ff4c0(Rec *o, s16 a, s32 b, s16 c, s16 d)
{
    factory_FactoryGroupBaseReset_4ff530();
    o->f04 = a;
    o->f00 = b;
    o->f06 = c;
    o->f08 = d;
}
