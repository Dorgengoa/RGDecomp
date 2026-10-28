/* rgp:protos */
#define RGP_SELF_InsectBattleGetPromptResult_319500 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
/*rgp*/
struct Obj0 { u8 pad000[0x5FC3]; s8 m5FC3; };

s8 InsectBattleGetPromptResult_319500(void)
{
    struct Obj0 *r1;
    s32 r0;

    r0 = GetLoadedOverlayId_1c3200();
    if (r0 != 5) {
        return (s8)1;
    }
    r1 = ((struct Obj0 *)InsectBattleGet_31a8d0());
    if (r1 != 0) {
        return r1->m5FC3;
    }
    return (s8)1;
}
