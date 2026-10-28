/* rgp:protos */
#define RGP_SELF_ViewSetScreenMatrix_1562b0 1
#include "port/game_protos.h"
#line 1
/* s88m: MATCH (lane 1562) -- right/left read before the m[0] store; recip order b,d,a,e */
#include "types.h"

typedef struct {
    f32 m00;
    f32 left;
    f32 right;
    f32 nearZ;
    f32 farZ;
    f32 sx;
    f32 sy;
    f32 cx;
    f32 cy;
    f32 ox;
    f32 oy;
    f32 m2C;
    f32 m30;
    f32 zmin;
    f32 zmax;
} Params;

typedef struct {
    u8 pad0[0x14];
    Params prm;
    u8 pad50[0xE0];
    f32 m[16];
    u8 pad170[0xD0];
    f32 m240;
    f32 m244;
    f32 m248;
    f32 m24C;
    u8 pad250[0x280];
    f32 m4D0;
    f32 m4D4;
    f32 m4D8;
    f32 m4DC;
    f32 m4E0;
    f32 m4E4;
    f32 m4E8;
} Cam;

/*rgp*/

void ViewSetScreenMatrix_1562b0(Cam *c, Params *prm)
{
    Params *p;
    f32 a, b, d, e, f, m5, m10, m14, l, r;

    p = &c->prm;
    p->m00 = prm->m00;
    p->left = prm->left;
    p->right = prm->right;
    p->nearZ = prm->nearZ;
    p->farZ = prm->farZ;
    p->sx = prm->sx;
    p->sy = prm->sy;
    p->cx = prm->cx;
    p->cy = prm->cy;
    p->ox = prm->ox;
    p->oy = prm->oy;
    p->m2C = prm->m2C;
    p->m30 = prm->m30;
    p->zmin = prm->zmin;
    p->zmax = prm->zmax;
    MtxIdentity_13d2e0(c->m);
    b = 1.0f / p->zmin;
    d = 1.0f / p->zmax;
    a = 1.0f / p->nearZ;
    e = 1.0f / p->farZ;
    r = p->right;
    l = p->left;
    c->m[0] = p->sx / 2.0f;
    f = 2.0f * (e - a);
    m14 = (l * (2.0f * e - d - b) - r * (2.0f * a - d - b)) / f;
    m10 = ((d - b) * (r - l)) / f;
    m5 = -p->sy / 2.0f;
    c->m[5] = m5;
    c->m[10] = m10;
    c->m[14] = m14;
    c->m[12] = p->ox;
    c->m[13] = p->oy;
    c->m240 = p->sx / (p->cx - 8.0f);
    c->m244 = p->sy / (p->cy - 8.0f);
    c->m248 = 1.0f / c->m240;
    c->m24C = 1.0f / c->m244;
    c->m4D0 = 1.0f / c->m[0];
    c->m4D4 = 1.0f / c->m[5];
    c->m4D8 = 1.0f / c->m[10];
    c->m4E0 = -c->m[12];
    c->m4E4 = -c->m[13];
    c->m4E8 = -c->m[14];
}
