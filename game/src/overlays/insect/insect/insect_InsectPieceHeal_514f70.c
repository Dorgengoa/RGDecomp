/* rgp:protos */
#define RGP_SELF_insect_InsectPieceHeal_514f70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514F70 -- 92 bytes.  A clamped add of `n` to the s16 counter at
 * +0x1C, capped at the s16 limit at +0x1E, then a notify and the DELTA
 * actually applied is returned.  The clamp compare lands in `$at`
 * (`slt $1, $17, $2`) -- the at-compare-class shape. */
typedef struct Gauge {
    u8  pad00[0x1C];
    s16 f1C;                        /* +0x1C */
    s16 f1E;                        /* +0x1E */
} Gauge;

/*rgp*/

s32 insect_InsectPieceHeal_514f70(Gauge *g, s32 n)
{
    s16 cur;
    s16 max;
    s32 v;

    if (n <= 0) {
        return 0;
    }
    cur = g->f1C;
    max = g->f1E;
    v = cur + n;
    if (max <= v) {
        v = max;
    }
    insect_InsectPieceSetHp_512ee0(g, v);
    return v - cur;
}
