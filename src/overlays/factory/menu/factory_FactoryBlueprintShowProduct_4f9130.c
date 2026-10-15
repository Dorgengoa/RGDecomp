#include "types.h"

/* factory.bin overlay, 0x004F9130 -- fill the item-detail card and pick its
 * gauge style.  588 bytes, 148 instructions, 4 conditional branches, 22 calls
 * (br/ins 0.027): the branch-light band.
 *
 * ★ D_0050FF70 is OVERLAY data at 0x50xxxx, far outside the gp window
 * (_gp 0x00485170 +/- 0x8000), so it is an INCOMPLETE array and takes %hi/%lo.
 * D_00484A70 (_gp - 0x700) is inside the window and stays plain.
 *
 * ★ The dispatch re-tests 0xC and 0xF after the `k == 0xC || k == 0xF` guard
 * because the source really does nest a second `if`/`else if` inside it -- the
 * duplicated `addiu $2, $0, 0xC` in the first `beql`'s delay slot is the
 * likely-branch duplication of the merge's first instruction, not a switch.
 */

typedef struct Rec {
    s16   f00;
    u8    pad02[0x2A];
    s16   f2C;
    u8    pad2E[0x2];
    void *f30;
} Rec;

typedef struct Ent {
    u8    pad00[0x4];
    Rec  *f04;
    u8    pad08[0x8];
    void *f10;
} Ent;

typedef struct Obj { u8 pad00[0x80]; void *f80; } Obj;

typedef struct Buf { u8 pad00[0xC]; s32 f0C; u8 pad10[0x9C]; } Buf;   /* 0xAC */

extern void *D_00484A70;                        /* _gp - 0x700 */
extern u8    D_0050FF70[];

extern void  func_131B60(void *p, s32 v, s32 n);
extern void  func_288E50(void *p, s32 k, s32 a, s32 b);
extern void  func_28A9A0(void *p, void *s, void *a, s32 n);
extern void  func_28AA00(void *p);
extern void *func_28AA30(void *bank, s32 id);
extern s32   func_28F400(void *w, u16 id, s32 k);
extern void  func_28F510(void *w, u16 id, void *p, s32 k);
extern void  func_28F590(void *w, u16 id, s32 a, s32 k);
extern void  func_28F9D0(void *w, u16 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void *func_28FE10(void *w, u16 id, s32 k);
extern void  func_28FC30(void *w, u16 id, s32 a, s32 b, s32 c);
extern void  func_290010(void *w, u16 id, s32 a, s32 b);
extern void  func_290BD0(void *w, u16 id, s32 a, s32 b, s32 c, s32 d);

void factory_FactoryBlueprintShowProduct_4f9130(Obj *o, Ent *e)
{
    Buf buf;
    s32 t;
    s32 k;

    func_28AA00(&buf);
    func_131B60(&buf, 0, 0xAC);
    buf.f0C = e->f04->f00;
    func_131B60(D_0050FF70, 0, 0x80);
    func_28A9A0(D_0050FF70, func_28AA30(D_00484A70, 0x22), &buf, 1);
    func_28F510(o->f80, 0x3A, D_0050FF70, 1);
    func_28F510(o->f80, 0x3A, e->f04->f30, 2);
    t = func_28F400(o->f80, 0x3A, 3);
    func_28F590(o->f80, 0x3A, t + 0xA, 4);
    func_28F510(o->f80, 0x3A, e->f10, 4);
    func_290010(o->f80, 0x3E, 0, -1);
    func_290010(o->f80, 0x3F, 0, -1);
    func_290BD0(o->f80, 0x3E, 8, 0, 0, 0);
    func_290BD0(o->f80, 0x3F, 8, 0, 0, 0);
    k = e->f04->f2C;
    if (k == 0xC || k == 0xF) {
        if (k == 0xC) {
            func_28FC30(o->f80, 0x3F, 0x28, 0x2D, 0);
            func_28F9D0(o->f80, 0x3F, 0x140, 0x20, 0x20, 0x20, 0);
        } else if (k == 0xF) {
            func_28FC30(o->f80, 0x3F, 0x28, 0x2D, 0);
            func_28F9D0(o->f80, 0x3F, 0x140, 0, 0x20, 0x20, 0);
        }
        func_290010(o->f80, 0x3F, 1, -1);
    } else {
        func_288E50(func_28FE10(o->f80, 0x3E, 0), k, 0x28, 0x2D);
        func_290010(o->f80, 0x3E, 1, -1);
    }
}
