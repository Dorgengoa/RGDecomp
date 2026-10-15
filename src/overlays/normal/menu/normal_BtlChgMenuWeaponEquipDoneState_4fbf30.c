#include "types.h"
/* normal 0x004FBF30 -- close arm for widget 0x49; $4 is unused, the guard is
 * on the SECOND parameter and shares the prologue's `sd $31` delay slot. */

extern void    *D_0048449C;       /* gp - 0xCD4 */
extern void    *D_00484498;       /* gp - 0xCD8 */
extern const u8 D_005278E0[];

extern void func_291110(void *p, s32 id, s32 c, s32 d);
extern void func_28D820(const void *p, s32 a);
extern void func_28EDE0(void *p, s32 id, s32 a);

s32 normal_BtlChgMenuWeaponEquipDoneState_4fbf30(void *unused, s32 show)
{
    if (show != 0) {
        func_291110(D_0048449C, 0x49, 0, 1);
    }
    func_28D820(D_005278E0, 0x28);
    func_28EDE0(D_00484498, 0x5602, 0);
    return 1;
}
