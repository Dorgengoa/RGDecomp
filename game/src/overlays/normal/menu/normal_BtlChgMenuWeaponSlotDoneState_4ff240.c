/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuWeaponSlotDoneState_4ff240 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FF240 -- the party-select scene's opener.  `$5` is the state
 * flag; the entity root is fetched FIRST (its null exit returns 0 before the
 * flag is even tested), and the roster handle from normal_FUN_00505F90 is
 * reused for both func_3C2FB0 and normal_FUN_004F4DC0, which is why retail
 * reuses the root's register for it. */

typedef struct Root { u8 pad00[0x18]; s32 f18; } Root;

extern u8 normal_D_00527020[];

extern void *D_00484454;          /* gp - 0xD1C */
extern void *D_00484498;          /* gp - 0xCD8 */
extern void *D_0048449C;          /* gp - 0xCD4 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuWeaponSlotDoneState_4ff240(void *a, s32 b)
{
    Root *root;
    s32   n;

    root = ((Root *)GetGameData_1fede0());
    if (root == 0) {
        return 0;
    }
    if (b != 0) {
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x3E, 0, 1);
        UiSetWidgetVisible_290010(D_0048449C, 0x2B, 0, -1);
        normal_BtlChgMenuCursorShow_503730(0);
        normal_FieldHudPanelSelectHide_4f4eb0(normal_D_00527020, -1);
        n = normal_BtlChgPageGetMember_505f90(D_00484454);
        if (PartyGetSlotChara_3c2fb0(root->f18, n) == 0) {
            return 0;
        }
        normal_FieldHudPanelSelectRaise_4f4dc0(normal_D_00527020, n);
    }
    StateMachineSetState_28ede0(D_00484498, 0x5600, 0);
    return 1;
}
