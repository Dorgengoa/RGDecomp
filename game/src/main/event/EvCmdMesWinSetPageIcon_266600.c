/* rgp:protos */
#define RGP_SELF_EvCmdMesWinSetPageIcon_266600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Rec {
    u8 pad0000[0x1DEE];
    u8 m1DEE;
} Rec;

/*rgp*/
/*rgp*/

s32 EvCmdMesWinSetPageIcon_266600(R8 *q)
{
    Rec *r;

    r = ((Rec *)MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0(q++)));
    if (r == 0) {
        return 0;
    }
    r->m1DEE = (u8)ScriptGetInt_26a2a0(q);
    return 1;
}
