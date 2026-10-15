#include "types.h"
/* insect 0x004FAF00 -- 668 bytes, 167 instructions, 18 calls, 7 conditional
 * branches, br/ins 0.042.  From x_band.py's branch-light band; no jalr, no
 * float, not a 0050d6a0 family member.
 *
 * A ten-iteration widget refresh loop.  Read off the listing:
 *
 *  - `(u8 *)o + 0x5054` is computed in the FIRST call's delay slot and parked
 *    in $18 for three later argument slots -- the HOIST polarity of
 *    insect-extern-handle-hoist, so it is a named local assigned before the
 *    guard body's first statement;
 *  - `o->f5EAD[i]` by contrast is REMATERIALISED at all three of its sites
 *    (`sll 1 / addu / sll 1 / addu / addiu 0x5EAD` four times over), which is
 *    insect-array-member-blocks-cse's array-member form.  The element stride
 *    is 6, so the member is `u8 f5EAD[10][6]`;
 *  - `sltu $2,$0,$22 / xori $2,$2,1 / andi $2,$2,0xFF` is `(u8)!x`, NOT
 *    `x == 0` -- the two idioms are different sequences (session 13);
 *  - the colour constant is built with `ori / dsll 16 / ori`, a 64-bit
 *    materialisation, so the local is `s64`; every use is `dsll32 0 / dsra32 0`
 *    = `(s32)col` handed to an `s64` parameter;
 *  - `sd $22, 0x0($29)` is func_393020's NINTH argument, past the eight EABI
 *    argument registers, and `sd` makes that parameter 64-bit;
 *  - the `sq`/`lq` pair at 0xB0($29) is the ALLOCATOR spilling `n`: retail
 *    already holds $16..$23 and $30, so the tenth long-lived value has to go
 *    to the frame, and mwcc spills a GPR as a full quadword.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                         /* +0x0878 */
    u8    pad87C[0x4F90 - 0x87C];
    u8    f4F90[0x5054 - 0x4F90];       /* +0x4F90 */
    u8    pad5054[0x5DA8 - 0x5054];
    s32   f5DA8;                        /* +0x5DA8 */
    u8    pad5DAC[0x5EAD - 0x5DAC];
    u8    f5EAD[10][6];                 /* +0x5EAD */
    u8    pad5EE9[0x5EF1 - 0x5EE9];
    u8    f5EF1;                        /* +0x5EF1 */
} Ins;

typedef struct Ent {
    u8 pad00[0xB];
    s8 fB;                              /* +0x0B */
} Ent;

extern u8 D_00524C28[];
extern u8 D_00524C30[];

extern void func_1343B8(u8 *d, u8 *t, s32 v);
extern void func_290010(void *h, s32 id, s32 a, s32 b);
extern s32  func_290460(void *h, s32 id);
extern void func_290A40(void *h, s32 id, s32 c, s32 k);
extern void func_290F60(void *h, s32 id, s32 x, s32 y);
extern void func_3925D0(u8 *w, s32 a, s32 b, s32 c, s32 k);
extern void func_392660(u8 *w, s32 a, s32 b, s32 c, s32 d, s32 k);
extern void func_393020(u8 *w, s32 a, s32 b, s32 c, s32 k,
                        s32 p, s32 q, u8 *r, s64 t);
extern s32  insect_InsectBattleGetPoolEntry_50dc90(Ins *o, s32 k, u8 m, s32 *out);
extern Ent *insect_InsectCursorSetFindPage_511e60(u8 *p, s32 k);
extern s32  insect_InsectTeamSlotFindMember_513f60(s32 a, s32 k);

void insect_InsectBattleRosterListRefresh_4faf00(Ins *o, s32 arg)
{
    s32  out[6];
    u8  *w;
    s32  a;
    s32  b;
    s32  c;
    s32  d;
    s32  i;
    s64  t;
    s32  n;
    s32  k;
    s64  col;

    if (arg != 0) {
        w = (u8 *)o + 0x5054;
        func_290F60(o->f878, 0x7553, 0, 0);
        a = func_290460(o->f878, 0x754F);
        b = func_290460(o->f878, 0x7551);
        c = func_290460(o->f878, 0x7552);
        d = func_290460(o->f878, 0x758F);
        t = o->f5DA8;
        func_290010(o->f878, 0x758F, (u8)!t, -1);
        n = insect_InsectCursorSetFindPage_511e60(o->f4F90, 1)->fB;
        for (i = 0; i < 10; i++) {
            k = n - 1 + i;
            if (k >= 0) {
                if (insect_InsectBattleGetPoolEntry_50dc90(o, k, o->f5EF1, out) != 0) {
                    if ((out[2] >= 5) && (out[3] >= 0x2BC)) {
                        func_1343B8(o->f5EAD[i], D_00524C28, out[2]);
                    } else {
                        func_1343B8(o->f5EAD[i], D_00524C30, out[2]);
                    }
                }
                func_393020(w, a, b, c, i, out[0], out[1], o->f5EAD[i], t);
                func_3925D0(w, d, out[4], 1, i);
                func_392660(w, d, 0, out[5], 1, i + 10);
            }
            col = 0xFF7F7F7F;
            if (insect_InsectTeamSlotFindMember_513f60(arg, k) != -1) {
                col = 0xFF202020;
            }
            func_290A40(o->f878, 0x7551, col, i);
            func_290A40(o->f878, 0x754F, col, i);
            func_290A40(o->f878, 0x7552, col, i);
            func_290A40(o->f878, 0x7550, col, i);
        }
    }
}
