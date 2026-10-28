/* rgp:protos */
#define RGP_SELF_title_FUN_004eab00 1
#define RGP_SELF_title_TitleMenuCursorMoveCb_4eaa90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EAA90.  Third of the three slots that hold TWO
 * functions; the one at 0x004EAB00 is unnamed because Ghidra missed it.
 */

extern s16 D_0048416C;
extern s16 D_0048417C;
extern s16 D_00484188;
extern s16 D_0048418C;

/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleMenuCursorMoveCb_4eaa90(void)
{
    if ((D_00484188 == 1) && (D_0048418C == 0) && (D_0048416C != 0)
        && (IsTgsDemoBuild_207f20() == 0)) {
        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 4, 0, 1.0f);
    }
    return 1;
}

s32 title_FUN_004eab00(void)
{
    D_0048417C = 0;
    return 1;
}
