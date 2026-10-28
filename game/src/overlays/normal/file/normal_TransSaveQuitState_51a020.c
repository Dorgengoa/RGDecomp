/* rgp:protos */
#define RGP_SELF_normal_TransSaveQuitState_51a020 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051A020 -- two guarded blocks around a widget teardown.
 * ⚠ `$4` is never read: the first parameter leaves no trace, so its presence
 * is inferred from the callers rather than measured.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
extern u8 normal_D_00526818;
extern u8 normal_D_00527F10;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransSaveQuitState_51a020(void *a, s32 b)
{
    if (b != 0) {
        SaveUiHideWidget_37b460(0x75A2);
        ScreenFadeBlockFadeOutColor_1782a0(&normal_D_00527F10, 0x14, 0.0f, 0.0f, 0.0f);
    }
    if (ScreenFadeBlockIsDone_178110(&normal_D_00527F10) != 0) {
        McPortTypesInvalidateMaybe_373100();
        normal_TransMenuSetOpen_516a40(0);
        TaskSetEnabled_27c2a0(1, &normal_D_00526818);
        SceneOverlayModeOff_288300();
    }
    return 1;
}
