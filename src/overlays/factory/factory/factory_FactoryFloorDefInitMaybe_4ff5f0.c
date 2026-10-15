#include "types.h"

/* factory.bin overlay, 0x004FF5F0 -- construct one shaped-region record: run
 * the base reset, then drop the ten incoming fields into it in order.
 * 164 bytes, 44 instructions, 0 conditional branches, 1 call.
 *
 * * A LIST unit, found by ranking the open population on STORE density rather
 * than size ([[main-pass33-lists]], ported here as `scripts/f_lrank.py`).
 *
 * * TEN parameters: eight arrive in `$4`-`$11` and the last two on the stack
 * at `caller_sp + 0` and `+ 8`, which with a 0x90 frame is `0x90($29)` and
 * `0x98($29)` -- [[im-eabi-stack-arguments]].  Both are read with `lw`, so
 * both are `s32`, not `s64`.
 *
 * * The base call is spelled `(void)`, as in `factory_FactoryGroupBaseSet_4ff4c0`: it reads
 * the `$4` the caller already holds.
 */

typedef struct Region {
    s16 f00;
    s8  f02;
    s8  f03;
    s16 f04;
    s16 f06;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
} Region;                                       /* 0x18 */

extern void factory_FactoryFloorDefResetMaybe_4ff6a0(void);

void factory_FactoryFloorDefInitMaybe_4ff5f0(Region *o, s16 a, s8 b, s8 c, s16 d, s16 e,
                          s32 f, s32 g, s32 h, s32 i)
{
    factory_FactoryFloorDefResetMaybe_4ff6a0();
    o->f00 = a;
    o->f02 = b;
    o->f03 = c;
    o->f04 = d;
    o->f06 = e;
    o->f08 = f;
    o->f0C = g;
    o->f10 = h;
    o->f14 = i;
}
