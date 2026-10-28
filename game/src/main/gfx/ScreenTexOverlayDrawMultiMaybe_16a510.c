/* rgp:protos */
#define RGP_SELF_ScreenTexOverlayDrawMultiMaybe_16a510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } Vec4;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void ScreenTexOverlayDrawMultiMaybe_16a510(s32 arg0, Vec4 *arg1, s32 arg2, s32 *arg3, s32 mode, s32 *ofs)
{
    Vec4 v __attribute__((aligned(16)));
    s32 d[2];
    s32 h;

    v = *arg1;
    if (mode <= 0 || mode > 3) {
        return;
    }
    h = GetDrawCtx_15de80();
    DrawEnvGetCenterX_145130(h);
    DrawEnvGetCenterY_145120(h);
    DrawEnvGetWidth_1451e0(h);
    DrawEnvGetHeight_1451d0(h);
    DrawEnvGetHeight_1451d0(h);
    GsPktOpen_13f4a0(arg0);
    GsPktSetPrimType_13f470(arg0, 6);
    GsPktSetTexture_13ec00(arg0, arg2);
    GsPktSetRGBAQ_13ee40(arg0, arg3[0], arg3[1], arg3[2], arg3[3]);
    GsPktFinalizeTags_13f260(arg0);
    if (mode == 1) {
        d[0] = 0;
        d[1] = 0;
        ScreenTexOverlayWriteSpriteMaybe_16a890(arg0, &v, d);
    }
    if (mode == 2) {
        d[0] = ofs[0] * 3 / 4;
        d[1] = ofs[1] * 3 / 4;
        ScreenTexOverlayWriteSpriteMaybe_16a890(arg0, &v, d);
        d[0] = -ofs[0] * 3 / 4;
        d[1] = -ofs[1] * 3 / 4;
        ScreenTexOverlayWriteSpriteMaybe_16a890(arg0, &v, d);
    }
    if (mode == 3) {
        d[0] = ofs[0];
        d[1] = 0;
        ScreenTexOverlayWriteSpriteMaybe_16a890(arg0, &v, d);
        d[0] = -ofs[0];
        d[1] = 0;
        ScreenTexOverlayWriteSpriteMaybe_16a890(arg0, &v, d);
        d[0] = 0;
        d[1] = ofs[1];
        ScreenTexOverlayWriteSpriteMaybe_16a890(arg0, &v, d);
        d[1] = 0;
        d[1] = -ofs[1];
        ScreenTexOverlayWriteSpriteMaybe_16a890(arg0, &v, d);
    }
    GsPktCommit_13f190(arg0);
}
