#include "types.h"
/* normal 0x004FF240 -- the party-select scene's opener.  `$5` is the state
 * flag; the entity root is fetched FIRST (its null exit returns 0 before the
 * flag is even tested), and the roster handle from normal_FUN_00505F90 is
 * reused for both func_3C2FB0 and normal_FUN_004F4DC0, which is why retail
 * reuses the root's register for it. */

typedef struct Root { u8 pad00[0x18]; s32 f18; } Root;

extern const u8 D_00527020[];

extern void *D_00484454;          /* gp - 0xD1C */
extern void *D_00484498;          /* gp - 0xCD8 */
extern void *D_0048449C;          /* gp - 0xCD4 */

extern Root *func_1FEDE0(void);
extern void  func_28EDE0(void *p, s32 id, s32 a);
extern void  func_290010(void *p, u16 id, s32 c, s32 d);
extern void  func_291110(void *p, u16 id, s32 c, s32 d);
extern void *func_3C2FB0(s32 a, s32 b);
extern void  normal_BtlChgMenuCursorShow_503730(s32 a);
extern void  normal_FieldHudPanelSelectRaise_4f4dc0(const u8 *p, s32 a);
extern void  normal_FieldHudPanelSelectHide_4f4eb0(const u8 *p, s32 a);
extern s32   normal_BtlChgPageGetMember_505f90(void *p);

s32 normal_BtlChgMenuWeaponSlotDoneState_4ff240(void *a, s32 b)
{
    Root *root;
    s32   n;

    root = func_1FEDE0();
    if (root == 0) {
        return 0;
    }
    if (b != 0) {
        func_291110(D_0048449C, 0x3E, 0, 1);
        func_290010(D_0048449C, 0x2B, 0, -1);
        normal_BtlChgMenuCursorShow_503730(0);
        normal_FieldHudPanelSelectHide_4f4eb0(D_00527020, -1);
        n = normal_BtlChgPageGetMember_505f90(D_00484454);
        if (func_3C2FB0(root->f18, n) == 0) {
            return 0;
        }
        normal_FieldHudPanelSelectRaise_4f4dc0(D_00527020, n);
    }
    func_28EDE0(D_00484498, 0x5600, 0);
    return 1;
}
