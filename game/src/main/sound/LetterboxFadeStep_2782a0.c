/* rgp:protos */
#define RGP_SELF_LetterboxFadeStep_2782a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Fields: +0x08 step, +0x0C value, +0x10 limit, +0x1C delay counter. */

/*rgp*/
/*rgp*/

typedef struct Fade {
    u8  pad00[8];
    f32 step;   /* +0x08 */
    f32 cur;    /* +0x0C */
    f32 lim;    /* +0x10 */
    u8  pad14[8];
    s32 wait;   /* +0x1C */
} Fade;

void LetterboxFadeStep_2782a0(Fade *f)
{
    if (f->step == 0.0f) {
        return;
    }
    if (f->wait > 0) {
        f->wait = f->wait - 1;
        return;
    }
    f->cur = f->cur + f->step;
    if (f->cur <= 0.0f) {
        f->cur = 0.0f;
    }
    if (0.0f < f->step) {
        if (f->cur > f->lim) {
            f->cur = f->lim;
        }
    }
    if (0.0f > f->step) {
        if (f->cur < f->lim) {
            f->cur = f->lim;
        }
    }
    MapMgrCaptionSetOffsetY_1e2640(GetMapMgr_201a90(), (s32)(-80.0f * f->cur));
}
