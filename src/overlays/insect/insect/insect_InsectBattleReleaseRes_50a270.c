#include "types.h"
/* insect 0x0050A270 -- 492 bytes, 123 instructions, 31 calls, 6 conditional
 * branches, br/ins 0.049.  The insect scene's teardown: it releases the 0x80+i
 * resource band, drops five sound cues and clears the 0x4D flag it tested on
 * the way in.
 *
 * Five `insect_InsectBattleTestFlag_50da40` guards, and the polarity of each is read off the
 * branch: `bnel` past the block is `== 0` (the block is the fall-through),
 * `beql` past it is `!= 0`.  Two of the five are `== 0` and three are `!= 0`.
 *
 * The first guard's `beql`-family branch carries `addiu $17, $0, 0xE` -- the
 * loop counter's initialiser, which is also the guarded block's own last
 * instruction, duplicated.  One `i = 0xE;` in the source, after the `if`.
 *
 * o->f4B4C is REMATERIALISED at its one site so it is an array member.
 *
 * ★ `t1` is declared FIRST because it is the only value that gets $18; every
 * other callee-saved value here has a disjoint lifetime and coalesces into $17.
 * Declaration order, descending from the highest.
 */

typedef struct Ins {
    u8    pad000[0x870];
    void *f870;                 /* +0x0870 */
    u8    pad874[0x4B4C - 0x874];
    u8    f4B4C[4];             /* +0x4B4C */
} Ins;

extern void  func_14D830(void *p);
extern void  func_158AC0(void *h, s32 k);
extern void *func_15DE40(void);
extern void  func_1B0870(void *p);
extern void  func_1C3DC0(void *h, s32 a, s32 b, s32 c);
extern void *func_1C4A90(void *h, s32 k);
extern void  func_1C4C70(void *h, s32 k);
extern void  func_1CFB10(void *h, s32 k, f32 v);
extern void  func_1CFC50(void *h, s32 k);
extern void *func_1ED3F0(void *g, s32 k);
extern void *func_1FDB70(void);
extern void *func_206A40(void);
extern void  func_42B650(void *p, s32 k);

extern s32  insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern void insect_InsectBattleClearFlag_50da90(Ins *o, s32 k);
extern void insect_InsectModelMemReleaseAll_512280(void *a);

void insect_InsectBattleReleaseRes_50a270(Ins *o)
{
    void *t1;
    void *p;
    s32 i;
    void *h;
    void *g;
    void *t2;

    func_1CFB10(o->f870, 0, 1.0f);
    func_1CFB10(o->f870, 0xC, 1.0f);
    func_1C3DC0(o->f870, 1, 0, 0x10);
    if (insect_InsectBattleTestFlag_50da40(o, 0x4D) == 0) {
        p = func_206A40();
        func_42B650(p, 2);
        func_42B650(p, 3);
    }
    i = 0xE;
    do {
        func_1B0870(func_1C4A90(o->f870, i + 0x80));
        func_1CFC50(o->f870, i + 0x80);
        func_1C4C70(o->f870, i + 0x80);
        i++;
    } while (i < 0x1A);
    if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
        func_1CFC50(o->f870, 0x8A);
    }
    func_1CFC50(o->f870, 0x9B);
    insect_InsectModelMemReleaseAll_512280(o->f4B4C);
    h = func_15DE40();
    func_158AC0(h, 0x29C);
    func_158AC0(h, 0x29D);
    if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
        func_158AC0(h, 0x241);
    }
    func_158AC0(h, 0x242);
    if (insect_InsectBattleTestFlag_50da40(o, 0x4D) == 0) {
        func_158AC0(func_15DE40(), 0x29E);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
        g = func_1FDB70();
        t1 = func_1ED3F0(g, 1);
        t2 = func_1ED3F0(g, 2);
        func_14D830(t1);
        func_14D830(t2);
    }
    insect_InsectBattleClearFlag_50da90(o, 0x4D);
}
