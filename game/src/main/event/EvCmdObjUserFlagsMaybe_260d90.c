/* rgp:protos */
#define RGP_SELF_EvCmdObjUserFlagsMaybe_260d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 D_004BDA28[];

s32 EvCmdObjUserFlagsMaybe_260d90(s64 * arg0)
{
    s32 mode;
    s32 idx;
    s32 t;
    s32 *p;

    mode = ScriptGetInt_26a2a0((s32)arg0++);
    idx = ScriptGetInt_26a2a0((s32)arg0++);
    if (idx < 0 || idx >= 0xE0) {
        return 0;
    }
    switch (mode) {
    case 0:
        D_004BDA28[idx] |= ScriptGetInt_26a2a0((s32)arg0);
        break;
    case 1:
        ScriptSetRefInt_26a1e0((s32)arg0, D_004BDA28[idx]);
        break;
    case 2:
        t = ScriptGetInt_26a2a0((s32)arg0);
        D_004BDA28[idx] &= ~t;
        break;
    }
    return 1;
}
