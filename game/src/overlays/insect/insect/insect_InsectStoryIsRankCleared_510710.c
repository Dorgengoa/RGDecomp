/* rgp:protos */
#define RGP_SELF_insect_InsectStoryIsRankCleared_510710 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510710 -- 68 bytes.  Two queries against the same handle; the
 * `slt $2,$2,$16` has the SECOND result in rs, so the comparison is
 * `b < a` with the first result named. */

typedef struct Ctx {
    u8  pad00[0x10];
    s32 m10;                        /* +0x10 */
} Ctx;

/*rgp*/
/*rgp*/

s32 insect_InsectStoryIsRankCleared_510710(void)
{
    Ctx *g;
    s32  a;
    s32  b;

    g = ((Ctx *)GetGameData_1fede0());
    a = ((short)StateVarGet_3ccac0(g->m10, 5));
    b = ((short)StateVarGet_3ccac0(g->m10, 6));
    return b < a;
}
