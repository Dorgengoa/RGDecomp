/* rgp:protos */
#define RGP_SELF_normal_TransSaveHighlightOption_519e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00519E70 -- leaf tail call.  D_00480710 is ADDRESS-TAKEN off gp
 * (`addiu $5,$28,-0x4A60`), so it must be declared <= 8 B to stay in small
 * data. */

extern s32 D_00480710;            /* gp - 0x4A60 */

/*rgp*/

void normal_TransSaveHighlightOption_519e70(s32 a)
{
    SaveUiHighlightOption_37b5d0(a, &D_00480710, 0x7559);
}
