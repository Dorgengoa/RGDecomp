#include "types.h"

/* insmenu 0x004F2500 -- build the equipment panel.  96 instructions, 15 calls,
 * ONE loop with a nested guard.
 *
 * ★ `slti $1, $16, 0x4` lands in $at and that is the DEFAULT polarity of the
 * $at class ([[at-compare-class]]): the consumer is `beql`, i.e. the branch is
 * taken on `>=`, so the natural `if (i < 4)` spelling already gives $at and
 * there is nothing to steer.  The latch's `slti $2, $16, 0x5` feeding `bnel`
 * is the mirror -- a strict `<` continue-condition, which is a GPR -- so
 * `for (i = 0; i < 5; i++)` is right and `i <= 4` would move it to $at.
 *
 * ★ The `beql` delay slot carries `addiu $16, $16, 0x1`, the loop increment,
 * which is the MERGE's first instruction duplicated -- a plain forward branch
 * around the guarded call, not a case body.
 *
 * ★ D_004842FC is re-read at the top of every iteration (it fills the latch's
 * delay slot); that falls out of the plain global read across a call boundary.
 */

extern const u8 D_004FA180[];
extern s32 D_004842FC;      /* gp - 0xE74 */

extern void insmenu_InsectVsFrameSetTintMaybe_4ea290(s32 a, s32 b, f32 t);
extern void *func_28FE10(const void *a, s32 id, s32 c);
extern void func_28BBB0(void *a, s32 b, s32 c);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern void func_290010(const void *h, s32 id, s32 a, s32 b);
extern void func_2907A0(const void *a, s32 id, f32 v);
extern const void *func_28AA30(s32 a, s32 id);
extern void func_28F510(const void *a, s32 id, const void *p, s32 d);
extern void func_28F590(const void *h, s32 id, s32 a, s32 b);
extern void func_28FC30(const void *a, s32 b, s32 c, s32 d, s32 e);

void insmenu_InsectVsRegisterPanelLayout_4f2500(void)
{
    void *w;
    const void *t;
    s32 i;

    insmenu_InsectVsFrameSetTintMaybe_4ea290(0x17, 0x2B, 4.0f);
    w = func_28FE10(D_004FA180, 0x17, 0);
    func_28BBB0(w, 0xFA, 0x2B);
    func_290F60(D_004FA180, 0x15, 0x26, 0x50);
    w = func_28FE10(D_004FA180, 0x3C, 0);
    func_28BBB0(w, 0x7D, 0x2B);
    func_290F60(D_004FA180, 0x3C, 0, 0xAC);
    func_290010(D_004FA180, 0x15, 1, -1);
    func_2907A0(D_004FA180, 0x15, 0.0f);

    for (i = 0; i < 5; i++) {
        t = func_28AA30(D_004842FC, i + 0xF);
        func_28F510(D_004FA180, 0x3D, t, i);
        if (i < 4) {
            func_28F590(D_004FA180, 0x3D, 0x27, i);
        }
    }

    func_28FC30(D_004FA180, 0x16, 0xEE, 0x1F, 0);
    func_290F60(D_004FA180, 0x16, 0, 0);
    func_2907A0(D_004FA180, 0x16, 0.0f);
}
