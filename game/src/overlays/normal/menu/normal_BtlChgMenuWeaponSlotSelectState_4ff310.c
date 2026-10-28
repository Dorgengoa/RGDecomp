/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuWeaponSlotSelectState_4ff310 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FF310 -- the shop/party picker's per-frame step.  func_28E170
 * returns the list state (2 = cancelled, 1 = confirmed); the panel handle is
 * fetched unconditionally because the confirmed arm reads its +0x12 row.
 * `$17` is a POINTER to the 0x450 selection pair, not the context pointer:
 * retail materialises `ctx + 0x450` and reads it at displacement 0. */

typedef struct Root  { u8 pad00[0x18]; s32 f18; } Root;
typedef struct Panel { u8 pad00[0x12]; s16 f12; } Panel;
typedef struct Ref   { u8 pad00[0x0C]; s32 f0C; } Ref;
typedef struct Ctx   { u8 pad000[0x450]; s16 f450; s16 f452; } Ctx;

extern Ctx  *D_00484454;          /* gp - 0xD1C */
extern void *D_00484498;          /* gp - 0xCD8 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern void *D_004844A0;          /* gp - 0xCD0 */
extern u8 D_004B2570[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuWeaponSlotSelectState_4ff310(void *a, s32 b)
{
    s32    st;
    Panel *pn;
    s16   *sel;
    Root  *root;
    Ref   *rf;
    s32    n;

    if (b != 0) {
        UiEntryListSelectByTag_28ea90(D_004844A0, 0x55F9, 0);
    }
    st = MenuGridCursorInput_28e170(D_004844A0, D_004B2570, 4, 0);
    pn = ((Panel *)UiEntryListGetCurrentData_28ec60(D_004844A0));
    if (st == 2) {
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x3E, 0, 1);
        StateMachineSetState_28ede0(D_00484498, 0x55F6, 0);
    } else if (st == 1) {
        sel = &D_00484454->f450;
        root = ((Root *)GetGameData_1fede0());
        if (root == 0) {
            return 0;
        }
        n = normal_BtlChgPageGetMember_505f90(D_00484454);
        rf = ((Ref *)PartyGetSlotChara_3c2fb0(root->f18, n));
        if (rf != 0) {
            if (sel[0] != rf->f0C || pn->f12 != sel[1]) {
                ItemIconTexRelease_204c90(sel[0], sel[1]);
                D_00484454->f450 = rf->f0C;
                D_00484454->f452 = pn->f12;
                MenuImgLoadRequest_204d40(D_00484454->f450, D_00484454->f452);
            }
        }
        StateMachineSetState_28ede0(D_00484498, 0x55FF, 0);
    }
    return 1;
}
