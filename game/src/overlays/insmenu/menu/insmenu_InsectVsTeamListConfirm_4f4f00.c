/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamListConfirm_4f4f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F4F00 (200 bytes) -- commit the picked entry: if either lookup
 * accepts it the panel bounces, otherwise the scene is handed over.
 *
 * ★ `addiu $4, $0, 0x6` in the first `bnel`'s delay slot is the shared arm's
 * first instruction duplicated -- the two lookups are an `||`, not two `if`s.
 * ★ `sh $0, -0xE30($28)` rides the guard's delay slot because the zero is
 * stored BEFORE the test in the source. */

typedef struct Panel Panel;
struct Panel {
    u8  pad00[0x16];
    s16 field16;
};

typedef struct Widget Widget;
struct Widget {
    u8  pad00[0x16];
    s16 field16;
    u8  pad18[2];
    s16 field1A;
};

typedef struct Scene Scene;

extern u8 insmenu_D_004FA1A0[];
extern s16 D_00484340;          /* gp - 0xE30 */
extern s16 D_0048435C;          /* gp - 0xE14 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsTeamListConfirm_4f4f00(Panel *p)
{
    Widget *w;

    w = ((Widget *)UiEntryListFindByTag_28ea40(insmenu_D_004FA1A0, 0x88BB));
    D_00484340 = 0;
    if (w != 0) {
        D_00484340 = w->field1A + w->field16;
    }
    D_0048435C = p->field16;
    if (SaveSlotEntryIsBrokenAt_373540(((Scene *)insmenu_InsectVsGetSaveCtx_4f3850()), D_00484340) != 0 ||
        SaveSlotEntryIsNoSpaceAt_373480(((Scene *)insmenu_InsectVsGetSaveCtx_4f3850()), D_00484340) != 0) {
        PlayMenuSeThunk_289ef0(6);
        return 0;
    }
    ReturnZero_207fe0();
    PlayMenuSeThunk_289ef0(5);
    SaveMgrSetSlot_37b9c0(D_00484340);
    UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88BF, 1);
    return 1;
}
