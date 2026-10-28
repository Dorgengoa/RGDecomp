/* rgp:protos */
#define RGP_SELF_EvCmdMesWinSetTextSpeed_242380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8_FUN_00242380 {
    s32 a;
    s32 b;
} E8_FUN_00242380;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMesWinSetTextSpeed_242380(E8_FUN_00242380 *q)
{
    void *a;
    void *r;
    f32 v;

    a = ScriptGetInt_2490f0(q++);
    r = MesMgrGetSlotWin_24fcc0(a);
    if (r == 0) return 0;
    v = TaggedGetFloat_2490d0(q);
    if (v < 0.0f) {
        if (((signed char)MesWinGetFlush_2775e0(r)) == 0) {
            MesWinScrollToPage_270650(r);
        }
        MesWinSetFlush_2775f0(r, 1);
    } else {
        MesWinSetTextSpeed_277580(r, v);
    }
    return 1;
}
