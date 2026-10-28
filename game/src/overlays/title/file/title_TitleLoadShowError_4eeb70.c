/* rgp:protos */
#define RGP_SELF_title_TitleLoadShowError_4eeb70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EEB70 -- store a halfword, then tail-call into main
 * with a gp-relative pointer and two constants.
 */

extern s16 D_00484204;
extern void *D_004841E0;
/*rgp*/

void title_TitleLoadShowError_4eeb70(s16 v)
{
    D_00484204 = v;
    StateMachineSetState_28ede0(D_004841E0, 0xA, 0);
}
