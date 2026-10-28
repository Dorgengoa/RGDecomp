/* rgp:protos */
#define RGP_SELF_AiCmdCharaIsNearGround_2c9730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern struct { void *p; s32 pad[3]; } D_004DB92C;
extern struct { f32 v; s32 pad[3]; } D_0045B080;
extern f32 D_0047D280;
/*rgp*/
/*rgp*/

s32 AiCmdCharaIsNearGround_2c9730(void *p, s32 mode)
{
    void *g;
    u8 f;
    f32 r;
    f32 kb;

    if (mode == 1) {
        g = D_004DB92C.p;
        f = 0;
        if ((((*(s32 *)((s32)g + 0x3D8) & 4) ? 1 : 0)) != 0) {
            r = CharaGetHeightAboveGround_238380(g);
            kb = *(volatile f32 *)&D_0045B080.v;
            if (r <= D_0047D280 * kb) {
                f = 1;
            }
        }
        ScriptSlotStoreIntRef_2cc900(p, f);
    }
    return 1;
}
