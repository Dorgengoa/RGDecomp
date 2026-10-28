/* rgp:protos */
#define RGP_SELF_EvCmdCueMesLabel_245970 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "event_vm.h"


/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCueMesLabel_245970(s64 *arg0)
{ __typeof__(arg0) rgp_entry_arg0 = arg0;
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(s32[3])]; char m1[0x10]; })];
    EventPlayer *player;

    arg0++;
    player = gEventContext->player;
    (*(s32 (*)[3])(rgp_blk1 + 0x0))[0] = 0;
    ScriptGetCodeAddr_249050((void *)rgp_entry_arg0);
    (*(s32 (*)[3])(rgp_blk1 + 0x0))[2] = ScriptGetInt_2490f0((s32)arg0++);
    (*(s32 (*)[3])(rgp_blk1 + 0x0))[1] = ScriptGetInt_2490f0((s32)arg0);
    Vec4VectorPushBack_249120(player, (*(s32 (*)[3])(rgp_blk1 + 0x0)));
    return 1;
}
