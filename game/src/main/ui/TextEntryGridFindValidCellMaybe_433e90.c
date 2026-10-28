/* rgp:protos */
#define RGP_SELF_TextEntryGridFindValidCellMaybe_433e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma divbyzerocheck on
#pragma opt_propagation off

/*rgp*/

/* Walk a 29-column grid from pos by step until a stop cell ('1', 'A'-'D').
   wrap == 0: horizontal walk, wraps within the starting row.
   wrap != 0: vertical walk over 6 rows, wraps top <-> bottom.
   MATCH levers (s88m): `cur = pos` s16 local + opt_propagation off = the
   `daddu v1,s0` copy feeding the row/col divs; `pos += (s16)step` = the
   narrowed `addu v0,s4,s2` (no re-ext of pos); st/w assigned after the
   declarations, rem0 declared before lo/hi. */
s16 TextEntryGridFindValidCellMaybe_433e90(s32 ctx, s8 *map, s16 pos, s16 wrap, s16 step)
{
    s32 p0 = pos;
    s32 row = p0 / 29;
    s32 rem0 = p0 % 29;
    s32 lo = row * 29;
    s32 hi = lo + 28;
    s32 w;
    s32 st;
    s16 cur;
    s32 crow;
    s32 crem;
    s32 nrow;
    s8 c;

    st = step;
    w = wrap;
    for (;;) {
        cur = pos;
        TextEntryGridProbeNop_434050();
        c = map[cur];
        if (c == '1' || c == 'A' || c == 'B' || c == 'C' || c == 'D') {
            break;
        }
        crow = pos / 29;
        crem = pos % 29;
        pos += (s16)step;
        nrow = pos / 29;
        if (w == 0) {
            if (nrow != crow) {
                if (nrow < crow) {
                    pos = hi;
                } else {
                    pos = lo;
                }
            }
        } else if (nrow < 0) {
            pos = crem + 0x91;
        } else if (nrow >= 6) {
            pos = rem0;
        }
    }
    return pos;
}
