/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsCtrlSetRefreshRows_4eb050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EB050 (200 bytes) -- refresh both save-slot rows: clear the row
 * when the card has gone, then pick its icon and its label.
 *
 * ★ `addiu $2, $28, -0xE5C` appears twice because the array base is
 * recomputed in both arms of the first guard -- one duplicated into the likely
 * slot -- and only then does `addu $17, $2, $16` form the row POINTER, which is
 * callee-saved because it lives across three calls.
 * ★ `lbu $2, 0($17)` three times is one source read per use, the middle one
 * sunk into the `b`'s delay slot. */

extern u8 insmenu_D_004FA180[];
extern u8 D_004B27E0;
extern u8 D_00484314[2];        /* gp - 0xE5C */
extern void *D_004842FC;        /* gp - 0xE74 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsCtrlSetRefreshRows_4eb050(void)
{
    u8 *slot;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (((unsigned char)PadIsAnalogMode_184960(&D_004B27E0)) == 0) {
            D_00484314[i] = 0;
        }
        slot = &D_00484314[i];
        if (*slot == 0) {
            UiSetSpriteU_28f930(insmenu_D_004FA180, 0x44, 0xE8, i + 1);
        } else {
            UiSetSpriteU_28f930(insmenu_D_004FA180, 0x44, 0x104, i + 1);
        }
        UiSetTextString_28f510(insmenu_D_004FA180, 0xC, MsgTableLookup_28aa30(D_004842FC, *slot + 8), i + 2);
    }
}
