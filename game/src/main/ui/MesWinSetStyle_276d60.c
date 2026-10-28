/* rgp:protos */
#define RGP_SELF_MesWinSetStyle_276d60 1
#include "port/game_protos.h"
#line 1
#include "types.h"


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesWinSetStyle_276d60(void *arg0, s32 arg1)
{
    s32 u;
    switch (arg1) {
    case 0:
        MesWinSetFrameType_272b30((void *)arg0, 1);
        TextStyleSetOutlineMode_26f160(arg0, 5);
        MesWinSetFixedPos_272b70(arg0, 0);
        MesWinSetSeEnabled_272b50(arg0, 1);
        return;
    case 1:
        MesWinSetFrameType_272b30((void *)arg0, 0);
        TextStyleSetOutlineMode_26f160(arg0, 5);
        MesWinSetFixedPos_272b70(arg0, 1);
        MesWinSetSeEnabled_272b50(arg0, 0);
        *(s8*)((u8 *)arg0 + 0x1DEE) = 0;
        return;
    }
}
