#include "types.h"

/* factory.bin overlay, 0x004F51A0 -- draw the animated cursor quad over one
 * blueprint cell.  752 bytes, 188 instructions, 6 conditional branches, 28
 * calls (br/ins 0.032): the branch-light band.
 *
 * The same skeleton as factory_FactoryMarkerDrawItemIcon_4f5490 (0.839 by mnemonic sequence) with
 * a different cell test, a tint colour and a four-phase cursor advance.
 *
 * Relocation notes: D_0050CBD8 and D_0050B7A0 are OVERLAY data at 0x50xxxx,
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
extern u8    D_0050CBD8[];
extern Tile  D_0050B7A0[];

extern void *func_15DE80(void);
extern void *func_15DE40(void);
extern Ref  *func_159FB0(void *ctx, void *name, s32 k);
extern void  func_1418C0(void *ctx, s16 k, f32 v);
extern s32   func_15D340(Pos *out, Vec *v);
extern Slot *func_290460(void *w, u16 id);
extern void *func_141B00(void *h);
extern void  func_141A20(void *h);
extern s32   func_2F6660(void);
extern f32   func_293350(void);
extern void  func_13E500(void *g, s32 a);
extern void  func_13E4F0(void *g, s32 a);
extern void  func_13E4D0(void *g, s32 a);
extern void  func_13E4C0(void *g, s32 a, s32 b);
extern void  func_13E430(void *g, s32 a);
extern void  func_13E3D0(void *g, s32 a);
extern void  func_13E400(void *g, s32 a);
extern void  func_13E460(void *g, s32 a);
extern void  func_13E2F0(void *g, s32 a);
extern void  func_13F730(void *g, s32 a);
extern void  func_13EC00(void *g, void *p);
extern void  func_13EDD0(void *g, Col *c);
extern void  func_13ED60(void *g, s32 a, s32 b);
extern void  func_13EF10(void *g, s32 a, s32 b, s32 c);
extern void  func_13F5B0(void *g);

void factory_FactoryMarkerDrawKindAnim_4f51a0(Panel *o, s32 idx)
{
    Pos   p;
    Vec   v;
    Col   c;
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

    h = func_15DE80();
    r = func_159FB0(func_15DE40(), D_0050CBD8, -1);
    if (r != 0) {
        func_1418C0(func_15DE80(), r->f00, 1.0f);
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
    if (func_15D340(&p, &v) == 0) {
        return;
    }
    p.x = p.x - 0x260;
    p.y = p.y - 0x640;
    s = func_290460(D_004807F0, idx + 0xAA);
    c.r = 128.0f;
    c.g = 128.0f;
    c.b = 128.0f;
    c.a = 128.0f * s->f3C;
    g = func_141B00(h);
    func_13E500(g, 1);
    func_13E4F0(g, 1);
    func_13E4D0(g, 1);
    func_13E4C0(g, 5, 0);
    func_13E430(g, 1);
    func_13E3D0(g, 1);
    func_13E400(g, 1);
    func_13E460(g, 0);
    func_13E2F0(g, 1);
    func_13F730(g, 6);
    func_13EC00(g, r);
    func_13EDD0(g, &c);
    t = &D_0050B7A0[idx];
    if (func_2F6660() == 0) {
        e->f10 = e->f10 + func_293350();
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
    func_13ED60(g, t->f08, t->f0A);
    func_13EF10(g, x0, y0, 0);
    func_13ED60(g, t->f08 + t->f0C, t->f0A + t->f0E);
    func_13EF10(g, x1, y1, 0);
    func_13F5B0(g);
    func_141A20(h);
}
