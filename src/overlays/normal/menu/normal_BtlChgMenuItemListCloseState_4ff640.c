#include "types.h"
/* normal 0x004FF640 -- f(void *, s32) opener guarded on `b`.  func_28EA40's
 * record is read AT ITS USE (the `lh 0x14` sits in the argument slot), so it
 * must not be named. */

extern const u8 D_00527020;

extern void *D_00484498;          /* gp - 0xCD8 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern void *D_004844A0;          /* gp - 0xCD0 */

typedef struct Rec { u8 pad000[0x14]; s16 f014; } Rec;

extern void  func_291110(void *w, s32 id, s32 a, s32 b);
extern Rec  *func_28EA40(void *w, s32 id);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern void  normal_FieldHudPanelSelectHide_4f4eb0(const u8 *p, s32 a);
extern void  normal_FieldHudPanelSelectRaise_4f4dc0(const u8 *p, s32 a);

s32 normal_BtlChgMenuItemListCloseState_4ff640(void *a, s32 b)
{
    if (b != 0) {
        func_291110(D_0048449C, 0x41, 0, 1);
        normal_FieldHudPanelSelectHide_4f4eb0(&D_00527020, func_28EA40(D_004844A0, 0x55F2)->f014);
        normal_FieldHudPanelSelectRaise_4f4dc0(&D_00527020, -1);
        func_291110(D_0048449C, 0x21, 0, 1);
        func_28EDE0(D_00484498, 0x55F6, 0);
    }
    return 1;
}
