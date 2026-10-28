/* rgp:protos */
#define RGP_SELF_InsectCageMenuMoveSlotOpen_38d070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same init-sequence shape as sibling src/p20f/InsectCageMenuSwitchCageOpen_38caa0.c (D_00483304,
   D_00483334, strcpy(D_00483304+0x200, InsectCageMenuMsgLookup_389d30(K)), UiFitCenterWindow_388270,
   InsectCageMenuSetCursorVisible_389d00, InsectCageMenuSetCursorTarget_389790 all reused with the same types there).
   InsectCageMenuGetMoveTargetCageItem_38d4b0 is declared void by its own already-admitted definition
   (src/wrappers/InsectCageMenuGetMoveTargetCageItem_38d4b0.c) but its last inner call (InsectCageMenuGetCageItem_391060,
   also void) never touches $2, so it incidentally still carries
   InsectCageMenuGetMoveTargetCage_38d4e0's return value through to any caller that consumes it --
   declared s32 here to capture that. */

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcpy(s32, s32);
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00483304;
extern s16 D_00483334;

typedef struct Obj {
    u8 pad000[0xA];
    s16 fA;
    u8 pad00C[0x6];
    s16 f12;
} Obj;

s32 InsectCageMenuMoveSlotOpen_38d070(Obj *arg0)
{
    s16 v;

    D_00483334 = 0;
    v = InsectRecSlotCountItems_3cfb80(InsectCageMenuGetMoveTargetCageItem_38d4b0());
    arg0->fA = v;
    if (v >= 5) {
        arg0->fA = 4;
    }
    v = arg0->fA;
    arg0->f12 = v;
    if (v >= 5) {
        arg0->f12 = 0;
    }
    strcpy(D_00483304 + 0x200, InsectCageMenuMsgLookup_389d30(0x516));
    UiFitCenterWindow_388270(0x754E, 0);
    InsectCageMenuSetCursorVisible_389d00(1);
    InsectCageMenuSetCursorTarget_389790(3, arg0, 1);
    return 1;
}
