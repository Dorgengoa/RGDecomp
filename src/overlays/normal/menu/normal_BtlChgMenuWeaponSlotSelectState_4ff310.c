#include "types.h"
/* normal 0x004FF310 -- the shop/party picker's per-frame step.  func_28E170
 * returns the list state (2 = cancelled, 1 = confirmed); the panel handle is
 * fetched unconditionally because the confirmed arm reads its +0x12 row.
 * `$17` is a POINTER to the 0x450 selection pair, not the context pointer:
 * retail materialises `ctx + 0x450` and reads it at displacement 0. */

typedef struct Root  { u8 pad00[0x18]; s32 f18; } Root;
typedef struct Panel { u8 pad00[0x12]; s16 f12; } Panel;
typedef struct Ref   { u8 pad00[0x0C]; s32 f0C; } Ref;
typedef struct Ctx   { u8 pad000[0x450]; s16 f450; s16 f452; } Ctx;

extern Ctx  *D_00484454;          /* gp - 0xD1C */
extern void *D_00484498;          /* gp - 0xCD8 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern void *D_004844A0;          /* gp - 0xCD0 */
extern const u8 D_004B2570[];

extern void   func_28EA90(void *w, s32 id, s32 a);
extern s32    func_28E170(const void *a, const void *b, s32 c, s32 d);
extern Panel *func_28EC60(const void *a);
extern void   func_291110(void *w, u16 id, s32 c, s32 d);
extern void   func_28EDE0(void *w, s32 id, s32 a);
extern Root  *func_1FEDE0(void);
extern s32    normal_BtlChgPageGetMember_505f90(void *p);
extern Ref   *func_3C2FB0(s32 a, s32 b);
extern void   func_204C90(s32 a, s32 b);
extern void   func_204D40(s32 a, s32 b);

s32 normal_BtlChgMenuWeaponSlotSelectState_4ff310(void *a, s32 b)
{
    s32    st;
    Panel *pn;
    s16   *sel;
    Root  *root;
    Ref   *rf;
    s32    n;

    if (b != 0) {
        func_28EA90(D_004844A0, 0x55F9, 0);
    }
    st = func_28E170(D_004844A0, D_004B2570, 4, 0);
    pn = func_28EC60(D_004844A0);
    if (st == 2) {
        func_291110(D_0048449C, 0x3E, 0, 1);
        func_28EDE0(D_00484498, 0x55F6, 0);
    } else if (st == 1) {
        sel = &D_00484454->f450;
        root = func_1FEDE0();
        if (root == 0) {
            return 0;
        }
        n = normal_BtlChgPageGetMember_505f90(D_00484454);
        rf = func_3C2FB0(root->f18, n);
        if (rf != 0) {
            if (sel[0] != rf->f0C || pn->f12 != sel[1]) {
                func_204C90(sel[0], sel[1]);
                D_00484454->f450 = rf->f0C;
                D_00484454->f452 = pn->f12;
                func_204D40(D_00484454->f450, D_00484454->f452);
            }
        }
        func_28EDE0(D_00484498, 0x55FF, 0);
    }
    return 1;
}
