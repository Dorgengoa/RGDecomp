/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsStateAdvance_4ecba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x4ECBA0 -- fetch a handle, pass its +0x24 member on, latch
 * the gp byte flag.  `addiu $2, $0, 0x1` feeds BOTH the `sb`
 * and the return register, so the stored value and the returned
 * value are the same constant. */
/*rgp*/
/*rgp*/
extern u8 D_00484304;
s32 insmenu_InsectVsStateAdvance_4ecba0(void)
{
    RecordAdvanceState_430bf0(*(void **)((u8 *)GetGameData_1fede0() + 0x24), 0);
    D_00484304 = 0x1;
    return 0x1;
}
