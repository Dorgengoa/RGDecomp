/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFadeStart_50e1e0 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"
/* insect 0x0050E1E0 -- 68 bytes, 17 instructions.  Two parallel byte tables
 * 0x44 apart; the divisor is a variable, so the `bnez`/`break 0,7` trap pair
 * is real and needs the divbyzerocheck pragma.
 * `addu $4, $5, $4` here is the pointer as parameter ONE and the index as
 * parameter TWO -- the INDEX is in rs.  The identical encoding was read the
 * other way round on insect_InsectTeamSlotGetMember_513eb0 (ixa03), so the encoding does NOT
 * fix the parameter order: enumerate both. */

void insect_InsectBattleFadeStart_50e1e0(u8 *p, s32 i, s32 v, s32 d, s32 k)
{
    u8 *q;
    u8 *r;
    s32 t;

    p[i + 0x5EF0] = v;
    q = p + i + 0x5EAC;
    r = p + i + 0x5EF0;
    p[i + 0x5EAC] = d;
    if (k == 1) {
        t = p[i + 0x5EEF];
        *q = (*r - t) / d;
    }
}
