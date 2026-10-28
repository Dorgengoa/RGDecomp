/* rgp:protos */
#define RGP_SELF_EntryScriptCmdSetPair20Related_322cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EntryScriptCmdSetPair20Related_322cf0(s64 *arg0) {
    f32 f;
    f32 g;
    s32 t;
    s32 u;

    t = GetEntryTableGlobal_32c2e0();
    if (t == 0) {
        return 0;
    }
    u = EntryTableGetCurrent_323530(t);
    if (u == 0) {
        return 0;
    }
    f = (f32)VariantGetInt_15f780((s32)arg0++);
    g = (f32)VariantGetInt_15f780((s32)arg0);
    EntrySetPair20Related_323be0(u, (s32)f, (s32)g);
    return 1;
}
