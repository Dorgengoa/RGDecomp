/* rgp:protos */
#define RGP_SELF_EvCmdEventIconShow_25e320 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_25e320;
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00481F78;
extern s32 D_004BD980[];

s32 EvCmdEventIconShow_25e320(E8_25e320 *p0)
{
    s32 a;
    s32 b;
    s32 h;

    a = ScriptGetInt_26a2a0(p0++);
    b = ScriptGetInt_26a2a0(p0);
    h = ((s32)RecStackGetSlot_1c4330(D_00481F78, D_004BD980[a]));
    EventIconShow_278bf0(h, b);
    return 1;
}
