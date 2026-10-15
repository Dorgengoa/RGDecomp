#include "types.h"
/* insect 0x004FB7C0 -- 640 bytes, 160 instructions, 25 calls, 6 conditional
 * branches, br/ins 0.037.  A five-phase 0x765C/0x765D/0x765E widget driver on
 * the insect_InsectBattleGetStep_50d6a0(o, 2) state.
 *
 * Compare chain 5, 4, 3, 2, 1 -- REVERSED -- so source order is 1, 2, 3, 4, 5,
 * which is also the block order (0x4FB81C, 0x4FB8E4, 0x4FB97C, 0x4FB994,
 * 0x4FB9EC).  There are no empty cases: the DEFAULT is the one that gets the
 * epilogue-head-PLUS-ONE target (`b .L004FBA34` with `ld $31` in its own delay
 * slot) while every case arm branches to the head itself.
 *
 * o->f506C is REMATERIALISED at all four of its sites (bare
 * `addiu $4, $16, 0x506C`), so it is an array member.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x506C - 0x880];
    u8    f506C[4];             /* +0x506C */
    u8    pad5070[0x5DA0 - 0x5070];
    s32   f5DA0;                /* +0x5DA0 */
} Ins;

extern const u8 D_005240B0[];

extern void func_28F510(void *h, s32 id, s32 a, s32 b);
extern void func_28F5D0(void *h, s32 id, s32 a, s32 b, s32 c);
extern void func_290010(void *h, s32 id, s32 a, s32 b);
extern void func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32  func_290770(void *h, s32 id);
extern void func_2907A0(void *h, s32 id, f32 v);

extern void insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern s32  insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern s32  insect_InsectMsgCenterX_512b10(void *a, s32 k, s32 v);
extern s32  insect_InsectMsgGet_512b70(void *a, s32 k);

void insect_InsectBattleMenuVictoryCondSelect_4fb7c0(Ins *o)
{
    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        func_290010(o->f878, 0x765C, 1, -1);
        func_28F510(o->f878, 0x765D, insect_InsectMsgGet_512b70(o->f506C, 0x3E8), 0);
        func_28F5D0(o->f878, 0x765D,
                    insect_InsectMsgCenterX_512b10(o->f506C, 0x3E8, o->f5DA0 + 0x40),
                    0xA, 0);
        func_28F510(o->f878, 0x765E, insect_InsectMsgGet_512b70(o->f506C, 0x3EA), 0);
        func_28F510(o->f878, 0x765E, insect_InsectMsgGet_512b70(o->f506C, 0x3E9), 1);
        func_290010(o->f87C, 0xC37E, 1, -1);
        insect_InsectBattleSetStep_50d7a0(o, 2, 2, -1);
        break;
    case 2:
        func_2907A0(o->f878, 0x765C, 0.0f);
        func_290690(o->f878, 0x765C, 1.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_005240B0, 1);
        insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 4, 0, -1);
        break;
    case 3:
        insect_InsectBattleCursorUpdateDesc_4f4530(o, D_005240B0, 0);
        break;
    case 4:
        func_290690(o->f878, 0x765C, 0.0f, 0.125f, -1.0f);
        func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
        insect_InsectBattleSetStep_50d7a0(o, 5, 2, -1);
        break;
    case 5:
        if (func_290770(o->f878, 0x765C) <= 0.0f) {
            insect_InsectBattleSetStep_50d7a0(o, 6, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 6, 0, -1);
        }
        break;
    }
}
