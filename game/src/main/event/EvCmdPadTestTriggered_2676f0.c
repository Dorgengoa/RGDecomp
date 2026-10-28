/* rgp:protos */
#define RGP_SELF_EvCmdPadTestTriggered_2676f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004B2570[0x400];
extern u8 D_004B27E0[0x400];
/*rgp*/

s32 EvCmdPadTestTriggered_2676f0(s64 *arg0)
{
    s32 on;
    s32 flags;
    s32 kind;

    kind = ScriptGetInt_26a2a0(arg0++);
    on = 0;
    flags = PadGetTriggeredMask_183d00(D_004B2570);
    if (&IsPad2Enabled_2882c0 != NULL) {
        flags |= PadGetTriggeredMask_183d00(D_004B27E0);
    }
    switch (kind) {
    case 0:
        if (flags & 0x20) {
            on = 1;
        }
        break;
    case 1:
        if (flags & 0x50) {
            on = 1;
        }
        break;
    case 2:
        if (flags & 0x80) {
            on = 1;
        }
        break;
    case 3:
        if (flags & 0x100) {
            on = 1;
        }
        break;
    default:
        return 1;
    }
    ScriptSetRefInt_26a1e0(arg0, on);
    return 1;
}
