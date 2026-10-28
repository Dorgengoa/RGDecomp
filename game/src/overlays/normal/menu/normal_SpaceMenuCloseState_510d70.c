/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuCloseState_510d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00510D70 -- `beql $5,$0,L / addiu $2,$0,1(slot) / ... / addiu
 * $2,$0,1 / L: jr`.  The return constant is materialised in BOTH arms, which
 * is the recorded duplicated-constant shape rather than one value at a join.
 * ⚠ `$4` is never read: the first parameter leaves no trace here, so its
 * presence is inferred from the callers, not measured.
 * One of the 55 unnamed functions. */
typedef struct Rec {
    u8 pad00[0x14];
    u8 f14;
} Rec;

extern Rec *D_004846B8;

s32 normal_SpaceMenuCloseState_510d70(void *a, s32 b)
{
    if (b != 0) {
        D_004846B8->f14 = 0xB;
    }
    return 1;
}
