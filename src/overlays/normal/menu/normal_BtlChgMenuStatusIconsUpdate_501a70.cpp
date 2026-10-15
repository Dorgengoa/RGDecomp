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
 * detail page.  It copies the 10-entry D_00525170 action table onto the stack
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
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual void s045();
    virtual void s046();
    virtual void s047();
    virtual void s048();
    virtual void s049();
    virtual void s050();
    virtual void s051();
    virtual void s052();
    virtual void s053();
    virtual void s054();
    virtual void s055();
    virtual void s056();
    virtual void s057();
    virtual void s058();
    virtual void s059();
    virtual void s060();
    virtual void s061();
    virtual void s062();
    virtual void s063();
    virtual void s064();
    virtual void s065();
    virtual void s066();
    virtual void s067();
    virtual void s068();
    virtual void s069();
    virtual void s070();
    virtual void s071();
    virtual void s072();
    virtual void s073();
    virtual void s074();
    virtual void s075();
    virtual void s076();
    virtual void s077();
    virtual void s078();
    virtual void s079();
    virtual void s080();
    virtual void s081();
    virtual void s082();
    virtual void s083();
    virtual void s084();
    virtual void s085();
    virtual void s086();
    virtual void s087();
    virtual void s088();
    virtual void s089();
    virtual void s090();
    virtual void s091();
    virtual void s092();
    virtual void s093();
    virtual void s094();
    virtual void s095();
    virtual void s096();
    virtual void s097();
    virtual void s098();
    virtual void s099();
    virtual void s100();
    virtual s32  has(s32 k);                       /* slot 101 -> vtable +0x19C */
};

typedef struct Act  { s16 f00; s16 f02; s16 f04; } Act;
typedef struct Root { u8 pad00[0x18]; s32 f18; } Root;

extern const s16 D_00525170[];

extern void *D_0048449C;          /* gp - 0xCD4  */
extern s16   D_004844DC;          /* gp - 0xC94  */
extern s16   D_004844E0;          /* gp - 0xC90  */
extern void *D_00481BB8;          /* gp - 0x35B8 */
extern s16   D_00480550;          /* gp - 0x4C20 */
extern s16   D_00480552;          /* gp - 0x4C1E */

extern "C" {

extern Root *func_1FEDE0(void);
extern s32   func_28AA30(void *w, s16 a);
extern void  func_28F9D0(void *w, u16 id, s16 a, s32 b, s32 c, s32 d, s32 e);
extern void  func_28FC30(void *w, u16 id, s32 a, s32 b, s32 c);
extern void  func_290010(void *w, u16 id, s32 a, s32 b);
extern void  func_290B20(void *w, u16 id, s32 a, s32 b, s32 c, s32 d);
extern s32   func_3C2010(s32 w, s32 a, s32 b);
extern Ent  *func_3C2FB0(s32 w, s32 k);

}

extern "C" void normal_BtlChgMenuStatusIconsUpdate_501a70(s32 a)
{
    s16   sel[2];
    Act   tbl[10];
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

    sp = (s16 *)D_00525170;
    dp = (s16 *)tbl;
    k = 0xF;
    do {
        dp[0] = sp[0];
        dp[1] = sp[1];
        sp += 2;
        dp += 2;
        k--;
    } while (k > 0);
    t = func_1FEDE0();
    if (t == 0) {
        return;
    }
    func_3C2010(t->f18, 1, 1);
    e = func_3C2FB0(t->f18, (s16)a);
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
    func_290010(D_0048449C, 0x33, 1, -1);
    if ((s16)cnt == 0) {
        D_004844E0 = -1;
        D_004844DC = 0;
        func_290010(D_0048449C, 0x33, 0, -1);
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
        func_28FC30(D_0048449C, 0x34, 0x12, 0x12, 0);
        func_28F9D0(D_0048449C, 0x34, tbl[D_004844E0].f04, 0x9E, 0x12, 0x12, 0);
        func_290B20(D_0048449C, 0x34,
                    func_28AA30(D_00481BB8, tbl[D_004844E0].f02), -1, -1, 0);
        func_290010(D_0048449C, 0x34, 1, -1);
    }
}
