/* rgp:protos */
#define RGP_SELF_EvCmdCastSetClothActive_247440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *gEventContext;

s32 EvCmdCastSetClothActive_247440(s64 *arg0, s32 arg1)
{
    s32 temp_18;
    s32 temp_17;
    s32 temp_16;

    temp_16 = *(s32 *)((u8 *)gEventContext + 4) + 0x60;
    temp_18 = EventCastFindKeyByName_24bb50(temp_16, ScriptGetCodeAddr_249050(arg0++));
    temp_17 = ScriptGetInt_2490f0(arg0++);
    switch (arg1) {
    case 2:
        EventCastObjSetClothActive_24a560(temp_16, temp_18, temp_17, -1);
        break;
    case 3:
        EventCastObjSetClothActive_24a560(temp_16, temp_18, temp_17, ScriptGetInt_2490f0(arg0));
        break;
    }
    return 1;
}
