/* rgp:protos */
#define RGP_SELF_MovCfgCmdMtnStart_311d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004829A0;
extern s32 D_004829A4;
extern s32 D_004829A8;
extern s32 D_004829AC;

s32 MovCfgCmdMtnStart_311d50(s32 arg0, s32 arg1)
{
    s32 temp_16;

    if (arg1 != 1) {
        return 0;
    }
    if (D_004829A8 == 0 || D_004829AC >= 0x80) {
        return 1;
    }
    temp_16 = D_004829A8 + (D_004829AC * 0xC);
    NamedCompListSet_3125d0(temp_16, MovCfgStrDup_311e50(ScriptArgGetStr_311df0(arg0)), D_004829A0 + (D_004829A4 * 0x14), 0);
    return 1;
}
