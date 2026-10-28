/* rgp:protos */
#define RGP_SELF_insect_InsectStoryIsRetryMaybe_510480 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510480 -- a predicate.  `xor $2,$2,$3 / sltiu $2,$2,0x1` is the
 * recorded bool-from-an-EQUALITY idiom, and the absence of a trailing
 * `andi $2,$2,0xFF` is what says the return is `s32` and not `u8`.
 * func_31A8D0 and func_1FEDE0 take NO arguments -- $4 is never written in this
 * function and both results are used as pointers. */
typedef struct Root { u8 pad00[0x5F00]; s16 f5F00; } Root;
typedef struct Dev  { u8 pad00[0x10]; void *f10; } Dev;

/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectStoryIsRetryMaybe_510480(void)
{
    Root *g;
    Dev *d;
    s32 r;

    g = ((Root *)InsectBattleGet_31a8d0());
    d = ((Dev *)GetGameData_1fede0());
    StateVarGet_3ccac0(d->f10, 5);
    StateVarGet_3ccac0(d->f10, 6);
    r = ((short)StateVarGet_3ccac0(d->f10, 7));
    return (r + 1) == g->f5F00;
}
