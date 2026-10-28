/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuStep_5115c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005115C0 -- two gp objects gate the teardown; states 9 and 10 run
 * the same call from two SEPARATE arms, which retail does not tail-merge.
 *
 * s32/nc32a: the whole residue was ONE COLOUR -- retail's second `||` operand
 * is loaded into $4, ours into $2.  It is $4 because `func_28ED70` TAKES the
 * guarded pointer: the guard's own load IS the argument setup, which is why
 * retail's `jal func_28ED70` has a `nop` delay slot (a0 already live) and why
 * no spelling of the guard could ever reach the register.  The draft declared
 * `func_28ED70(void)`; every other merged caller on four overlays declares
 * `func_28ED70(void *)`.  Fixing the SIGNATURE closed the unit. */
typedef struct N {
    u8 pad000[0x14];
    u8 f14;
} N;

extern void *D_004846B8;          /* gp - 0xAB8 */
extern void *D_004846B4;          /* gp - 0xABC */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_SpaceMenuStep_5115c0(void)
{
    s32 st;

    if (D_004846B8 == NULL || D_004846B4 == NULL) {
        return 1;
    }
    StateMachineUpdate_28ed70(D_004846B4);
    normal_SpaceMenuUpdate_512070(D_004846B8);
    st = ((N *)D_004846B8)->f14;
    if (st == 9) {
        StateMachineSetState_28ede0(D_004846B4, 6, 1);
    } else if (st == 0xA) {
        StateMachineSetState_28ede0(D_004846B4, 6, 1);
    }
    MapMgrWarpMenuFadeStep_1e2690(GetMapMgr_201a90());
    return 1;
}
