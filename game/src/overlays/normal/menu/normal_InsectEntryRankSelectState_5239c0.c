/* rgp:protos */
#define RGP_SELF_normal_InsectEntryRankSelectState_5239c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005239C0 -- the 0x7531/0x7533/0x7534 request driver on the static
 * widget normal_D_005281C0.  frame -0x30 = save area only ($16/$17 sq + $31 sd).
 *
 * `addiu $6,$0,1` at 0x00523A14 is BOTH the `st == 1` comparand and the third
 * argument of the two func_28EDE0 calls -- one materialised constant, shared.
 * `lh $6,-0x79C($28)` is func_3CC9C0's `s16` PARAMETER narrowing a gp s32 in
 * one instruction; the register-resident `n` at the second call has to take
 * the `dsll32/dsra32 ..,16` form of the same narrowing.
 * `ld $3,0x160($3)` makes the limit an s64, so `n > p->f18->f160` promotes
 * `n` with the `dsll32/dsra32 ..,0` sign extension.
 *
 * The 1.9f at _gp-0x7E14 is a .lit4 POOL ENTRY: spelled `extern f32 D_0047D35C`
 * the object is FOUR bad words, all of them an order permutation around the
 * `sw $0,-0x7A0($28)` (the extern's load is pinned against that store's alias
 * hazard).  As the literal the schedule is retail's; scored through the pool
 * retarget (build/dv_oslit_nu06.py).
 */

typedef struct Sub { u8 pad00[0x160]; s64 f160; } Sub;
typedef struct Ctx { u8 pad00[0x10]; s32 f10; u8 pad14[4]; Sub *f18; } Ctx;
typedef struct Hnd { u8 pad00[0x12]; s16 f12; } Hnd;

extern u8 normal_D_005281C0[];
extern u8 normal_D_00528180[];
extern u8 D_004B2570[];

extern f32 D_0047D7D4;            /* gp - 0x799C */
extern s32 D_004807C4;            /* gp - 0x49AC */
extern s32 D_004849A8;            /* gp - 0x7C8  */
extern s32 D_004849D0;            /* gp - 0x7A0  */
extern s32 D_004849D4;            /* gp - 0x79C  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_InsectEntryRankSelectState_5239c0(void *a, s32 b)
{
    s32  st;
    Hnd *h;
    Ctx *p;
    s32  n;
    s32  d;
    s32  v;

    if (b != 0) {
        UiEntryListSelectByTag_28ea90(normal_D_005281C0, 0x7531, 0);
    }
    st = MenuGridCursorInput_28e170(normal_D_005281C0, D_004B2570, 4, 0);
    h = ((Hnd *)UiEntryListGetCurrentData_28ec60(normal_D_005281C0));
    if (st == 1) {
        p = ((Ctx *)GetGameData_1fede0());
        if (p == 0) {
            return 0;
        }
        d = 5 - D_004807C4;
        if (d < 0) {
            d = 0;
        }
        v = 6 - (h->f12 + d);
        D_004849D4 = v;
        n = normal_InsectEntryGetFee_524220(v);
        if (!(p->f18->f160 < n)) {
            D_004849D0 = 0;
            UiSetWidgetColor_2905b0(normal_D_00528180, 2, 1.9f, 1.9f, 1.9f, -1.0f);
            UiFadeWidgetColor_2904e0(normal_D_00528180, 2, 1.0f, 1.0f, 1.0f, -1.0f, D_0047D7D4);
            StateVarSet_3cc9c0(p->f10, 6, D_004849D4, 0);
            StateVarSet_3cc9c0(p->f10, 0x1D, n, 0);
            StateMachineSetState_28ede0(&D_004849A8, 0x7533, 1);
        } else {
            D_004849D4 = -1;
            StateMachineSetState_28ede0(&D_004849A8, 0x7534, 1);
        }
    } else if (st == 2) {
        StateMachineSetState_28ede0(&D_004849A8, 0x7533, 1);
    }
    return 1;
}
