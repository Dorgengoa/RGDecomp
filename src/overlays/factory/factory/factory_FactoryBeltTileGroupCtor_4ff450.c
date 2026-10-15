#include "types.h"

/* factory.bin overlay, 0x004FF450 -- outermost member of the forwarder family:
 * run its own setup, forward to `004FF3D0`, and RETURN the record pointer.
 * 112 bytes, 28 instructions, no conditional branches.
 *
 * * The trailing `daddu $2, $20, $0` is the returned `o`, re-read from the
 * callee-saved copy rather than from `$4` -- this is a C++ constructor's
 * `return this`, and the first argument has to survive the forwarded call for
 * it, which is why `o` is in `$20` and not `$4`.
 */

typedef struct Rec {
    s32 f00;
    s16 f04;
    s16 f06;
    s16 f08;
} Rec;

extern void factory_FactoryBeltTileGroupInit_4ff3d0(Rec *o, s16 a, s32 b, s16 c, s16 d);
extern void factory_FactoryGroupBaseCtor_4ff560(void);

Rec *factory_FactoryBeltTileGroupCtor_4ff450(Rec *o, s16 a, s32 b, s16 c, s16 d)
{
    factory_FactoryGroupBaseCtor_4ff560();
    factory_FactoryBeltTileGroupInit_4ff3d0(o, a, b, c, d);
    return o;
}
