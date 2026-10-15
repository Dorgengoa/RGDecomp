#include "types.h"
/* normal 0x0051EFE0 -- clears the eight 0x28-byte party slots at
 * D_00484744 + 0x84, then walks the query iterator and re-fills the window
 * [a, a+8) from it, accumulating every hit's f10 into the 0x763C readout.
 * The prologue is MERGED normal_FUN_0051E480's verbatim: the SAME 0x477600
 * query key, the same `func_3FCF00(&q, c, 1, 1, 0, 0, 1, 0)` and the same
 * `Iter it; Query q;` declaration order (Iter FIRST -- the frame lays the
 * locals out in REVERSE declaration order, q at 0x70 and it at 0x88).
 * func_291250's fourth parameter is s64, so `total` needs retail's
 * `dsll32/dsra32 $7,$20,0` widening pair ([[mwcc-s32-s64-widening-pair]]) and
 * `e->f10` -- a u16 -- reaches it through a bare `lhu` with no widening. */

typedef struct Iter  { u8 pad00[0x8]; } Iter;
typedef struct Query { const u8 *f00; u8 pad04[0x14]; } Query;   /* 0x18 */
typedef struct Ctx   { u8 pad00[0x10]; void *f10; } Ctx;
typedef struct Ent   { u8 pad00[0x10]; u16 f10; } Ent;
typedef struct Slot  { u8 pad00[0x28]; } Slot;
typedef struct Tab   { u8 pad000[0x84]; Slot f084[8]; } Tab;

extern const u8 D_00477600;
extern void *D_00484710;          /* gp - 0xA60 */
extern Tab  *D_00484744;          /* gp - 0xA2C */

extern Ctx  *func_1FEDE0(void);
extern void  func_3FCF00(Query *q, Ctx *c, s32 a, s32 b, s32 d, s32 e, s32 f, s32 g);
extern void  func_370170(Iter *it, Query *q);
extern Ent  *func_370040(Iter *it);
extern void  func_131B60(void *p, s32 v, s32 n);
extern void  func_3FDAF0(Ent *e, void *p);
extern void  func_28F510(void *w, u16 id, void *p, s32 k);
extern void  func_28F100(void *w, u16 id, s32 a, s32 b, s32 k);
extern void  func_28F670(void *w, u16 id, s32 a, s32 b, s32 c, s32 d, s32 k);
extern void  func_291250(void *w, u16 id, s32 slot, s64 v);

s32 normal_TransHunterBountyListFill_51efe0(s32 a)
{
    Iter   it;
    Query  q;
    s32    total;
    s32    n;
    s32    k;
    Ent   *e;
    s32    i;
    Ctx   *c;

    c = func_1FEDE0();
    q.f00 = &D_00477600;
    func_3FCF00(&q, c, 1, 1, 0, 0, 1, 0);
    func_370170(&it, &q);
    i = 0;
    do {
        func_131B60(&D_00484744->f084[i], 0, 0x28);
        func_28F510(D_00484710, 0x763B, NULL, i);
        func_28F100(D_00484710, 0x763B, 0, 0, i);
        func_28F670(D_00484710, 0x763B, 0, 0, 0, 0, i);
        func_28F670(D_00484710, 0x7639, 0, 0, 0, 0, i);
        i += 1;
    } while (i < 8);
    total = 0;
    n = 0;
    while (e = func_370040(&it), e != 0) {
        total += e->f10;
        k = n - a;
        if ((k >= 0) && (k < 8)) {
            func_3FDAF0(e, &D_00484744->f084[k]);
            func_28F510(D_00484710, 0x763B, &D_00484744->f084[k], k);
            func_291250(D_00484710, 0x763B, k, e->f10);
            func_28F100(D_00484710, 0x763B, 0xC, 0x10, k);
            func_28F670(D_00484710, 0x763B, 0xC, 0x10, 0xC, 0x10, k);
            func_28F670(D_00484710, 0x7639, 0xE, 0x12, 0xE, 0x12, k);
        }
        n += 1;
    }
    func_291250(D_00484710, 0x763C, 0, total);
    return n;
}
