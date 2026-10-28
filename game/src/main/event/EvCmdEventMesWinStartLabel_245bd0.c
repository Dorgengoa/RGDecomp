/* rgp:protos */
#define RGP_SELF_EvCmdEventMesWinStartLabel_245bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern void *gEventContext;

s32 EvCmdEventMesWinStartLabel_245bd0(s64 *arg0, s32 arg1)
{
    s32 t;
    s32 a;

    t = *(s32 *)((u8 *)gEventContext + 4) + 0x420;
    if (arg1 == 1) {
        MesWinOwnerStartLabel_24eae0(t, ScriptGetInt_2490f0((s32)arg0), 0);
    } else if (arg1 == 2) {
        a = ScriptGetInt_2490f0((s32)arg0++);
        MesWinOwnerStartLabel_24eae0(t, a, ScriptGetInt_2490f0((s32)arg0));
    }
    return 1;
}
