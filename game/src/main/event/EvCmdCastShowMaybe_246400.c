/* rgp:protos */
#define RGP_SELF_EvCmdCastShowMaybe_246400 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"
#include "event_vm.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCastShowMaybe_246400(s32 arg0) { __typeof__(arg0) rgp_entry_arg0 = arg0;
    s32 temp_16;
    s32 temp_16_2;

    arg0 += 8;
    temp_16 = (s32)((u8 *)gEventContext->player + 0x60);
    temp_16_2 = EventCastGetObjId_24c160(temp_16, EventCastFindKeyByName_24bb50(temp_16, ScriptGetCodeAddr_249050((void *)rgp_entry_arg0)), 0);
    if (!(ScriptGetInt_2490f0(arg0) == 0)) {
        ObjRecClearFlags_1c3dc0(gEventContext->arg, 1, temp_16_2, 0x2000);
    } else {
        ObjRecSetFlags_1c3e00(gEventContext->arg, 1, temp_16_2, 0x2000);
    }
    return 1;
}
