#include "types.h"

/* factory.bin overlay, 0x004EFE90 -- refill the four recipe-preview slots from
 * the current selection's iterator.  612 bytes, 156 instructions, 5
 * conditional branches, 25 calls (br/ins 0.032): the branch-light band.
 *
 * ★ D_0050FDD0 is OVERLAY data at 0x50xxxx, far outside the gp window
 * (_gp 0x00485170 +/- 0x8000), so it is an INCOMPLETE array and takes %hi/%lo.
 * D_00484A70 (_gp - 0x700) is inside the window and stays plain.
 *
 * ★ `o->f6C = 0;` before the func_289710 call is NOT a dead store -- the call
 * may alias it, so mwcc keeps the `sw $0`.
 *
 * ★ SPLIT THE CALL OUT OF THE STORE: `func_28EA40(...)->f12 = o->f70 - 1;`
 * evaluates the RHS BEFORE the call and costs a `dsll32`/`dsra32` pair plus a
 * stolen delay slot; the two-statement form is exact.
 *
 * ★ `n = 0; if (g != 0) n = g->f06;` -- a NULL-or-value select is an `if`,
 * never a ternary; retail's `beqz` carries the zero in its delay slot.
 */

typedef struct Ent {
    s16   f00;
    u8    pad02[0xA];
    void *f0C;
    u8    pad10[0x1C];
    s16   f2C;
    u8    pad2E[0x2];
    void *f30;
} Ent;

typedef struct Group { u8 pad00[0x6]; s16 f06; } Group;
typedef struct Meta  { u8 pad00[0x12]; s16 f12; } Meta;

typedef struct Buf { s32 f00; u8 pad04[0xA8]; } Buf;    /* 0xAC */
typedef struct Iter { u8 pad00[0x8]; } Iter;

typedef struct Scr {
    u8    pad00[0x6C];
    f32   f6C;
    s16   f70;
    u8    pad72[0x2];
    u8    f74[0x14];
    u8    pad88[0x4];
    void *f8C;
    void *f90;
} Scr;

extern void *D_00484A70;                        /* _gp - 0x700 */
extern u8    D_0050FDD0[];

extern s32    factory_FactoryPartsItemToGroup_4efb80(Scr *o, s16 k);
extern void   factory_FactoryPartsSetIcon_4efc40(Scr *o, s16 k, s32 slot);
extern Group *factory_FactoryPartGroupFindById_504080(s32 h, s32 k);
extern void   func_131B60(void *p, s32 v, s32 n);
extern void   func_28A9A0(void *p, void *s, void *a, s32 n);
extern void   func_28AA00(void *p);
extern void  *func_28AA30(void *bank, s32 id);
extern Meta  *func_28EA40(void *w, u32 id);
extern void   func_28F510(void *w, u16 id, void *p, s32 k);
extern void   func_28F970(void *w, u16 id, s32 a, s32 b, s32 c);
extern void   func_290010(void *w, u16 id, s32 a, s32 b);
extern void   func_290F60(void *w, u16 id, s32 x, s32 y);
extern f32    func_289710(Scr *o, s32 a, s32 b, s32 c, s32 d, s32 e);
extern s32    func_367F30(void);
extern void   func_370170(Iter *it, void *p);
extern Ent   *func_370040(Iter *it);

void factory_FactoryPartsListBuild_4efe90(Scr *o)
{
    Iter   it;
    Buf    buf;
    Ent   *e;
    Group *g;
    Meta  *m;
    s32    h;
    s32    k;
    s32    n;
    s32    i;

    func_370170(&it, o->f74);
    func_290010(o->f8C, 0x44, 0, -1);
    o->f70 = 0;
    e = func_370040(&it);
    if (e != 0) {
        o->f70 = o->f70 + 1;
        h = func_367F30();
        k = factory_FactoryPartsItemToGroup_4efb80(o, e->f00);
        g = factory_FactoryPartGroupFindById_504080(h, k);
        n = 0;
        if (g != 0) {
            n = g->f06;
        }
        func_28AA00(&buf);
        func_131B60(&buf, 0, 0xAC);
        buf.f00 = n;
        func_131B60(D_0050FDD0, 0, 0x40);
        func_28A9A0(D_0050FDD0, func_28AA30(D_00484A70, 0x1C), &buf, 1);
        func_290010(o->f8C, 0x44, 1, -1);
        func_28F510(o->f8C, 0x44, e->f0C, 0);
        func_28F510(o->f8C, 0x44, D_0050FDD0, 1);
        func_28F510(o->f8C, 0x44, e->f30, 2);
        factory_FactoryPartsSetIcon_4efc40(o, e->f2C, 0);
    }
    i = 1;
    while (i <= 3 && e != 0) {
        e = func_370040(&it);
        o->f70 = o->f70 + 1;
        factory_FactoryPartsSetIcon_4efc40(o, e->f2C, i);
        i++;
    }
    while (func_370040(&it) != 0) {
        o->f70 = o->f70 + 1;
    }
    o->f6C = 0.0f;
    o->f6C = func_289710(o, 0x43, 0x12F, 4, o->f70, 0);
    func_28F970(o->f8C, 0x43, 0x76, 0x56, 0);
    func_28F970(o->f8C, 0x43, 0x76, 0x5C, 1);
    func_28F970(o->f8C, 0x43, 0x76, 0x64, 2);
    func_290F60(o->f8C, 0x43, 0x6F, 0x20);
    m = func_28EA40(o->f90, 0x88F4);
    m->f12 = o->f70 - 1;
}
