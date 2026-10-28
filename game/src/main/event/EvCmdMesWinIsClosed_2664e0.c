/* rgp:protos */
#define RGP_SELF_EvCmdMesWinIsClosed_2664e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMesWinIsClosed_2664e0(s64 *arg0) {
    s32 temp_2;

    temp_2 = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0((s32)arg0++));
    if (temp_2 == 0) {
        return 0;
    }
    ScriptSetRefInt_26a1e0((s32)arg0, MesWinGetState_276a80(temp_2) == 0);
    return 1;
}
