/* rgp:protos */
#define RGP_SELF_title_TitleGetResult_4ec7d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EC7D0 -- two guards and a call pair; three exits
 * return the same halfword global, two return 0.
 *
 * ★ Every `beql` here branches to the SHARED EPILOGUE carrying its result in
 * the delay slot, so the zero exits are the FALL-THROUGH and the work is the
 * positively-guarded arm.  Spelling the first test as `if (x == 0) return 0;`
 * makes mwcc invert it to `bnezl` and jump around an inline zero -- right
 * length, 20 of 26 words wrong.
 */

extern void *D_00484160;
extern s16 D_0048418C;
/*rgp*/
/*rgp*/
/*rgp*/

s16 title_TitleGetResult_4ec7d0(void)
{
    if (D_00484160 != 0) {
        if (D_0048418C == 2) {
            if (title_TitleLoadIsDone_4ef3a0() != 0) {
                return D_0048418C;
            }
        } else {
            NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32D);
            return D_0048418C;
        }
    }
    return 0;
}
