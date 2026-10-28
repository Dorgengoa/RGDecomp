/* rgp:protos */
#define RGP_SELF_factory_FactoryPartGroupReset_4fee10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004FEE10 -- construct the placement-plan record: run
 * the base reset, then zero the two mode bytes and the whole 20-word body.
 * 124 bytes, 32 instructions, 0 conditional branches, 1 call.
 *
 * * A pure LIST: 24 stores in 32 instructions, which is the shape
 * [[main-pass33-lists]] ranks first and this session ported into
 * `scripts/f_lrank.py`.  Twenty `sw $0` in a row are TWENTY EXPLICIT
 * ASSIGNMENTS -- a struct assignment or a `for` loop is mwcc's copy LOOP and
 * comes out dozens of words short.
 *
 * * `factory_FactoryGroupBaseReset_4ff530` is spelled `(void)`, as `factory_FactoryGroupBaseSet_4ff4c0`
 * already does: the base ctor reads `$4`, which the caller already holds, and
 * declaring the parameter would emit a redundant marshal.
 */

typedef struct Plan {
    u8  pad00[0x14];
    u8  f14;
    u8  f15;
    u8  pad16[0x2];
    s32 f18;
    s32 f1C;
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

void factory_FactoryPartGroupReset_4fee10(Plan *o)
{
    factory_FactoryGroupBaseReset_4ff530((void *)o);
    o->f14 = 0;
    o->f15 = 0;
    o->f18 = 0;
    o->f1C = 0;
    o->f20 = 0;
    o->f24 = 0;
    o->f28 = 0;
    o->f2C = 0;
    o->f30 = 0;
    o->f34 = 0;
    o->f38 = 0;
    o->f3C = 0;
    o->f40 = 0;
    o->f44 = 0;
    o->f48 = 0;
    o->f4C = 0;
    o->f50 = 0;
    o->f54 = 0;
    o->f58 = 0;
    o->f5C = 0;
    o->f60 = 0;
    o->f64 = 0;
}
