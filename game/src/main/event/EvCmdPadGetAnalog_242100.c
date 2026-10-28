/* rgp:protos */
#define RGP_SELF_EvCmdPadGetAnalog_242100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern u8 D_004B2570[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdPadGetAnalog_242100(E8 *q, s32 n)
{
    if (n > 0) {
        ScriptSetRefFloat_249010(q++, PadGetAnalogLXNorm_183af0(D_004B2570));
    }
    if (n > 1) {
        ScriptSetRefFloat_249010(q++, PadGetAnalogLYNorm_183a50(D_004B2570));
    }
    if (n > 2) {
        ScriptSetRefFloat_249010(q++, PadGetAnalogRXNorm_183c30(D_004B2570));
    }
    if (n > 3) {
        ScriptSetRefFloat_249010(q, PadGetAnalogRYNorm_183b90(D_004B2570));
    }
    return 1;
}
