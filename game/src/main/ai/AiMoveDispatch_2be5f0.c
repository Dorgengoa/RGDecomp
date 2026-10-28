/* rgp:protos */
#define RGP_SELF_AiMoveDispatch_2be5f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void AiMoveDispatch_2be5f0(void *arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0)
{
    s32 temp_4;

    VecCopy_1cbe30((s32)((u8 *)arg0 + 0x1A0), arg2);
    temp_4 = *(s32 *)((u8 *)arg0 + 0x28C);
    switch (temp_4) {
    case 0:
        AiMoveFaceTarget_2be560(arg0, arg1, arg2);
        return;
    case 1:
        AiMoveWalkOrRunToTarget_2be310(arg0, arg1, arg2, arg3, fparg0);
        return;
    case 2:
        AiMoveWalkToTarget_2be2e0(arg0, arg1, arg2, arg3, fparg0);
        return;
    case 3:
        AiMoveRunToTarget_2be160(arg0, arg1, arg2, arg3, fparg0);
        return;
    case 4:
        AiMoveModeIdle_2be150();
        return;
    }
}
