#include "types.h"
#pragma opt_propagation off
/* normal 0x004FDF70 -- the 0x55FC page's re-entry.  Sibling of
 * normal_FUN_004FD760: same func_28DB40 frame call and the same contracted
 * adda.s/madd.s 0x25 slot, but driven off the caller's record and with the
 * D_00527910 lookup table + func_3C8370 model load bolted on.
 * The `negu $16,$16` is `n = 50; if (f12 == 1) n = -n;`, not a -50 literal.
 * func_1FEDE0 is called with a NOP delay slot -> it takes (void); $4 is a
 * stale copy of r->f10 that m2c mistook for an argument.
 *
 * s32 lane nc32i -- MATCH.  Two edits, NEITHER of which pays alone:
 *   1. the o == NULL arm is a NESTED `else { flag = 1; }`, not a shared
 *      `goto fail`.  mwcc threads only the FIRST predecessor of a shared
 *      block, so the 2nd goto read `beq` + `nop` where retail has
 *      `beql $16,$0` + `addiu $17,$0,1` in the likely slot.
 *   2. `#pragma opt_propagation off` -- without it mwcc constant-folds
 *      `n = 50; if (f12 == 1) n = -n;` into `addiu $16,$0,-0x32`;
 *      retail keeps `addiu $16,$0,0x32` in the bne delay slot and negates
 *      with `negu $16,$16`.  Ten arithmetic respellings of the negation
 *      all fold onto the same object; the pragma is the only lever. */

typedef struct Rec {
    u8  pad00[4];
    s16 f04;
    s16 f06;
    u8  pad08[8];
    s16 f10;
    s16 f12;
    u8  pad14[2];
    s16 f16;
} Rec;                                  /* >= 0x18 */

typedef struct Ent  { s32 f00; u8 pad04[0xC]; } Ent;          /* 0x10 */
typedef struct Model{ u8 pad00[0xC]; s32 f0C; u8 pad10[0x20]; s32 f30; } Model;
typedef struct Obj  { u8 pad00[0x10]; Model *f10; } Obj;
typedef struct Node { u8 pad00[4]; s32 f04; u8 pad08[0xC]; s32 f14; } Node;
typedef struct Widget { u8 pad00[0x28]; Node *f28; } Widget;
typedef struct Ctx  { u8 pad00[0x18]; s32 f18; } Ctx;

extern void *D_0048449C;          /* gp - 0xCD4  */
extern void *D_00484498;          /* gp - 0xCD8  */
extern f32   D_004844B0;          /* gp - 0xCC0  */
extern f32   D_0047D3F0;          /* gp - 0x7D80 */
extern f32   D_0047D240;          /* gp - 0x7F30 */
extern s32   D_00480500;          /* gp - 0x4C70 */
extern s32   D_00480504;          /* gp - 0x4C6C */
extern s32   D_00480508;          /* gp - 0x4C68 */
extern const u8 D_005278E0[];
extern Ent   D_00527910[];

extern void    func_28DB40(const void *p, s32 a, s32 b, s32 c, s32 d, s32 e,
                           s32 f, s32 g);
extern void    func_2910A0(void *p, s32 id, s32 *outX, s32 *outY);
extern void    func_290F50(void *p, s32 id, s32 c, s32 d, s32 e, f32 x);
extern void    func_28EDE0(void *p, s32 id, s32 a);
extern Ctx    *func_1FEDE0(void);
extern Obj    *func_3C8370(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern Widget *func_290460(void *p, s32 id);
extern void    func_291110(void *p, s32 id, s32 c, s32 d);

s32 normal_BtlChgMenuItemGridCursorMoveCb_4fdf70(Rec *r)
{
    s32 x26;
    s32 y26;
    s32 x27;
    s32 y27;
    s32 x23;
    s32 y23;
    u32 n;
    s32 flag;
    s16 idx;
    Ent *e;
    Ctx *c;
    Obj *o;
    Widget *w;
    Node *nd;

    func_28DB40(D_005278E0, 0x28, r->f10 * r->f04 + 0x19,
                r->f12 * r->f06 + 0x17, 0x2A, 0x30, 0x2B, 0xD1);
    if (r->f12 == D_00480504 && r->f16 != D_00480508) {
        n = 50;
        if (r->f12 == 1) {
            n = -n;
        }
        func_2910A0(D_0048449C, 0x26, &x26, &y26);
        func_2910A0(D_0048449C, 0x27, &x27, &y27);
        func_2910A0(D_0048449C, 0x23, &x23, &y23);
        func_290F50(D_0048449C, 0x26, x26, y26 + n, 0, D_0047D3F0);
        func_290F50(D_0048449C, 0x27, x27, y27 + n, 0, D_0047D3F0);
        func_290F50(D_0048449C, 0x23, x23, y23 + n, 0, D_0047D3F0);
        func_290F50(D_0048449C, 0x25, 0x183,
                    (s32)(30.0f + (f32)r->f16 * D_004844B0), 0, D_0047D240);
        func_28EDE0(D_00484498, 0x55FC, 0);
    }
    flag = 0;
    idx = r->f10 + r->f12 * 8 + r->f16 * 8;
    if (idx < 0x21) {
        e = &D_00527910[idx];
        if (e->f00 == -1) {
            goto fail;
        }
        c = func_1FEDE0();
        if (c == NULL) {
            return 0;
        }
        o = func_3C8370(c->f18, e->f00, 0, -1, 0, 0);
        if (o != NULL) {
            w = func_290460(D_0048449C, 0x42);
            if (w == NULL) {
                return 0;
            }
            nd = w->f28;
            if (nd == NULL) {
                return 0;
            }
            nd->f04 = o->f10->f0C;
            nd->f14 = o->f10->f30;
            func_291110(D_0048449C, 0x41, 1, 1);
        } else {
            flag = 1;
        }
        goto merge;
    }
fail:
    flag = 1;
merge:
    if (flag != 0) {
        func_291110(D_0048449C, 0x41, 0, 1);
    }
    D_00480500 = r->f10;
    D_00480504 = r->f12;
    D_00480508 = r->f16;
    return 1;
}
