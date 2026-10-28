/* rgp:protos */
#define RGP_SELF_normal_TransSaveQuitConfirmCb_518ae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518AE0 -- enters the shop's confirm step once, then routes to the
 * empty-basket message or the quantity page.  Pass-33 LIST rank: 152 bytes,
 * 38 instructions, TWO conditional branches, 6 calls.
 *
 * `normal_TransSavePanelFade_518700`'s own delay slot is a bare `nop`, so the listing looks
 * argument-free -- its argument is the `addiu $4,$0,0x2` riding the PRECEDING
 * branch-likely slot.  Recorded on normal_ShopMenuItemInfoShow_509520, seen again here.
 *
 * `D_00484820 = 1;` is written before normal_TransSaveShowMsg_519ff0 and fills its slot. */

typedef struct Obj { u8 pad00[0x10]; s16 f10; } Obj;

extern s8    D_00484820;          /* gp - 0x950 */
extern void *D_004847D0;          /* gp - 0x9A0 */
extern void *D_004847D8;          /* gp - 0x998 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 normal_TransSaveQuitConfirmCb_518ae0(Obj *p);

s32 normal_TransSaveQuitConfirmCb_518ae0(Obj *p)
{
    if (D_00484820 != 0) {
        return 1;
    }
    D_00484820 = 1;
    normal_TransSaveShowMsg_519ff0(-1);
    normal_TransSaveYesNoCursorBob_5188c0(0, 1, 0);
    if (p->f10 == 0) {
        SaveMgrRelease_37bb70();
        StateMachineSetState_28ede0(D_004847D0, 8, 0);
        return 1;
    }
    normal_TransSavePanelFade_518700(2);
    UiEntryListSelectByTag_28ea90(D_004847D8, 2, 0);
    return 1;
}
