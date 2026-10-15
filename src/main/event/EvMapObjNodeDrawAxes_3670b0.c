#include "types.h"

extern struct { f32 v; f32 pad[3]; } D_0045B080;
extern f32 D_0047F930;
extern f32 D_0047F934;
extern f32 D_0047F938;
extern f32 D_0047F93C;
extern f32 D_0047F940;
extern f32 D_0047F944;
extern f32 D_0047F948;
extern f32 D_0047F94C;
extern f32 D_0047F950;
extern f32 D_0047F954;
extern f32 D_0047F958;
extern f32 D_0047F95C;

extern void FrameCalcWorldMatrix_148ff0(void *q, f32 *v);
extern void VecScale_1cbca0(f32 *d, f32 *s, f32 t);
extern void GsPktSetTextured_13e400(void *dl, s32 v);
extern void GsPktEnableZTest_13e460(void *dl, s32 v);
extern void GsPktOpenPrim_13f730(void *dl, s32 v);
extern void VecAdd_1cbdc0(f32 *d, f32 *s, f32 *t);
extern void GsPktDrawLine3D_1cca80(void *dl, f32 *a, f32 *b, f32 *c);
extern void GsPktClose_13f5b0(void *dl);

void EvMapObjNodeDrawAxes_3670b0(void *p, void *dl)
{
    f32 a[4];
    f32 b[4];
    f32 c[4];
    f32 d[4];
    f32 e[4];
    f32 f[4];
    f32 g[4];
    f32 h[4];
    void *q;
    f32 t;
    f32 k;

    if (dl == 0) {
        return;
    }
    q = *(void **)((u8 *)p + 0x144);
    if (q == 0) {
        return;
    }
    FrameCalcWorldMatrix_148ff0(q, d);
    k = *(volatile f32 *)&D_0045B080.v;
    t = 0.5f * k;
    VecScale_1cbca0(d, d, t);
    VecScale_1cbca0(c, c, t);
    VecScale_1cbca0(b, b, t);
    GsPktSetTextured_13e400(dl, 0);
    GsPktEnableZTest_13e460(dl, 0);
    GsPktOpenPrim_13f730(dl, 1);
    f[0] = D_0047F930;
    f[1] = D_0047F934;
    f[2] = D_0047F938;
    f[3] = D_0047F93C;
    VecAdd_1cbdc0(e, d, a);
    GsPktDrawLine3D_1cca80(dl, a, e, f);
    g[0] = D_0047F940;
    g[1] = D_0047F944;
    g[2] = D_0047F948;
    g[3] = D_0047F94C;
    VecAdd_1cbdc0(e, c, a);
    GsPktDrawLine3D_1cca80(dl, a, e, g);
    h[0] = D_0047F950;
    h[1] = D_0047F954;
    h[2] = D_0047F958;
    h[3] = D_0047F95C;
    VecAdd_1cbdc0(e, b, a);
    GsPktDrawLine3D_1cca80(dl, a, e, h);
    GsPktClose_13f5b0(dl);
}
