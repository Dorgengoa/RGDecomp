/* rgp:protos */
#define RGP_SELF_EvCmdEventPlayerIsIdle_261050 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct S00482040 {
    u8 pad[0x484];
    s32 unk484;
} S00482040;

extern S00482040 *D_00482040;
/*rgp*/
/*rgp*/

s32 EvCmdEventPlayerIsIdle_261050(s32 arg0) {
    s32 result;
    s32 z;
    S00482040 *p;

    if (D_00482040 == NULL) {
        ScriptSetRefInt_26a1e0(arg0, 1);
        return 0;
    }
    z = D_00482040->unk484 == 0;
    if (z) {
        ScriptSetRefInt_26a1e0(arg0, 1);
    } else {
        result = EventPlayerIsIdle_250ba0(D_00482040);
        ScriptSetRefInt_26a1e0(arg0, result);
    }
    return 1;
}
