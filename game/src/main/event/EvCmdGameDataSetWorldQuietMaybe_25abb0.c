/* rgp:protos */
#define RGP_SELF_EvCmdGameDataSetWorldQuietMaybe_25abb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 EvCmdGameDataSetWorldQuietMaybe_25abb0(s32 arg0, s32 arg1) {
    u8 *p;

    if (arg1 != 1) {
        return 0;
    }
    p = (u8 *)GetGameData_1fede0();
    p[0x2C] = (p[0x2C] & ~1) | (ScriptGetInt_26a2a0(arg0) != 0);
    return 1;
}
