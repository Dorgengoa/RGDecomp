/* rgp:protos */
#define RGP_SELF_EvCmdPadIsHeld_2440e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8_FUN_002440e0 {
    s32 a;
    s32 b;
} E8_FUN_002440e0;

extern u8 D_004B2570[];
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdPadIsHeld_2440e0(E8_FUN_002440e0 *q)
{
    void *a;
    void *b;

    a = ScriptGetInt_2490f0(q++);
    b = PadIsHeld_183a20(D_004B2570, a);
    ScriptSetRefInt_249030(q, b);
    return 1;
}
