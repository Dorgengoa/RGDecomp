/* rgp:protos */
#define RGP_SELF_EvCmdPadIsTriggered_244130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8_FUN_00244130 {
    s32 a;
    s32 b;
} E8_FUN_00244130;

extern u8 D_004B2570[];
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdPadIsTriggered_244130(E8_FUN_00244130 *q)
{
    void *a;
    void *b;

    a = ScriptGetInt_2490f0(q++);
    b = PadIsTriggered_1839f0(D_004B2570, a);
    ScriptSetRefInt_249030(q, b);
    return 1;
}
