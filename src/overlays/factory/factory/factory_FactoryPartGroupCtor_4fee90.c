#include "types.h"

/* factory.bin overlay, 0x004FEE90 -- the outer plan constructor: run the other
 * base reset, forward the whole twenty-seven-parameter list to
 * `factory_FactoryPartGroupInit_4fecc0`, and hand the object back.
 * 328 bytes, 84 instructions, 0 conditional branches, 2 calls.
 *
 * * TWIN of `factory_FactoryPartGroupInit_4fecc0`.  Its seventeen stack arguments arrive at
 * `0x130($29)` and are re-marshalled to `0x0($29)`; the `lw` in and `sd` out
 * are the same `s32` in an eight-byte EABI slot seen from both sides
 * ([[im-eabi-stack-arguments]]), not an `s64`.
 *
 * * It RETURNS the object -- `daddu $2, $22, $0` after the forwarding call --
 * which `factory_FactoryPartGroupInit_4fecc0` does not.
 */

typedef struct Plan {
    u8 pad00[0x68];
} Plan;                                        /* 0x68 */

extern void factory_FactoryGroupBaseCtor_4ff560(Plan *o);
extern void factory_FactoryPartGroupInit_4fecc0(Plan *o, s16 a, s32 b, s16 c, s16 d, s8 e,
                                 s8 f, f32 x, f32 y, s32 g,
                                 s32 h00, s32 h01, s32 h02, s32 h03, s32 h04,
                                 s32 h05, s32 h06, s32 h07, s32 h08, s32 h09,
                                 s32 h10, s32 h11, s32 h12, s32 h13, s32 h14,
                                 s32 h15, s32 h16);

Plan *factory_FactoryPartGroupCtor_4fee90(Plan *o, s16 a, s32 b, s16 c, s16 d, s8 e, s8 f,
                           f32 x, f32 y, s32 g,
                           s32 h00, s32 h01, s32 h02, s32 h03, s32 h04, s32 h05,
                           s32 h06, s32 h07, s32 h08, s32 h09, s32 h10, s32 h11,
                           s32 h12, s32 h13, s32 h14, s32 h15, s32 h16)
{
    factory_FactoryGroupBaseCtor_4ff560(o);
    factory_FactoryPartGroupInit_4fecc0(o, a, b, c, d, e, f, x, y, g,
                         h00, h01, h02, h03, h04, h05, h06, h07,
                          h08, h09, h10, h11, h12, h13, h14, h15,
                          h16);
    return o;
}
