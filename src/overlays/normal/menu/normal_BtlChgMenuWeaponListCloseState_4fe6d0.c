#include "types.h"
/* normal 0x004FE6D0 -- close arm for widgets 0x41 / 0x21; the record read at
 * +0x14 stays AT ITS USE as normal_FUN_004F4EB0's second argument. */

typedef struct Hdl { u8 pad00[0x14]; s16 f14; } Hdl;

extern void    *D_0048449C;       /* gp - 0xCD4 */
extern void    *D_004844A0;       /* gp - 0xCD0 */
extern void    *D_00484498;       /* gp - 0xCD8 */
extern const u8 D_00527020[];

extern void  func_291110(void *p, s32 id, s32 c, s32 d);
extern Hdl  *func_28EA40(void *p, s32 id);
extern void  normal_FieldHudPanelSelectHide_4f4eb0(const u8 *p, s32 n);
extern void  normal_FieldHudPanelSelectRaise_4f4dc0(const u8 *p, s32 n);
extern void  func_28EDE0(void *p, s32 id, s32 a);

s32 normal_BtlChgMenuWeaponListCloseState_4fe6d0(void *unused, s32 show)
{
    if (show != 0) {
        func_291110(D_0048449C, 0x41, 0, 1);
        normal_FieldHudPanelSelectHide_4f4eb0(D_00527020, func_28EA40(D_004844A0, 0x55F2)->f14);
        normal_FieldHudPanelSelectRaise_4f4dc0(D_00527020, -1);
        func_291110(D_0048449C, 0x21, 0, 1);
        func_28EDE0(D_00484498, 0x55F6, 0);
    }
    return 1;
}
