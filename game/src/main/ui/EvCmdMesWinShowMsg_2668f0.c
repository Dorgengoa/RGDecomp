/* rgp:protos */
#define RGP_SELF_EvCmdMesWinShowMsg_2668f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMesWinShowMsg_2668f0(s64 *arg0, s32 arg1)
{
    s32 obj;
    s32 k;
    s32 s;
    s32 r;

    obj = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0(arg0++));
    if (obj == 0) {
        return 0;
    }
    switch (*(s32 *)arg0) {
    case 0:
        k = ScriptGetInt_26a2a0(arg0++);
        if (k == -1) {
            MesWinShowMsg_272950(obj, k);
            return 1;
        }
        if (MesWinGetTextFile_274e40(obj) != 0 && MesWinGetTextFileSize_274e30(obj) >= 0) {
            s = MesWinGetTextFile_274e40(obj);
            if (s == 0) {
                return 0;
            }
            r = MesWinGetTextFileSize_274e30(obj);
            if (r <= 0) {
                return 0;
            }
            r = TextFindAtLabelLine_2772f0(s, r, k);
            if (r == 0) {
                return 0;
            }
            MesWinSetLabelText_274e20(obj, r);
            MesWinSetText_2727b0(obj, MesWinGetLabelText_274e10(obj), 0, 0);
        } else {
            MesWinShowMsg_272950(obj, k);
        }
        break;
    case 2:
        MesWinSetTextWithEnd_2726c0(obj, ScriptGetCodeAddr_26a200(arg0++), 0);
        break;
    }
    if (arg1 >= 3) {
        ScriptSetRefInt_26a1e0(arg0, MesWinGetCharCount_274c70(obj));
    }
    return 1;
}
