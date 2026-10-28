/* rgp:protos */
#define RGP_SELF_EvCmdMenuWinSetTexName_265170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMenuWinSetTexName_265170(s64 *arg0) {
    s32 t2;
    s32 t17_2;
    s32 t17;
    s32 t16_2;
    s64 *p;

    t17 = ScriptGetInt_26a2a0((s32)arg0++);
    t16_2 = ScriptGetCodeAddr_26a200((s32)arg0++);
    t17_2 = ScriptGetInt_26a2a0((s32)arg0);
    if ((t2 = ((s32)MenuWinGet_2653e0(t17))) == 0) {
        return 0;
    }
    MenuWinSetAlphaBlend_26c260(t2, 1);
    MenuWinSetAlphaTest_26c250(t2, 1);
    MenuWinSetTexName_26c410(t2, t16_2, t17_2);
    return 1;
}
