/* rgp:protos */
#define RGP_SELF_insect_InsectBattleSwapSide_50e1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050E1A0 -- 56 bytes, 14 instructions.  A toggle: the flag byte at
 * +0x5EF1 and bit 0 of the state byte at +0x4FBC move together.  The
 * `bnel $3, $0` carries `sb $0, 0x5EF1($4)` -- the TARGET block's own store --
 * so the CLEARING arm is the `else` and the SETTING arm is the fall-through. */

typedef struct Ins {
    u8 pad0000[0x4FBC];
    u8 f4FBC;                       /* +0x4FBC */
    u8 pad4FBD[0x5EF1 - 0x4FBD];
    u8 f5EF1;                       /* +0x5EF1 */
} Ins;

void insect_InsectBattleSwapSide_50e1a0(Ins *o)
{
    if (o->f5EF1 == 0) {
        o->f5EF1 = 1;
        o->f4FBC |= 1;
    } else {
        o->f5EF1 = 0;
        o->f4FBC &= ~1;
    }
}
