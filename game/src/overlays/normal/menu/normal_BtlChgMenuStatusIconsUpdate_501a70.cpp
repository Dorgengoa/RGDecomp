/* rgp:protos */
#line 1
/* !! PARKED -- lane r2b, session 19 round 2.  NOT byte-identical.  Do NOT add
 * to config/ocunits/normal.txt.
 *
 * RESIDUE: ONE WORD SHORT (0x2C4 vs 0x2C8).  Every register, every guard
 * polarity, every branch-likely and the whole tail are otherwise aligned --
 * the file went 178-word `?` with a full callee-saved permutation to a single
 * missing instruction.
 *
 * THE MISSING WORD: @0x00501B7C retail computes the stack table's element
 * address in TWO steps
 *      addu  $v0,$v0,$sp        ; sp + (s16)j*6
 *      addiu $v0,$v0,0x40       ; + the local's frame offset
 *      lh    $v0,0x0($v0)
 * where mwcc folds the frame offset into the load displacement
 * (`lh $v0,0x40($v0)`).  The SAME unit folds it correctly 30 words later
 * (`lh $6,0x44($2)`), so this is one access spelled differently, not a
 * global addressing-mode difference.  ARMS (3, all one object == the folded
 * form): `tbl[(s16)j].f00`; `ap = &tbl[(s16)j], ap->f00` as a comma in the
 * while-condition (mwcc dead-store-eliminates `ap`); `*(s16 *)&tbl[(s16)j]`.
 * A FOURTH arm `*(s16 *)((s32)tbl + (s16)j * 6)` is 2 words LONG -- mwcc
 * hoists `(s32)tbl` into a callee-saved register outside the loop and shifts
 * every other allocation.  Same family as the frame-address CSE class
 * (`0050ef80` sp+i*6, 19 spellings; `00503930`, 16 spellings) that
 * LEVERS.md already stop-lists.
 */
#include "types.h"
/* normal 0x00501A70 -- the twin of normal_FUN_004F5F00 for the single-member
 * detail page.  It copies the 10-entry normal_D_00525170 action table onto the stack
 * two halfwords at a time, asks the member (virtual slot 101) which entries it
 * can perform, keeps at most two ids in `sel`, and drives the 0x33/0x34 chip
 * from the gp pair D_004844E0 (current) / D_004844DC (stickiness), rotating
 * only after 0x14 frames.
 *
 * `lw $25,0($16) / lw $25,0x19C($25) / jalr $25` -> C++ virtual, vptr 0,
 * slot (0x19C-8)/4 = 101.
 * `daddiu $5,$0,1` for the "already selected" flag is a C++ `bool`.
 * The stack copy runs at stride 4 over a table whose ENTRIES are 6 bytes --
 * 15 two-halfword iterations, not 10 entry copies. */

struct Ent {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 has(s32 k) { return VCM(s32, (void *, s32), 0x19C, k); }                       /* slot 101 -> vtable +0x19C */
};

typedef struct Act  { s16 f00; s16 f02; s16 f04; } Act;
typedef struct Root { u8 pad00[0x18]; s32 f18; } Root;

extern "C" s16 normal_D_00525170[];

extern "C" void *D_0048449C;          /* gp - 0xCD4  */
extern "C" s16   D_004844DC;          /* gp - 0xC94  */
extern "C" s16   D_004844E0;          /* gp - 0xC90  */
extern "C" void *D_00481BB8;          /* gp - 0x35B8 */
extern "C" s16   D_00480550;          /* gp - 0x4C20 */
extern "C" s16   D_00480552;          /* gp - 0x4C1E */

extern "C" {

extern Root *GetGameData_1fede0(void);
extern s32   MsgTableLookup_28aa30(void *w, s16 a);
extern void  UiSetSpriteUvRect_28f9d0(void *w, u16 id, s16 a, s32 b, s32 c, s32 d, s32 e);
extern void  UiSetSpriteSize_28fc30(void *w, u16 id, s32 a, s32 b, s32 c);
extern void  UiSetWidgetVisible_290010(void *w, u16 id, s32 a, s32 b);
extern void  UiSetTextStringPos_290b20(void *w, u16 id, s32 a, s32 b, s32 c, s32 d);
extern s32   PartyCountMembers_3c2010(s32 w, s32 a, s32 b);
extern Ent  *PartyGetSlotChara_3c2fb0(s32 w, s32 k);

}

extern "C" void normal_BtlChgMenuStatusIconsUpdate_501a70(s32 a)
{
    s16   sel[2];
    Act   tbl[10] __attribute__((aligned(16)));
    s32   j;
    s32   cnt;
    Ent  *e;
    Root *t;
    s32   v;
    s32   q;
    s32   cur;
    s16  *sp;
    s16  *dp;
    s32   k;
    Act  *ap;
    bool  found;

    sp = (s16 *)normal_D_00525170;
    dp = (s16 *)tbl;
    k = 0xF;
    do {
        dp[0] = sp[0];
        dp[1] = sp[1];
        sp += 2;
        dp += 2;
        k--;
    } while (k > 0);
    t = GetGameData_1fede0();
    if (t == 0) {
        return;
    }
    PartyCountMembers_3c2010(t->f18, 1, 1);
    e = PartyGetSlotChara_3c2fb0(t->f18, (s16)a);
    if (e == 0) {
        return;
    }
    j = 0;
    cnt = 0;
    sel[0] = D_00480550;
    sel[1] = D_00480552;
    while ((v = *(s16 *)(s32)&tbl[(s16)j]) > 0) {
        if (e->has((s16)v) != 0) {
            sel[(s16)cnt] = (s16)j;
            cnt = (s16)(cnt + 1);
            if (cnt >= 2) {
                break;
            }
        }
        j = (s16)(j + 1);
    }
    UiSetWidgetVisible_290010(D_0048449C, 0x33, 1, -1);
    if ((s16)cnt == 0) {
        D_004844E0 = -1;
        D_004844DC = 0;
        UiSetWidgetVisible_290010(D_0048449C, 0x33, 0, -1);
    } else if ((s16)cnt > 0) {
        cur = D_004844E0;
        if (cur == -1) {
            D_004844E0 = sel[0];
        } else {
            found = false;
            for (q = 0; q < 2; q++) {
                if (cur == sel[q]) {
                    found = true;
                    break;
                }
            }
            if (found) {
                D_004844DC = (s16)(D_004844DC + 1);
                if ((s16)D_004844DC >= 0x14) {
                    if ((s16)cnt >= 2) {
                        D_004844E0 = sel[q ^ 1];
                    } else {
                        D_004844E0 = sel[0];
                    }
                    D_004844DC = 0;
                }
            } else {
                D_004844DC = 0;
                D_004844E0 = sel[0];
            }
        }
        UiSetSpriteSize_28fc30(D_0048449C, 0x34, 0x12, 0x12, 0);
        UiSetSpriteUvRect_28f9d0(D_0048449C, 0x34, tbl[D_004844E0].f04, 0x9E, 0x12, 0x12, 0);
        UiSetTextStringPos_290b20(D_0048449C, 0x34,
                    MsgTableLookup_28aa30(D_00481BB8, tbl[D_004844E0].f02), -1, -1, 0);
        UiSetWidgetVisible_290010(D_0048449C, 0x34, 1, -1);
    }
}
