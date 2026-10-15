#include "types.h"

/* factory.bin overlay, 0x004EFD30 -- rebuild the single recipe-detail slot
 * from the panel's item iterator.  348 bytes, 88 instructions, 2 conditional
 * branches, 17 calls: the branch-light LIST band.
 *
 * Near-twin of factory_FUN_004EFE90 (which walks the same iterator four
 * slots deep); this one seeks the iterator to m->f16 + m->f1A and fills one
 * entry, so it is that function's `if (e != 0)` body with the counter and the
 * tail removed.
 *
 * * D_0050FDD0 is OVERLAY data at 0x50xxxx, far outside the gp window
 * (_gp 0x00485170 +/- 0x8000), so it is an INCOMPLETE array and takes %hi/%lo.
 * D_00484A70 (_gp - 0x700) is inside the window and stays plain.
 *
 * * `beql $17, $0, <epilogue>` carrying `ld $31, 0x30($29)` -- retail FALLS
 * THROUGH into the body, so the body is the source's `if (e != 0)` arm.
 *
 * * mwcc allocates stack locals in REVERSE declaration order: `buf` is
 * declared LAST and takes the lower slot 0x40, `it` the higher 0xF8.
 *
 * * `n = 0; if (g != 0) n = g->f06;` -- a NULL-or-value select is an `if`,
 * never a ternary; retail's `beqz` carries the zero in its delay slot.
 *
 * * `buf.f00 = n;` sits BETWEEN the two func_131B60 calls in source order --
 * mwcc sinks the `sw $18, 0x40($29)` into the second call's delay slot.
 */

typedef struct Ent {
    s16   f00;
    u8    pad02[0xA];
    void *f0C;
    u8    pad10[0x20];
    void *f30;
} Ent;

typedef struct Group { u8 pad00[0x6]; s16 f06; } Group;

typedef struct Meta {
    u8  pad00[0x16];
    s16 f16;
    u8  pad18[0x2];
    s16 f1A;
} Meta;

typedef struct Buf { s32 f00; u8 pad04[0xA8]; } Buf;    /* 0xAC */
typedef struct Iter { u8 pad00[0x8]; } Iter;

typedef struct Scr {
    u8    pad00[0x74];
    u8    f74[0x14];
    u8    pad88[0x4];
    void *f8C;
    void *f90;
} Scr;

extern void *D_00484A70;                        /* _gp - 0x700 */
extern u8    D_0050FDD0[];

extern s32    factory_FactoryPartsItemToGroup_4efb80(Scr *o, s16 k);
extern Group *factory_FactoryPartGroupFindById_504080(s32 h, s32 k);
extern void   func_131B60(void *p, s32 v, s32 n);
extern void   func_28A9A0(void *p, void *s, void *a, s32 n);
extern void   func_28AA00(void *p);
extern void  *func_28AA30(void *bank, s32 id);
extern Meta  *func_28EA40(void *w, u32 id);
extern void   func_28F510(void *w, u16 id, void *p, s32 k);
extern void   func_290010(void *w, u16 id, s32 a, s32 b);
extern s32    func_367F30(void);
extern void   func_36FFF0(Iter *it, s32 n);
extern Ent   *func_36FF80(Iter *it);
extern void   func_370170(Iter *it, void *p);

void factory_FactoryPartsRefreshDetail_4efd30(Scr *o)
{
    Iter   it;
    Buf    buf;
    Ent   *e;
    Group *g;
    Meta  *m;
    s32    h;
    s32    k;
    s32    n;

    func_370170(&it, o->f74);
    func_290010(o->f8C, 0x44, 0, -1);
    m = func_28EA40(o->f90, 0x88F4);
    func_36FFF0(&it, m->f16 + m->f1A);
    e = func_36FF80(&it);
    if (e != 0) {
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
    }
}
