#include "types.h"
/* insect 0x004FBA40 -- 628 bytes, 157 instructions, 22 calls, 6 conditional
 * branches, br/ins 0.038.  The 0x7585-0x7588 panel builder on the
 * insect_InsectBattleGetStep_50d6a0(o, 2) state.
 *
 * Compare chain 3, 0x1D, 1 -- REVERSED -- so source order is 1, 0x1D, 3, which
 * is the block order (0x4FBA94, 0x4FBC24, 0x4FBC58).  Case 0x1D FALLS THROUGH
 * into case 3: its last instruction (`lw $4, 0x878($18)` at 0x4FBC54) is case
 * 3's first argument load, hoisted, and there is no `b` between them.
 *
 * D_00525FF0 is REMATERIALISED with its own `lui`/`addiu` at every one of its
 * nine sites, so it stays a plain extern reference -- the opposite of the same
 * family's 0x0050EAF0, where retail hoists the identical kind of handle into a
 * callee-saved register and the source needs a local.  Read which one retail
 * did off the listing; it is not a property of the callee.
 *
 * Both `(o->f5DA0 - 0x1B8) / 2` divides are written out as `bgez / addiu 1 /
 * sra 1`, the SIGNED divide-by-two, so the source really divides.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    u8    pad87C[0x506C - 0x87C];
    u8    f506C[4];             /* +0x506C */
    u8    pad5070[0x5DA0 - 0x5070];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
    u8    pad5DA8[0x5EF1 - 0x5DA8];
    u8    f5EF1;                /* +0x5EF1 */
} Ins;

extern u8 D_00525FF0[];

extern void  func_28F510(void *h, s32 id, s32 a, s32 b);
extern void  func_290010(void *h, s32 id, s32 a, s32 b);
extern void *func_290460(void *h, s32 id);
extern void  func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32   func_290770(void *h, s32 id);
extern void  func_2907A0(void *h, s32 id, f32 v);
extern void  func_290F60(void *h, s32 id, s32 x, s32 y);
extern void  func_3934D0(void *g, void *w, s32 a, s32 b, s32 c, u8 d);
extern void  func_3939E0(void *g, void *w, s32 a, s32 b, f32 x, f32 y);
extern void  func_393AC0(void *g, void *w, s32 a, s32 b, s32 c);

extern s32  insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern s32  insect_InsectMsgGet_512b70(void *a, s32 k);

void insect_InsectBattleMenuReport_4fba40(Ins *o)
{
    void *p;
    void *g;

    p = (u8 *)o + 0x506C;
    g = (u8 *)o + 0x5054;
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        func_393AC0(g, func_290460(D_00525FF0, 0x7586), 0x1B8, 0x124, 0);
        func_3939E0(g, func_290460(D_00525FF0, 0x7588), 1, 0, 432.0f, 288.0f);
        func_3934D0(g, func_290460(D_00525FF0, 0x7587), 0x1B0, 0x11C, 1,
                    o->f5EF1);
        func_290010(D_00525FF0, 0x7585, 1, -1);
        func_290F60(D_00525FF0, 0x7586, (o->f5DA0 - 0x1B8) / 2,
                    (o->f5DA4 - 0x124) / 2);
        func_2907A0(D_00525FF0, 0x7586, 0.0f);
        func_290690(D_00525FF0, 0x7586, 1.0f, 0.125f, -1.0f);
        func_290F60(o->f878, 0x7588, 0, 0x20);
        func_28F510(o->f878, 0x7586, insect_InsectMsgGet_512b70(p, 0x27), 0);
        func_290F60(o->f878, 0x7587, 4, 4);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
        break;
    case 0x1D:
        func_290690(o->f878, 0x7586, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
        /* fallthrough */
    case 3:
        if (func_290770(o->f878, 0x7586) <= 0.0f) {
            insect_InsectBattleSetState_50d8c0(o, 0x28, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
        }
        break;
    }
}
