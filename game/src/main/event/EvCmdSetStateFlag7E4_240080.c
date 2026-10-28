/* rgp:protos */
#define RGP_SELF_EvCmdSetStateFlag7E4_240080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R00240080 {
    u8 pad0[0x10];
    s32 unk10;
} R00240080;

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdSetStateFlag7E4_240080(void *rgp_a0)
{
    s32 flag;

    flag = ScriptGetInt_2490f0((void *)rgp_a0) != 0;
    StateFlagSet_3ccb70(((R00240080 *)GetGameData_1fede0())->unk10, 0x7E4, flag, 1);
    return 1;
}
