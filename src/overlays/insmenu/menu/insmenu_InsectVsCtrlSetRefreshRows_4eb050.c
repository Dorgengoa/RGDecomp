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

extern const u8 D_004FA180[];
extern const u8 D_004B27E0;
extern u8 D_00484314[2];        /* gp - 0xE5C */
extern void *D_004842FC;        /* gp - 0xE74 */

extern s32  func_184960(const void *a);
extern void func_28F930(const void *a, s32 id, s32 icon, s32 row);
extern s32  func_28AA30(void *a, s32 n);
extern void func_28F510(const void *a, s32 id, s32 text, s32 row);

void insmenu_InsectVsCtrlSetRefreshRows_4eb050(void)
{
    u8 *slot;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (func_184960(&D_004B27E0) == 0) {
            D_00484314[i] = 0;
        }
        slot = &D_00484314[i];
        if (*slot == 0) {
            func_28F930(D_004FA180, 0x44, 0xE8, i + 1);
        } else {
            func_28F930(D_004FA180, 0x44, 0x104, i + 1);
        }
        func_28F510(D_004FA180, 0xC, func_28AA30(D_004842FC, *slot + 8), i + 2);
    }
}
