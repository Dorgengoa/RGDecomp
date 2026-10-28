/* rgp:protos */
#define RGP_SELF_factory_FactoryPartGroupInit_4fecc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FECC0 -- build one placement plan from a full
 * parameter list: run the base constructor, hand the first four values to the
 * record ctor, then drop the remaining twenty-one into the body.
 * 324 bytes, 84 instructions, 0 conditional branches, 2 calls.
 *
 * ** TWENTY-SEVEN parameters.  Eight integers arrive in `$4`-`$11`, the two
 * floats in `$f12`/`$f13` on their OWN sequence, and the remaining seventeen
 * integers in eight-byte stack slots from `caller_sp + 0`, which with a 0xA0
 * frame is `0xA0($29)` through `0x120($29)` ([[im-eabi-stack-arguments]]).
 * The float pair sits BETWEEN `$10` and `$11` in the declaration -- the store
 * order 0x14/0x15/0x18/0x1C/0x20 is what says so, and it is the only evidence
 * there is, since the two register files are filled independently.
 *
 * * Every stack argument is read with `lw`, so every one is `s32`; an `s64`
 * would read the whole slot.
 */

typedef struct Plan {
    u8  pad00[0x14];
    s8  f14;
    s8  f15;
    u8  pad16[0x2];
    f32 f18;
    f32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
    s32 f50;
    s32 f54;
    s32 f58;
    s32 f5C;
    s32 f60;
    s32 f64;
} Plan;                                        /* 0x68 */

/*rgp*/
/*rgp*/

void factory_FactoryPartGroupInit_4fecc0(Plan *o, s16 a, s32 b, s16 c, s16 d, s8 e, s8 f,
                          f32 x, f32 y, s32 g,
                          s32 h00, s32 h01, s32 h02, s32 h03, s32 h04, s32 h05,
                          s32 h06, s32 h07, s32 h08, s32 h09, s32 h10, s32 h11,
                          s32 h12, s32 h13, s32 h14, s32 h15, s32 h16)
{
    factory_FactoryPartGroupReset_4fee10(o);
    factory_FactoryGroupBaseSet_4ff4c0(o, a, b, c, d);
    o->f14 = e;
    o->f15 = f;
    o->f18 = x;
    o->f1C = y;
    o->f20 = g;
    o->f24 = h00;
    o->f28 = h01;
    o->f2C = h02;
    o->f30 = h03;
    o->f34 = h04;
    o->f38 = h05;
    o->f3C = h06;
    o->f40 = h07;
    o->f44 = h08;
    o->f48 = h09;
    o->f4C = h10;
    o->f50 = h11;
    o->f54 = h12;
    o->f58 = h13;
    o->f5C = h14;
    o->f60 = h15;
    o->f64 = h16;
}
