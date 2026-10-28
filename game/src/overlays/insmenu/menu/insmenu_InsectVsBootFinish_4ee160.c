/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsBootFinish_4ee160 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EE160 -- the insmenu_FUN_004EC150 shape with a different callee
 * and a non-zero second argument.  The +0x24 deref is written as a cast rather
 * than a struct member because it appears ONCE: the address-CSE defect that
 * forces a real member (see 004ED0F0) only bites on a second use. */
/*rgp*/
/*rgp*/
extern u8 D_00484304;
s32 insmenu_InsectVsBootFinish_4ee160(void)
{
    RecordSetMode_431310(*(void **)((u8 *)GetGameData_1fede0() + 0x24), 2);
    D_00484304 = 1;
    return 1;
}
