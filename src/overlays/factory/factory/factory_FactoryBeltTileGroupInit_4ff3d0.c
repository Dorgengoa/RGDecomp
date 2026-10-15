#include "types.h"

/* factory.bin overlay, 0x004FF3D0 -- the thunked constructor: run the base
 * setup through the external thunk, then forward all five arguments.
 * 108 bytes, 28 instructions, no conditional branches.
 *
 * * Middle member of the `004FF4C0` / `004FF3D0` / `004FF450` forwarder family.
 * Every argument is copied into a callee-saved register BEFORE the leading
 * call and copied back afterwards, so the frame is 0x60 for a function with no
 * locals at all.
 */

typedef struct Rec {
    s32 f00;
    s16 f04;
    s16 f06;
    s16 f08;
} Rec;

extern void factory_FactoryGroupBaseSet_4ff4c0(Rec *o, s16 a, s32 b, s16 c, s16 d);
extern void factory_FactoryGroupBaseResetThunk_4ff530(void);

void factory_FactoryBeltTileGroupInit_4ff3d0(Rec *o, s16 a, s32 b, s16 c, s16 d)
{
    factory_FactoryGroupBaseResetThunk_4ff530();
    factory_FactoryGroupBaseSet_4ff4c0(o, a, b, c, d);
}
