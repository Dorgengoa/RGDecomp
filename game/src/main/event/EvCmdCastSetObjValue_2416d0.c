/* rgp:protos */
#define RGP_SELF_EvCmdCastSetObjValue_2416d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *gEventContext;

s32 EvCmdCastSetObjValue_2416d0(s32 arg0) { __typeof__(arg0) rgp_entry_arg0 = arg0;
    void *ctx;
    s32 temp_17;
    s32 temp_16;
    s32 temp_16_2;

    arg0 += 8;
    ctx = gEventContext;
    temp_17 = *(s32 *)((u8 *)ctx + 0);
    temp_16 = *(s32 *)((u8 *)ctx + 4) + 0x60;
    temp_16_2 = EventCastGetObjId_24c160(temp_16, EventCastFindKeyByName_24bb50(temp_16, ScriptGetCodeAddr_249050((void *)rgp_entry_arg0)), 0);
    ObjRecSetValue_1c3d60(temp_17, 1, temp_16_2, ScriptGetInt_2490f0(arg0));
    return 1;
}
