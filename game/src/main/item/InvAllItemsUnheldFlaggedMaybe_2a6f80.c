/* rgp:protos */
#define RGP_SELF_InvAllItemsUnheldFlaggedMaybe_2a6f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 InvAllItemsUnheldFlaggedMaybe_2a6f80(void)
{
    u8 sp28[8];
    u8 sp10[0x18] __attribute__((aligned(16)));
    s32 t;

    InvViewCtorFromOwner_3cec70(sp10, ((s32)GetGameData_1fede0()), 9, -1, -1, -1);
    IterInit_370170(sp28, sp10, 0, 0);
    goto test;
    do {
        if (ItemIsUnheldFlaggedMaybe_3d4420(t) == 0) {
            return 0;
        }
test:
        t = IterNext_370040(sp28);
    } while (t != 0);
    return 1;
}
