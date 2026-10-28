/* rgp:protos */
#define RGP_SELF_factory_FactoryMarkerDrawItemIcon_4f5490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F5490 -- project one blueprint cell into screen
 * space and stroke its two-corner frame.  640 bytes, 160 instructions, 4
 * conditional branches, 26 calls (br/ins 0.025): the branch-light band.
 *
 * Relocation notes: factory_D_0050CBE8 and factory_D_0050B960 are OVERLAY data at 0x50xxxx,
 * far outside the gp window (_gp 0x00485170 +/- 0x8000), so both are declared
 * as INCOMPLETE arrays and take %hi/%lo.  D_004807F0 (_gp - 0x4980) is inside
 * the window and stays plain.
 *
 * ★ Both `beql`s DUPLICATE the merge's first instruction (f_ds.py), so both
 * are plain forward branches -- there is no switch and no branch-likely
 * conversion class here.
 *
 * ★ `andi $5, $2, 0xFFFF` on `idx + 0xA4` is func_290460's u16 parameter, not
 * a mask in the source.
 *
 * ★ The 1.0f in the fourth slot of the projection vector is materialised with
 * `lui` + `sw`, not `mtc1` + `swc1`: it is a constant store into an f32 field.
 */

typedef struct Cell {
    f32 f00;
    f32 f04;
    f32 f08;
    s16 f0C;
    u8  f0E;
    u8  pad0F[0x5];
} Cell;                                         /* 0x14 */

typedef struct Panel {
    u8    pad00[0x78];
    Cell *f78;
} Panel;

typedef struct Tile {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    u8  pad10[0x30];
} Tile;                                         /* 0x40 */

typedef struct Vec { f32 x; f32 y; f32 z; f32 w; } Vec;
typedef struct Pos { s32 x; s32 y; s32 z; s32 w; } Pos;

typedef struct Ref { s16 f00; } Ref;

extern void *D_004807F0;                        /* _gp - 0x4980 */
extern u8    factory_D_0050CBE8[];
extern Tile  factory_D_0050B960[];

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryMarkerDrawItemIcon_4f5490(Panel *o, s32 idx)
{
    Pos   p __attribute__((aligned(16)));
    Vec   v __attribute__((aligned(16)));
    void *h;
    void *g;
    Ref  *r;
    Cell *e;
    Tile *t;
    s32   x0;
    s32   x1;
    s32   y0;
    s32   y1;

    h = GetDrawCtx_15de80();
    r = ((Ref *)NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), factory_D_0050CBE8, -1));
    if (r != 0) {
        DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), r->f00, 1.0f);
    }
    e = &o->f78[idx];
    if (e->f0E == 0) {
        return;
    }
    if (e->f0C != 0) {
        return;
    }
    v.x = e->f00;
    v.y = e->f04;
    v.z = e->f08;
    v.w = 1.0f;
    if (ProjectToScreen_15d340(&p, &v) == 0) {
        return;
    }
    p.x = p.x - 0x260;
    p.y = p.y - 0x640;
    UiFindWidget_290460(D_004807F0, idx + 0xA4);
    g = DrawListBeginPrim_141b00(h);
    GsPktSetAlphaBlend_13e500(g, 1);
    GsPktSetBlendMode_13e4f0(g, 1);
    GsPktEnableAlphaTest_13e4d0(g, 1);
    GsPktSetAlphaTestFunc_13e4c0(g, 5, 0);
    GsPktSetZWriteMask_13e430(g, 1);
    GsPktSetTexFilter_13e3d0(g, 1);
    GsPktSetTextured_13e400(g, 1);
    GsPktEnableZTest_13e460(g, 0);
    GsPktSetOriginMode_13e2f0(g, 1);
    GsPktOpenPrim_13f730(g, 6);
    GsPktSetTexture_13ec00(g, r);
    GsPktSetRGBAQ_13ee40(g, 0x80, 0x80, 0x80, 0x80);
    t = &factory_D_0050B960[idx];
    x0 = p.x + t->f00 * 16;
    x1 = x0 + t->f04 * 16;
    y0 = p.y + t->f02 * 16;
    y1 = y0 + t->f06 * 16;
    GsPktSetUV_13ed60(g, t->f08, t->f0A);
    GsPktSetXYZ_13ef10(g, x0, y0, 0);
    GsPktSetUV_13ed60(g, t->f08 + t->f0C, t->f0A + t->f0E);
    GsPktSetXYZ_13ef10(g, x1, y1, 0);
    GsPktClose_13f5b0(g);
    DrawListEndPrim_141a20(h);
}
