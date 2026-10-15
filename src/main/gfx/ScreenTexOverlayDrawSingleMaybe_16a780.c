#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { s32 a, b, c, d; } I4;

extern void GsPktSetTexture_13ec00(s32, s32);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktCommit_13f190(s32);
extern void GsPktFinalizeTags_13f260(s32);
extern void GsPktSetPrimType_13f470(s32, s32);
extern void GsPktOpen_13f4a0(s32);
extern void DrawEnvGetCenterY_145120(s32);
extern void DrawEnvGetCenterX_145130(s32);
extern void DrawEnvGetHeight_1451d0(s32);
extern void DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);
extern void ScreenTexOverlayWriteSpriteMaybe_16a890(s32, V4 *, u8 *);

void ScreenTexOverlayDrawSingleMaybe_16a780(s32 arg0, V4 *arg1, s32 arg2, I4 *arg3) {
    V4 v;
    s32 t;

    v = *arg1;
    t = GetDrawCtx_15de80();
    DrawEnvGetCenterX_145130(t);
    DrawEnvGetCenterY_145120(t);
    DrawEnvGetWidth_1451e0(t);
    DrawEnvGetHeight_1451d0(t);
    DrawEnvGetHeight_1451d0(t);
    GsPktOpen_13f4a0(arg0);
    GsPktSetPrimType_13f470(arg0, 6);
    GsPktSetTexture_13ec00(arg0, arg2);
    GsPktSetRGBAQ_13ee40(arg0, arg3->a, arg3->b, arg3->c, arg3->d);
    GsPktFinalizeTags_13f260(arg0);
    {
        u8 buf[8] = {0};
        ScreenTexOverlayWriteSpriteMaybe_16a890(arg0, &v, buf);
    }
    GsPktCommit_13f190(arg0);
}
