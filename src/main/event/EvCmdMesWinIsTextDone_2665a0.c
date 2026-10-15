#include "types.h"

struct QFUN_002665a0 { s32 a; s32 b; };

extern void *ScriptGetInt_26a2a0(struct QFUN_002665a0 *q);
extern void *MesMgrGetSlotWin_266af0(void *a);
extern s32 MesWinGetState_276a80(void *b);
extern void ScriptSetRefInt_26a1e0(struct QFUN_002665a0 *q, s32 f);

s32 EvCmdMesWinIsTextDone_2665a0(struct QFUN_002665a0 *q)
{
    void *a;
    void *b;

    a = ScriptGetInt_26a2a0(q++);
    b = MesMgrGetSlotWin_266af0(a);
    if (b == 0) {
        return 0;
    }
    ScriptSetRefInt_26a1e0(q, MesWinGetState_276a80(b) == 3);
    return 1;
}
