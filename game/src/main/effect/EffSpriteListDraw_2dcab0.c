/* rgp:protos */
#define RGP_SELF_EffSpriteListDraw_2dcab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct Ent {
    u8 pad0[4];
    void *tex;      /* 0x04 */
    s32 flags;      /* 0x08 */
    s32 page;       /* 0x0C */
    f32 x;          /* 0x10 */
    f32 y;          /* 0x14 */
    f32 w;          /* 0x18 */
    f32 h;          /* 0x1C */
    u8 pad20[8];
    f32 sx;         /* 0x28 */
    f32 sy;         /* 0x2C */
    u8 pad30[8];
    f32 a;          /* 0x38 */
    f32 b;          /* 0x3C */
    f32 ang;        /* 0x40 */
    u8 pad44[0xA0 - 0x44];
    Vec4 pos;       /* 0xA0 */
    Vec4 col;       /* 0xB0 */
} Ent;

typedef struct Obj {
    u8 pad0[0x40];
    Vec4 org;       /* 0x40 */
    u8 pad50[0x244 - 0x50];
    u8 *list;       /* 0x244 */
    s16 count;      /* 0x248 */
} Obj;

typedef struct F4 { f32 a, b, c, d; } F4;
extern F4 D_0047EF30 __attribute__((section(".sdata")));

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
/*rgp*/
/*rgp*/
/*rgp*/

void EffSpriteListDraw_2dcab0(Obj *o, s32 dl)
{
    s16 r[4];
    Vec4 z __attribute__((aligned(16)));
    Vec4 g __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Vec4 q[4] __attribute__((aligned(16)));
    Vec4 t __attribute__((aligned(16)));
    u8 *p;
    u32 n;
    s32 page;
    u8 *e;
    s32 i;

    p = (u8 *)&z;
    n = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    *(F4 *)&g = D_0047EF30;
    GsPktSetOriginMode_13e2f0(dl, 1);
    GsPktOpenPrim_13f730(dl, 3);
    e = o->list;
    page = 0;
    for (i = 0; i < o->count; i++, e += 0xC0) {
        Ent *en = (Ent *)e;
        f32 fa;
        f32 fb;

        if (en->flags & 1) {
            continue;
        }
        if (*(f32 *)(e + 0xBC) <= 0.0f) {
            continue;
        }
        if (en->page != page) {
            GsPktClose_13f5b0(dl);
            GsPktSetAlphaBlend_13e500(dl, 1);
            GsPktSetBlendMode_13e4f0(dl, en->page);
            GsPktEnableAlphaTest_13e4d0(dl, 0);
            GsPktOpenPrim_13f730(dl, 3);
            page = en->page;
        }
        if (en->tex != 0) {
            GsPktSetTexture_13ec00(dl, en->tex);
        }
        sceVu0CopyVector(&pos, &en->pos);
        VecAdd_13be20(&pos, &pos, &o->org);
        fa = en->a * en->sx;
        fb = en->b * en->sy;
        p = (u8 *)r;
        n = 8;
        if (p != 0) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        r[0] = (s32)en->x;
        r[1] = (s32)en->y;
        r[2] = (s16)(s32)en->w + r[0];
        r[3] = (s16)(s32)en->h + r[1];
        if (BillboardProjectQuad_2dcdc0(q, &pos, fa, fb, en->ang) != 0) {
            VecMax_13dfe0(&t, &z, &en->col);
            VecMin_13df90(&t, &g, &t);
            GsPktSetRGBAQVec_13edd0(dl, &t);
            GsPktSetUV_13ed60(dl, r[0], r[1]);
            GsPktSetXYZVecI_13eeb0(dl, &q[0]);
            GsPktSetUV_13ed60(dl, r[0], r[3]);
            GsPktSetXYZVecI_13eeb0(dl, &q[1]);
            GsPktSetUV_13ed60(dl, r[2], r[1]);
            GsPktSetXYZVecI_13eeb0(dl, &q[2]);
            GsPktSetUV_13ed60(dl, r[2], r[3]);
            GsPktSetXYZVecI_13eeb0(dl, &q[3]);
            GsPktSetUV_13ed60(dl, r[0], r[3]);
            GsPktSetXYZVecI_13eeb0(dl, &q[1]);
            GsPktSetUV_13ed60(dl, r[2], r[1]);
            GsPktSetXYZVecI_13eeb0(dl, &q[2]);
        }
    }
}
