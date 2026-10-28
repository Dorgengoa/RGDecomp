/* rgp:protos */
#define RGP_SELF_insect_InsectBattleReleaseRes_50a270 1
#include "port/game_protos.h"
#line 1
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
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleReleaseRes_50a270(Ins *o)
{
    void *t1;
    void *p;
    s32 i;
    void *h;
    void *g;
    void *t2;

    ParamTableSetAlpha_1cfb10(o->f870, 0, 1.0f);
    ParamTableSetAlpha_1cfb10(o->f870, 0xC, 1.0f);
    ObjRecClearFlags_1c3dc0(o->f870, 1, 0, 0x10);
    if (insect_InsectBattleTestFlag_50da40(o, 0x4D) == 0) {
        p = GetMenuResGroup_206a40();
        ResGroupUnloadGroup_42b650(p, 2);
        ResGroupUnloadGroup_42b650(p, 3);
    }
    i = 0xE;
    do {
        ModelObjExEffectsStopAll_1b0870(ObjRecGetLiveObject_1c4a90(o->f870, i + 0x80));
        GameSceneObjReleaseMaybe_1cfc50(o->f870, i + 0x80);
        ObjRecReleaseResAndReset_1c4c70(o->f870, i + 0x80);
        i++;
    } while (i < 0x1A);
    if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
        GameSceneObjReleaseMaybe_1cfc50(o->f870, 0x8A);
    }
    GameSceneObjReleaseMaybe_1cfc50(o->f870, 0x9B);
    insect_InsectModelMemReleaseAll_512280(o->f4B4C);
    h = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(h, 0x29C);
    NameTableFreeGroup_158ac0(h, 0x29D);
    if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
        NameTableFreeGroup_158ac0(h, 0x241);
    }
    NameTableFreeGroup_158ac0(h, 0x242);
    if (insect_InsectBattleTestFlag_50da40(o, 0x4D) == 0) {
        NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x29E);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
        g = GetCharaDataMgr_1fdb70();
        t1 = CharaDataMgrGetMemStack_1ed3f0(g, 1);
        t2 = CharaDataMgrGetMemStack_1ed3f0(g, 2);
        MemStackReset_14d830(t1);
        MemStackReset_14d830(t2);
    }
    insect_InsectBattleClearFlag_50da90(o, 0x4D);
}
