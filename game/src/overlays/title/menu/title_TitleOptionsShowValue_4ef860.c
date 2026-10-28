/* rgp:protos */
#define RGP_SELF_title_TitleOptionsShowValue_4ef860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EF860 -- swap the first two arguments depending on
 * which of them the third and fourth match, then tail-call.  The last arm
 * leaves both alone and falls straight into the tail call.
 *
 * $8 is the FIFTH argument on this ABI ($8..$11 are arguments 5-8).
 */

/*rgp*/

void title_TitleOptionsShowValue_4ef860(s32 a, s32 b, s32 c, s32 d, s32 e)
{
    if (a == b) {
        a = d & 0xFFFF;
        b = e & 0xFFFF;
    } else if (a == c) {
        a = e & 0xFFFF;
        b = d & 0xFFFF;
    }
    title_TitleOptionsHighlightPair_4ef890(a, b, c, d, e);
}
