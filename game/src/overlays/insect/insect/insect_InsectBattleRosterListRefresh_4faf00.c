/* rgp:protos */
#define RGP_SELF_insect_InsectBattleRosterListRefresh_4faf00 1
#include "port/game_protos.h"
#line 1
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

extern u8 insect_D_00524C28[];
extern u8 insect_D_00524C30[];

extern void Sprintf_1343b8(u8 *d, u8 *t, s32 v);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleRosterListRefresh_4faf00(Ins *o, s32 arg)
{
    s32  out[6] __attribute__((aligned(16)));
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
        UiSetWidgetPos_290f60(o->f878, 0x7553, 0, 0);
        a = ((s32)UiFindWidget_290460(o->f878, 0x754F));
        b = ((s32)UiFindWidget_290460(o->f878, 0x7551));
        c = ((s32)UiFindWidget_290460(o->f878, 0x7552));
        d = ((s32)UiFindWidget_290460(o->f878, 0x758F));
        t = o->f5DA8;
        UiSetWidgetVisible_290010(o->f878, 0x758F, (u8)!t, -1);
        n = ((Ent *)insect_InsectCursorSetFindPage_511e60(o->f4F90, 1))->fB;
        for (i = 0; i < 10; i++) {
            k = n - 1 + i;
            if (k >= 0) {
                if (insect_InsectBattleGetPoolEntry_50dc90(o, k, o->f5EF1, out) != 0) {
                    if ((out[2] >= 5) && (out[3] >= 0x2BC)) {
                        Sprintf_1343b8(o->f5EAD[i], insect_D_00524C28, out[2]);
                    } else {
                        Sprintf_1343b8(o->f5EAD[i], insect_D_00524C30, out[2]);
                    }
                }
                InsectUiRosterRowSetTextMaybe_393020(w, a, b, c, i, out[0], out[1], o->f5EAD[i], (int)(t));
                UiIconSetUvByIndexMaybe_3925d0(w, d, out[4], 1, i);
                UiToggleIconPairLayoutRelated_392660(w, d, 0, out[5], 1, i + 10);
            }
            col = 0xFF7F7F7F;
            if (insect_InsectTeamSlotFindMember_513f60(arg, k) != -1) {
                col = 0xFF202020;
            }
            UiSetTextColor_290a40(o->f878, 0x7551, col, i);
            UiSetTextColor_290a40(o->f878, 0x754F, col, i);
            UiSetTextColor_290a40(o->f878, 0x7552, col, i);
            UiSetTextColor_290a40(o->f878, 0x7550, col, i);
        }
    }
}
