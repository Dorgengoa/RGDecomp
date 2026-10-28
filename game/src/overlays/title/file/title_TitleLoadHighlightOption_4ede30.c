/* rgp:protos */
#define RGP_SELF_title_TitleLoadHighlightOption_4ede30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EDE30 -- copy three gp-relative halfwords into a
 * stack buffer and pass it on.  $4 is never written: the incoming argument
 * rides straight through into the call.
 *
 * Ã¢Ëœâ€¦ All three `lh` are issued before all three `sh`, which is ONE LOCAL PER
 * LOAD assigned in the reference's LOAD order -- not pairwise assignment.
 */

extern s16 D_00480410;
extern s16 D_00480412;
extern s16 D_00480414;
/*rgp*/

void title_TitleLoadHighlightOption_4ede30(s16 a)
{
    s16 buf[3];
    s16 x;
    s16 y;
    s16 z;

    x = D_00480410;
    y = D_00480412;
    z = D_00480414;
    buf[0] = x;
    buf[1] = y;
    buf[2] = z;
    SaveUiHighlightOption_37b5d0(a, buf, 0x17);
}
