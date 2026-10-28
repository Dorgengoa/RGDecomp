/* rgp:protos */
#define RGP_SELF_factory_FactoryMarkerDrawKindAnim_4f51a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F51A0 -- draw the animated cursor quad over one
 * blueprint cell.  752 bytes, 188 instructions, 6 conditional branches, 28
 * calls (br/ins 0.032): the branch-light band.
 *
 * The same skeleton as factory_FactoryMarkerDrawItemIcon_4f5490 (0.839 by mnemonic sequence) with
 * a different cell test, a tint colour and a four-phase cursor advance.
 *
 * Relocation notes: factory_D_0050CBD8 and factory_D_0050B7A0 are OVERLAY data at 0x50xxxx,
 * far outside the gp window (_gp 0x00485170 +/- 0x8000), so both are declared
 * as INCOMPLETE arrays and take %hi/%lo.  D_004807F0 (_gp - 0x4980) is inside
 * the window and stays plain.
 *
 * ★ `slti $1, $3, 0x4` lands in `$at`, so the source token is `> 3` and not
 * `>= 4` -- a compare's destination follows the branch's RELATIONAL OPERATOR
 * TOKEN ([[at-compare-class]]).
 *
 * ★ The three 128.0f tint components are stored with `lui` + `sw` and the
 * fourth with `swc1`: the first three are constants, the fourth a product.
 *
 * ★ `t->f08` is WRITTEN and then read back by the first func_13ED60 argument;
 * mwcc re-extends the stored halfword rather than reloading it.
 */

typedef struct Cell {
    f32 f00;
    f32 f04;
    f32 f08;
    s16 f0C;
    u8  f0E;
    u8  pad0F[0x1];
    f32 f10;
} Cell;                                         /* 0x14 */

typedef struct Panel {
    u8    pad00[0x78];
    Cell *f78;
} Panel;

typedef struct Tile {
    s16 f00;
    s16 f02;
    u8  pad04[0x4];
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    u8  pad10[0x30];
} Tile;                                         /* 0x40 */

typedef struct Vec { f32 x; f32 y; f32 z; f32 w; } Vec;
typedef struct Pos { s32 x; s32 y; s32 z; s32 w; } Pos;
typedef struct Col { f32 r; f32 g; f32 b; f32 a; } Col;

typedef struct Ref  { s16 f00; } Ref;
typedef struct Slot { u8 pad00[0x3C]; f32 f3C; } Slot;

extern void *D_004807F0;                        /* _gp - 0x4980 */
extern u8    factory_D_0050CBD8[];
extern Tile  factory_D_0050B7A0[];

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
/*rgp*/
/*rgp*/

void factory_FactoryMarkerDrawKindAnim_4f51a0(Panel *o, s32 idx)
{
    Pos   p __attribute__((aligned(16)));
    Vec   v __attribute__((aligned(16)));
    Col   c __attribute__((aligned(16)));
    void *h;
    void *g;
    Ref  *r;
    Slot *s;
    Cell *e;
    Tile *t;
    s32   k;
    s32   x0;
    s32   x1;
    s32   y0;
    s32   y1;

    h = GetDrawCtx_15de80();
    r = ((Ref *)NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), factory_D_0050CBD8, -1));
    if (r != 0) {
        DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), r->f00, 1.0f);
    }
    e = &o->f78[idx];
    if (e->f0E == 0) {
        return;
    }
    if (e->f0C == 0) {
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
    s = ((Slot *)UiFindWidget_290460(D_004807F0, idx + 0xAA));
    c.r = 128.0f;
    c.g = 128.0f;
    c.b = 128.0f;
    c.a = 128.0f * s->f3C;
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
    GsPktSetRGBAQVec_13edd0(g, &c);
    t = &factory_D_0050B7A0[idx];
    if (GetPauseStep_2f6660() == 0) {
        e->f10 = e->f10 + GetSceneTimeStep_293350();
    }
    k = (s32)e->f10 >> 4;
    if (k > 3) {
        e->f10 = 0.0f;
        k = 0;
    }
    t->f08 = k * 48;
    x0 = p.x + t->f00 * 16;
    x1 = x0 + t->f0C * 16;
    y0 = p.y + t->f02 * 16;
    y1 = y0 + t->f0E * 16;
    GsPktSetUV_13ed60(g, t->f08, t->f0A);
    GsPktSetXYZ_13ef10(g, x0, y0, 0);
    GsPktSetUV_13ed60(g, t->f08 + t->f0C, t->f0A + t->f0E);
    GsPktSetXYZ_13ef10(g, x1, y1, 0);
    GsPktClose_13f5b0(g);
    DrawListEndPrim_141a20(h);
}
