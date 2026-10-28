/* rgp:protos */
#define RGP_SELF_insect_InsectStoryCheckMatchBeatenMaybe_510660 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510660 -- 172 bytes, 43 instructions, 6 calls.
 *
 * `slt $1,$16,$2` lands in $at, so the branch-taken condition is NOT a bare
 * `<` with the tested value on the left: the guard is spelled `d > n`
 * (at-compare-class).  Both early `return K` blocks reach the SHARED epilogue
 * through a branch-likely with the constant in the delay slot.
 */

typedef struct H {
    u8  pad00[0x10];
    s32 m10;                        /* +0x10 */
} H;

/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectStoryCheckMatchBeatenMaybe_510660(s32 f)
{
    H  *h;
    s32 b;
    s32 n;

    h = ((H *)GetGameData_1fede0());
    b = ((short)StateVarGet_3ccac0(h->m10, 6)) + 0x13;
    n = ((short)StateVarGet_3ccac0(h->m10, 7));
    if (((short)StateVarGet_3ccac0(h->m10, b)) <= n) {
        if (f != 0) {
            StateVarSet_3cc9c0(h->m10, b, ((short)StateVarGet_3ccac0(h->m10, 7)) + 1, 0);
        }
        return 0;
    }
    return 2;
}
