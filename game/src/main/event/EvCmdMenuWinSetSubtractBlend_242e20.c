/* rgp:protos */
#define RGP_SELF_EvCmdMenuWinSetSubtractBlend_242e20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

extern f32 D_0047E890;
extern f32 D_0047E894;
extern f32 D_0047E898;
extern f32 D_0047E89C;
extern f32 D_0047E8A0;
extern f32 D_0047E8A4;
extern f32 D_0047E8A8;
extern f32 D_0047E8AC;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdMenuWinSetSubtractBlend_242e20(s64 *arg0) {
    Vec a __attribute__((aligned(16)));
    Vec *qa = &a;
    Vec b __attribute__((aligned(16)));
    Vec *qb = &b;
    void *obj;
    s32 on;

    obj = MenuWinGet_2653e0(ScriptGetInt_2490f0((s32)arg0++));
    if (obj == NULL) {
        return 0;
    }
    on = ScriptGetInt_2490f0((s32)arg0);
    if (on != 0) {
        qa->x = D_0047E890;
        qa->y = D_0047E894;
        qa->z = D_0047E898;
        qa->w = D_0047E89C;
        qb->x = D_0047E8A0;
        qb->y = D_0047E8A4;
        qb->z = D_0047E8A8;
        qb->w = D_0047E8AC;
        MenuWinSetDrawMode_26c3e0(obj, 0);
        MenuWinSetBlendMode_26c270(obj, 1);
        MenuWinSetPos_26c3b0(obj, &a);
        MenuWinSetColor_26c380(obj, &b);
        MenuWinSetSize_26c320(obj, 0x200, 0x1C0);
    }
    MenuWinSetSubtractBlend_26c2e0(obj, on);
    return 1;
}
