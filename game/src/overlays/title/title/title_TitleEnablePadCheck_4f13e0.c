/* rgp:protos */
#define RGP_SELF_title_TitleEnablePadCheck_4f13e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004F13E0 -- set a byte flag, then tail-call into main
 * with the ABSOLUTE address of a main-image object.
 *
 * The lui/addiu pair is %hi/%lo, so the object has to be `const` -- a plain
 * extern comes out gp-relative and two words short.
 */

extern u8 D_004842A4;
extern u8 D_004B2570;
/*rgp*/

void title_TitleEnablePadCheck_4f13e0(void)
{
    D_004842A4 = 1;
    PadWaitReady_1849e0((void *)&D_004B2570);
}
