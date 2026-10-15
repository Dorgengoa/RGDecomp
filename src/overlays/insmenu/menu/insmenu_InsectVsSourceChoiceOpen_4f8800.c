#include "types.h"

/* insmenu 0x004F8800 -- `beqz $5` branches AWAY, so the block is the
 * FALL-THROUGH and the condition is `!= 0`; $4 is never read.
 *
 * ★ The tail guard is `c.lt.s $f0, $f1` (f1 = 1.0f) with `bc1tl` branching
 * AWAY, which is `>= 1.0f` -- MIPS has no `c.ge.s`.
 * ★ `daddu $7, $6, $0` after `addiu $6, $0, 0x1` is mwcc SHARING a constant it
 * already materialised, not a computed argument: write both literals.
 * ★ `sll $2, $3, 5 / subu $7, $2, $3` is `x * 31`.
 * ★ `D_0048436C = 0;` written BEFORE the first call fills its delay slot.
 */
typedef struct {
    u8  pad00[0x16];
    s16 field16;
} Ent;

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern s16 D_0048436C;      /* gp - 0xE04 */
extern s16 D_004842E8;      /* gp - 0xE88 */
extern f32 D_0047D460;

extern void *func_28FE10(const void *a, s32 id, s32 c);
extern void  func_28B8E0(void *a, s32 b, s32 c, s32 d);
extern void  func_291110(const void *a, s32 id, s32 c, s32 d);
extern void  func_2907A0(const void *a, s32 id, f32 v);
extern void  func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern s32   insmenu_InsectVsGetMsgTable_4f3320(void);
extern const void *func_28AA30(s32 a, s32 id);
extern void  func_28F510(const void *a, s32 id, const void *p, s32 d);
extern void  func_290F60(const void *a, s32 b, s32 c, s32 d);
extern Ent  *func_28EA40(const void *a, s32 b);
extern f32   func_290770(const void *a, s32 b);
extern void  func_28EDE0(void *a, s32 id, s32 c);

s32 insmenu_InsectVsSourceChoiceOpen_4f8800(s32 unused, s32 a)
{
    void *w;
    const void *t;
    Ent *e;

    if (a != 0) {
        D_0048436C = 0;
        w = func_28FE10(D_004FA180, 0x5C, 0);
        func_28B8E0(w, 0xF0, 0x46, 2);
        func_291110(D_004FA180, 0x5C, 1, 1);
        func_2907A0(D_004FA180, 0x5C, 0.0f);
        func_290690(D_004FA180, 0x5C, 1.0f, D_0047D460, -1.0f);
        func_2907A0(D_004FA180, 0x5E, 0.0f);
        t = func_28AA30(insmenu_InsectVsGetMsgTable_4f3320(), 0x578);
        func_28F510(D_004FA180, 0x5C, t, 0);
        t = func_28AA30(insmenu_InsectVsGetMsgTable_4f3320(), 0x579);
        func_28F510(D_004FA180, 0x5C, t, 1);
        func_290F60(D_004FA180, 0x5C, 0x88, 0xBE);
        e = func_28EA40(D_004FA1A0, 0x88C2);
        if (e != 0) {
            func_290F60(D_004FA180, 0x5D, 0, e->field16 * 31);
        }
    }
    if (func_290770(D_004FA180, 0x5C) >= 1.0f) {
        func_28EDE0(&D_004842E8, 0x88C7, 0);
    }
    return 1;
}
