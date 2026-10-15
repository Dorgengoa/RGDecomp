#include "types.h"

/* factory.bin overlay, 0x004EE660 -- 90 words, MATCH (session 23, lane fz23a).
 * Was 6 bad.  TWO levers, both needed:
 *   1. DISPATCH BRANCH POLARITY.  Retail `bnel $2,$3` PAST the arm, ours
 *      `beql $2,$3` INTO it.  Inverting BOTH guards -- `if (f5C == 1) ok = 0;
 *      else { if (f70 == 1) ok = 0; else ok = 1; }` instead of
 *      `if (f5C != 1) { if (f70 != 1) ok = 1; else ok = 0; } else ok = 0;` --
 *      fixed all six words but left the object ONE WORD LONG (91 vs 90).
 *   2. The extra word was `andi $2,$2,0xFF` at 0x004EE718, the u8 re-narrow of
 *      `ok` at the join.  It is the `!= 0` TOKEN: writing `if (ok)` instead of
 *      `if (ok != 0)` deletes it.  Each arm already narrows itself (`andi
 *      $2,$3,0xFF` for 1, `daddu $2,$0,$0` for 0) so the join narrow is pure
 *      tax.  `ok` MUST stay u8 -- retail's `ok = 1` IS the andi of $3.
 */

typedef struct Glob {
    u8    pad00[0x5C];
    u8    f5C;
    u8    pad5D[0x3];
    void *f60;
    void *f64;
    void *f68;
    u8    pad6C[0x4];
    u8    f70;
} Glob;

typedef struct Ctx {
    u8    pad00[0x70];
    void *f70;
    u8    pad74[0x1C];
    u8    f90;
} Ctx;

extern Glob *D_00484A50;                        /* _gp - 0x720 */
extern Ctx  *D_00484A48;                        /* _gp - 0x728 */
extern u8    D_004B2570[0x10];

extern void  func_28EA90(void *h, s32 id, s32 a);
extern void  factory_FactoryMoveShowPartInfo_4f4130(Glob *g);
extern void  func_28E170(void *h, u8 *p, s32 a, s32 b);
extern s32   factory_FactoryMoveWaitRequest_4f43e0(Glob *g);
extern void  func_28EDE0(void *h, s32 id, s32 a);
extern s32   func_1839F0(u8 *p, s32 mask);
extern void *func_207DF0(void);
extern void  func_1B9520(void *m, s32 id, s32 a, f32 v);
extern s32  *func_367EC0(void);
extern void  func_290690(void *h, s32 id, f32 a, f32 b, f32 c);

s32 factory_FactoryMoveStateTick_4ee660(void *w, s32 flag)
{
    u8    ok;
    void *b;
    void *h;
    void *a;
    s32  *q;

    b = D_00484A50->f60;
    a = D_00484A50->f68;
    h = D_00484A50->f64;
    if (flag != 0) {
        func_28EA90(h, 0x88FE, 1);
    }
    factory_FactoryMoveShowPartInfo_4f4130(D_00484A50);
    func_28E170(D_00484A50->f64, D_004B2570, 1, 0);
    if (factory_FactoryMoveWaitRequest_4f43e0(D_00484A50) != 0) {
        func_28EDE0(a, 0x893A, 0);
    } else if (func_1839F0(D_004B2570, 0x80) != 0) {
        if (D_00484A50->f5C == 1) {
            ok = 0;
        } else {
            if (D_00484A50->f70 == 1) {
                ok = 0;
            } else {
                ok = 1;
            }
        }
        if (ok) {
            func_1B9520(func_207DF0(), 5, 0, 1.0f);
            q = func_367EC0();
            *q = 1;
            D_00484A48->f90 = 2;
            if (D_00484A48->f70 != 0) {
                func_28EDE0(a, 0x88F4, 0);
            } else {
                func_28EDE0(a, 0x88D6, 0);
            }
            func_290690(b, 0x4D, 0.0f, -0.125f, -1.0f);
        }
    }
    return 1;
}
