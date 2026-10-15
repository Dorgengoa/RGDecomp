/* ★★★★★★★★ SESSION 48 (2026-09-07, SOLO): 10 BAD -> **MATCH**, 787 words /
 * 3,148 bytes -- the largest unit left open on the NORMAL board.  THREE edits,
 * and all three retire claims written in this very header:
 *
 *  1. ★★★★★★★★ `D_0047D360` IS A `.lit4` POOL ENTRY AND MUST BE THE LITERAL
 *     `0.785f`.  The "Relocation notes" below say these addresses "are NOT
 *     .lit4 pool entries here (retail issues lwc1 off $28)" -- ⚠⚠ READING
 *     `lwc1 off $28` IS WHAT A POOL ENTRY LOOKS LIKE.  0x0047D1FC-0x0047D7FF
 *     is mwcc's float literal pool (scripts/t_lit4.py) and it lives in MAIN's
 *     gp window by construction.  As an `extern f32` mwcc PINS the load at its
 *     use; as a literal it is a constant with no alias hazard and HOISTS to
 *     the top of the block -- which is retail's schedule and the whole of
 *     cluster 3.  ([[mwcc-float-literal-pool]]; screen the board with
 *     build/wf-normal/s48/poolscan.py.)  ⚠ Score with nscore.py only.
 *  2. ★ THE IDENTITY-CAST PIN on `&cards[i]`:
 *         { Ent **q = &cards[i]; q = (Ent **)(s32)q; *q = 0; }
 *     Retail materialises BOTH element addresses (`addiu $2,$3,0xC8 / addiu
 *     $19,$3,0xC0`); mwcc folds one into a displacement.  The ~60-arm negative
 *     below includes `Ent **q = &cards[i]; *q = 0;` ("a one-use pointer to a
 *     local array element is ALWAYS folded back") but NOT the cast, which is
 *     the s46 lever [[mwcc-identity-cast-splits-cse]] /
 *     [[mwcc-propagated-temp-colouring]].  ⇒ THE `items[i] = 0;` SCAFFOLD IS
 *     DELETED: the duplicate dead store is gone and the score IMPROVED.
 *  3. The two `o->f2D8[i]` stores stay in the order f000 THEN f004 -- f004 is
 *     the one retail puts in the jal's DELAY SLOT.  ⚠ In the pre-literal coat
 *     the reverse order scored better (7 vs 6); once the lwc1 hoists it is the
 *     last word of the unit.  A cell that wins in the old coat can be the
 *     wrong half in the new one ([[two-edit-cross-beats-count-ranking]]).
 *
 * Sweeps: build/wf-normal/s48/a_efc50{a,b,c,d}.py.
 * ⚠ The `Relocation notes` paragraph below is WRONG about the pool; it is left
 * in place only so the correction above has something to point at. */
/* ★★★★★★★ SESSION 45 (n45a7): 16 bad -> 10, exact 787 words.  ONE EDIT, and
 * it is the transferable one: CLUSTER 1 CLOSED.
 *   retail  lh $3,0x2($16) | lh $2,0x4($16) | sh $3,0x39A($17) | sh $2,0x39C
 *   ours    lh | sh | lh | sh, all through one register
 * The fix is to name each PAIR's two loads in temps before storing them --
 * BUT the temps must REUSE locals that are dead at that point (`idx` and
 * `cnt`), not new ones.  That is why this unit's own note "naming the loaded
 * halfwords in 2 or 4 s16 temps (3 spellings, all WORSE)" was wrong: a new
 * declaration pays for itself in the frame and the colouring, a reused dead
 * one does not.  Same fact closed normal_BtlChgPageWeaponGridScrollRow_504410 this session.
 *   ⚠ ALL SIX choices of the two reused locals ({idx,cnt},{cnt,idx},{idx,id},
 *   {n,lim},{lim,n},{i,n}) are ONE OBJECT -- the pairing is inert, only the
 *   REUSE matters.  FOUR distinct temps is 16 (no gain); FIVE (all loads
 *   hoisted) is 18; a 32-bit pair copy is 18.
 *
 * ⚠⚠ THE `items[i] = 0;` DUPLICATE ON LINE ~584 IS STILL A SCAFFOLD.  It is a
 * dead store, it is NOT what retail's source said, and it exists only to buy
 * the cluster-2 word.  Deleting it is -1 word (measured again this session).
 *
 * CLUSTER 2 (2 w) and CLUSTER 3 (7 w) were BOTH re-decked at the new 10-bad
 * base -- s28's rule that a moved base invalidates every old deck -- and both
 * are still null:
 *  - cluster 3: all six pair-preserving orderings of the four stores (14-17)
 *    and five positions of a named `f32 fv` (10 at best, i.e. the baseline
 *    object; positions 3 and 4 are LENGTH-WRONG).
 *  - cluster 2: removing the scaffold, `Ent **pc = &cards[i]` with 1 or 3
 *    derefs, naming `pt` as well, swapping the two stores, `cards[i] = 0;`
 *    twice instead, and `(u32)` on one or both indices -- every cell is
 *    LENGTH-WRONG (-1 to -3, or +1 with a 128-substitution renumber).
 */
#include "types.h"
/* normal 0x004EFC50 -- the two-slot compare/equip panel builder.  788
 * instructions, 3,152 bytes, 27 distinct callees, 3 virtual calls.
 *
 * FRESH unit, written from the listing in s32 (lane nf32f).
 *
 * Relocation notes:
 *  - _gp = 0x00485170.  D_00484410 (gp-0xD60), D_0047D278 (gp-0x7EF8),
 *    D_0047D288 (gp-0x7EE8), D_0047D34C (gp-0x7E24), D_0047D35C (gp-0x7E14),
 *    D_0047D360 (gp-0x7E10) and D_0047D1E8 (gp-0x7F88) are all INSIDE the gp
 *    window, so they stay plain externs and take %gp_rel -- they are NOT
 *    .lit4 pool entries here (retail issues lwc1 off $28).
 *  - D_005262C8 / D_005262D0 are OVERLAY rodata far outside the window;
 *    declared as incomplete s16 arrays so they take %hi/%lo.
 *
 * The three jalr $25 are C++ virtuals on two different objects; vptr is at
 * offset 0 and slot = 8 + 4*N, so 0x50 -> 18, 0xC0 -> 46, 0x4C8 -> 304.  One
 * class carries all three -- no vtable is emitted because nothing is
 * constructed here. */

/* s32 lane nf32f -- PARKED at 787/787 words (EXACT LENGTH) and 16 bad words.
 * ~1,050 bulk arms over 12 decks.  The three surviving clusters, in order of
 * size:
 *
 *  1. 0x004EFD10-0x004EFD28 (6 w).  The rq -> o field copy.  Retail issues
 *     lh(0x2) lh(0x4) sh(0x39A) sh(0x39C) -- BOTH LOADS BEFORE BOTH STORES,
 *     in two registers.  We issue lh sh lh sh in one.  Armed nulls here:
 *     naming the loaded halfwords in 2 or 4 s16 temps (3 spellings, all
 *     WORSE), and `const Req *rq` (INERT -- identical md5 to non-const, so
 *     it is not a type-based-alias problem).
 *
 *  2. 0x004EFDF0-0x004EFDFC (3 w) + the SCAFFOLD.  Retail's loop-1 head
 *     MATERIALISES BOTH element addresses:
 *         addiu $2,$3,0xC8 / addiu $19,$3,0xC0 / sw $0,0($2) / sw $0,0($19)
 *     We only ever get ONE of the two -- mwcc folds the other into a
 *     displacement (`sw $0,0xC8($3)`).  This is the LAST length word, and the
 *     `items[i] = 0;` is written TWICE below purely as a SCAFFOLD to buy it:
 *     the duplicate is a dead store, it is NOT what retail's source said, and
 *     the next session should delete it the moment the real lever is found.
 *     Armed nulls for the real lever (about 60 arms): a one-member WRAPPER
 *     STRUCT around each array (24 arms, byte-identical to no wrapper -- mwcc
 *     normalises it away), `*(Ent **)((u8 *)cards + i*4)`, `((Ent **)cards)[i]`,
 *     `*(Ent *volatile *)&cards[i]`, `*(cards + i)`, `(Ent *)0`, and
 *     `Ent **q = &cards[i]; *q = 0;` (a one-use pointer to a local array
 *     element is ALWAYS folded back).  Both store orders were swept.
 *
 *  3. 0x004F0140-0x004F015C (7 w).  The 0x74 handle loop.  Retail HOISTS
 *     `lwc1 $f0, -0x7E10($28)` to the top of the block; we sink it below the
 *     two `sh 0x22` stores.  Armed nulls: `f32 fv = D_0047D360;` named first
 *     (2 spellings), a `Slot *sl = &o->f2D8[i];` row pointer, and all four
 *     orderings of the two tt-> stores against the two f2D8 stores -- every
 *     one reads 21 bad against this 16.
 *
 * What DID pay, in case a sibling unit wants it:
 *  - all three 3-way dispatches are IF/ELSE-IF chains, not switches (a switch
 *    gives `beql INTO the arm`, retail has `bnel PAST an INLINE arm`);
 *  - `cnt++` / `id++`, never `cnt = cnt + 1` (an s16 costs 5 w that way, 3 as
 *    ++; a u16 costs 3 vs 2);
 *  - NAMING the second call's result (`lim = normal_FieldHudPartyRowCount_4f9c50(o)`) is what
 *    creates retail's SECOND dsll32/dsra32 pair on `idx`; eight spellings of
 *    the func_3C3070 side are one object;
 *  - `Ent *c = func_3C8370(..); cards[(u32)i] = c; if (cards[(u32)i] == 0)`
 *    -- the (u32) index cast breaks the address CSE across the call, and
 *    re-reading the array (rather than testing `c`) buys the materialised
 *    store address;
 *  - `Ent **pc = &cards[k];` with TWO derefs in the k-loop case 0, and
 *    `Item **pt = &items[k]; it = *pt; ... (*pt)->f000 ...` in case 1;
 *  - `Ent *cards[2]` is declared BEFORE `Item *items[2]`: the FIRST-declared
 *    local takes the HIGHER frame offset (cards 0xC8, items 0xC0). */

typedef struct CardInfo {
    s16 f000;
    u8  pad002[0xA];
    s32 f00C;
} CardInfo;

struct Ent {
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void v011();
    virtual void v012();
    virtual void v013();
    virtual void v014();
    virtual void v015();
    virtual void v016();
    virtual void v017();
    virtual s32  v018();
    virtual void v019();
    virtual void v020();
    virtual void v021();
    virtual void v022();
    virtual void v023();
    virtual void v024();
    virtual void v025();
    virtual void v026();
    virtual void v027();
    virtual void v028();
    virtual void v029();
    virtual void v030();
    virtual void v031();
    virtual void v032();
    virtual void v033();
    virtual void v034();
    virtual void v035();
    virtual void v036();
    virtual void v037();
    virtual void v038();
    virtual void v039();
    virtual void v040();
    virtual void v041();
    virtual void v042();
    virtual void v043();
    virtual void v044();
    virtual void v045();
    virtual s32  v046();
    virtual void v047();
    virtual void v048();
    virtual void v049();
    virtual void v050();
    virtual void v051();
    virtual void v052();
    virtual void v053();
    virtual void v054();
    virtual void v055();
    virtual void v056();
    virtual void v057();
    virtual void v058();
    virtual void v059();
    virtual void v060();
    virtual void v061();
    virtual void v062();
    virtual void v063();
    virtual void v064();
    virtual void v065();
    virtual void v066();
    virtual void v067();
    virtual void v068();
    virtual void v069();
    virtual void v070();
    virtual void v071();
    virtual void v072();
    virtual void v073();
    virtual void v074();
    virtual void v075();
    virtual void v076();
    virtual void v077();
    virtual void v078();
    virtual void v079();
    virtual void v080();
    virtual void v081();
    virtual void v082();
    virtual void v083();
    virtual void v084();
    virtual void v085();
    virtual void v086();
    virtual void v087();
    virtual void v088();
    virtual void v089();
    virtual void v090();
    virtual void v091();
    virtual void v092();
    virtual void v093();
    virtual void v094();
    virtual void v095();
    virtual void v096();
    virtual void v097();
    virtual void v098();
    virtual void v099();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual void v110();
    virtual void v111();
    virtual void v112();
    virtual void v113();
    virtual void v114();
    virtual void v115();
    virtual void v116();
    virtual void v117();
    virtual void v118();
    virtual void v119();
    virtual void v120();
    virtual void v121();
    virtual void v122();
    virtual void v123();
    virtual void v124();
    virtual void v125();
    virtual void v126();
    virtual void v127();
    virtual void v128();
    virtual void v129();
    virtual void v130();
    virtual void v131();
    virtual void v132();
    virtual void v133();
    virtual void v134();
    virtual void v135();
    virtual void v136();
    virtual void v137();
    virtual void v138();
    virtual void v139();
    virtual void v140();
    virtual void v141();
    virtual void v142();
    virtual void v143();
    virtual void v144();
    virtual void v145();
    virtual void v146();
    virtual void v147();
    virtual void v148();
    virtual void v149();
    virtual void v150();
    virtual void v151();
    virtual void v152();
    virtual void v153();
    virtual void v154();
    virtual void v155();
    virtual void v156();
    virtual void v157();
    virtual void v158();
    virtual void v159();
    virtual void v160();
    virtual void v161();
    virtual void v162();
    virtual void v163();
    virtual void v164();
    virtual void v165();
    virtual void v166();
    virtual void v167();
    virtual void v168();
    virtual void v169();
    virtual void v170();
    virtual void v171();
    virtual void v172();
    virtual void v173();
    virtual void v174();
    virtual void v175();
    virtual void v176();
    virtual void v177();
    virtual void v178();
    virtual void v179();
    virtual void v180();
    virtual void v181();
    virtual void v182();
    virtual void v183();
    virtual void v184();
    virtual void v185();
    virtual void v186();
    virtual void v187();
    virtual void v188();
    virtual void v189();
    virtual void v190();
    virtual void v191();
    virtual void v192();
    virtual void v193();
    virtual void v194();
    virtual void v195();
    virtual void v196();
    virtual void v197();
    virtual void v198();
    virtual void v199();
    virtual void v200();
    virtual void v201();
    virtual void v202();
    virtual void v203();
    virtual void v204();
    virtual void v205();
    virtual void v206();
    virtual void v207();
    virtual void v208();
    virtual void v209();
    virtual void v210();
    virtual void v211();
    virtual void v212();
    virtual void v213();
    virtual void v214();
    virtual void v215();
    virtual void v216();
    virtual void v217();
    virtual void v218();
    virtual void v219();
    virtual void v220();
    virtual void v221();
    virtual void v222();
    virtual void v223();
    virtual void v224();
    virtual void v225();
    virtual void v226();
    virtual void v227();
    virtual void v228();
    virtual void v229();
    virtual void v230();
    virtual void v231();
    virtual void v232();
    virtual void v233();
    virtual void v234();
    virtual void v235();
    virtual void v236();
    virtual void v237();
    virtual void v238();
    virtual void v239();
    virtual void v240();
    virtual void v241();
    virtual void v242();
    virtual void v243();
    virtual void v244();
    virtual void v245();
    virtual void v246();
    virtual void v247();
    virtual void v248();
    virtual void v249();
    virtual void v250();
    virtual void v251();
    virtual void v252();
    virtual void v253();
    virtual void v254();
    virtual void v255();
    virtual void v256();
    virtual void v257();
    virtual void v258();
    virtual void v259();
    virtual void v260();
    virtual void v261();
    virtual void v262();
    virtual void v263();
    virtual void v264();
    virtual void v265();
    virtual void v266();
    virtual void v267();
    virtual void v268();
    virtual void v269();
    virtual void v270();
    virtual void v271();
    virtual void v272();
    virtual void v273();
    virtual void v274();
    virtual void v275();
    virtual void v276();
    virtual void v277();
    virtual void v278();
    virtual void v279();
    virtual void v280();
    virtual void v281();
    virtual void v282();
    virtual void v283();
    virtual void v284();
    virtual void v285();
    virtual void v286();
    virtual void v287();
    virtual void v288();
    virtual void v289();
    virtual void v290();
    virtual void v291();
    virtual void v292();
    virtual void v293();
    virtual void v294();
    virtual void v295();
    virtual void v296();
    virtual void v297();
    virtual void v298();
    virtual void v299();
    virtual void v300();
    virtual void v301();
    virtual void v302();
    virtual void v303();
    virtual s32  v304();
    u8        pad004[0xC];
    CardInfo *f010;
};

typedef struct Slot {
    f32 f000;
    s16 f004;
    u8  pad006[2];
} Slot;

typedef struct Scene {
    u8   pad000[0x2D8];
    Slot f2D8[5];
    u8   pad300[0x378 - 0x300];
    s16  f378;
    u8   pad37A[0x398 - 0x37A];
    s16  f398;
    s16  f39A[2];
    s16  f39E[2];
    s16  f3A2;
    s16  f3A4;
    s16  f3A6;
    s16  f3A8;
    s16  f3AA;
    s16  f3AC;
    u8   f3AE;
} Scene;

typedef struct Req {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
    s16 f008;
} Req;

typedef struct Ctx {
    u8    pad000[0x18];
    void *f018;
} Ctx;

typedef struct Item {
    s16 f000;
    u8  pad002[6];
    s32 f008;
} Item;

typedef struct Txt {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
    s16 f008;
    s16 f00A;
    s16 f00C;
    s16 f00E;
} Txt;

typedef struct Icon {
    s16 f000;
    s16 f002;
    u8  pad004[4];
    s64 f008;
    s16 f010;
    u8  pad012[0xE];
    s16 f020;
    s16 f022;
    u8  pad024[4];
    s64 f028;
    s16 f030;
} Icon;

typedef struct Tint {
    u8  pad000[4];
    s32 f004;
    u8  pad008[4];
    u32 f00C;
} Tint;

typedef struct Handle {
    u8    pad000[0x20];
    Txt  *f020;
    Icon *f024;
    Tint *f028;
} Handle;

extern "C" s16   D_005262C8[];
extern "C" s16   D_005262D0[];
extern "C" void *D_00484410;
extern "C" f32   D_0047D1E8;
extern "C" f32   D_0047D278;
extern "C" f32   D_0047D288;
extern "C" f32   D_0047D34C;
extern "C" f32   D_0047D35C;
extern "C" f32   D_0047D360;

extern "C" s32   normal_BtlChgMenuGetPhase_4f9d40(void);
extern "C" s32   normal_FieldHudPartyRowCount_4f9c50(Scene *o);
extern "C" void  normal_FieldHudAllySuggestRefreshMaybe_4efb10(Scene *o, s32 id);
extern "C" s32   func_1F59C0(void);
extern "C" Ctx  *func_1FEDE0(void);
extern "C" s32   func_1FEDF0(void);
extern "C" s32   func_3C3070(void *w, s16 key);
extern "C" Ent  *func_3C2420(void *w, s32 i);
extern "C" Ent  *func_3C8370(void *w, s32 id, s32 c, s32 d, s32 e, s32 f);
extern "C" Item *func_3ADA90(Ent *o, s32 id, s32 c);
extern "C" Item *func_3AD940(Ent *o, s32 id, s32 c);
extern "C" void  func_1B9520(void *p, s32 a, s32 b, f32 v);
extern "C" void  func_3E0A20(s32 a);
extern "C" void  func_290010(void *w, s32 id, s32 a, s32 b);
extern "C" void  func_291110(void *w, u16 id, s32 c, s32 d);
extern "C" void  func_2905B0(void *w, u16 id, f32 a, f32 b, f32 c, f32 d);
extern "C" void  func_290F60(void *w, u16 id, s32 x, s32 y);
extern "C" void  func_290F50(void *w, u16 id, s32 c, s32 d, s32 e, f32 x);
extern "C" void  func_2904E0(void *w, u16 id, f32 a, f32 b, f32 c, f32 d, f32 e);
extern "C" void  func_2907A0(void *w, u16 id, f32 x);
extern "C" Handle *func_290460(Scene *w, u16 id);
extern "C" void *func_206A40(void);
extern "C" Txt  *func_42C3A0(void *o, s32 id);
extern "C" s32   func_3C78D0(void *w, s32 id, s32 c, s32 d);
extern "C" s32   func_3AD390(Ent *o, s16 k);
extern "C" s32   func_3A05C0(s32 h);
extern "C" s32   func_3F5CA0(Item *p);

extern "C" s32 normal_FieldHudAllySuggestOpen_4efc50(Scene *o, Req *rq);

s32 normal_FieldHudAllySuggestOpen_4efc50(Scene *o, Req *rq)
{
    Ent  *cards[2];
    Item *items[2];
    Ctx  *ctx;
    Ent  *ent;
    Handle *h;
    Txt  *tt;
    Icon *ic;
    Tint *tn;
    void *w;
    Item *it;
    s32   lim;
    s16   idx;
    s16   cnt;
    u16   id;
    s32   i;
    s32   n;

    if (o->f3AC != 0) {
        return 1;
    }
    if (o->f3A2 != 0) {
        return 1;
    }
    if (rq == 0) {
        return 2;
    }
    if (o->f378 == 0) {
        return 0x19;
    }
    if (normal_BtlChgMenuGetPhase_4f9d40() != 0) {
        return 0x1C;
    }
    if (func_1F59C0() == 0xB) {
        return 0x1E;
    }
    if (o->f3AE == 0) {
        return 0x1F;
    }
    o->f398 = rq->f000;
    idx = rq->f002;
    cnt = rq->f004;
    o->f39A[0] = idx;
    o->f39A[1] = cnt;
    idx = rq->f006;
    cnt = rq->f008;
    o->f39E[0] = idx;
    o->f39E[1] = cnt;
    ctx = func_1FEDE0();
    if (ctx == 0) {
        return 3;
    }
    if (func_1FEDF0() == 0) {
        return 3;
    }
    if (o->f398 < 0) {
        return 4;
    }
    idx = func_3C3070(ctx->f018, o->f398);
    lim = normal_FieldHudPartyRowCount_4f9c50(o);
    if (idx >= lim) {
        return 5;
    }
    ent = func_3C2420(ctx->f018, idx);
    if (ent == 0) {
        return 6;
    }
    if (ent->v046() != 0) {
        return 6;
    }
    cnt = 0;
    for (i = 0; i < 2; i++) {
        {
            Ent **q = &cards[i];
            q = (Ent **)(s32)q;
            *q = 0;
        }
        items[i] = 0;
        if (o->f39A[i] == 0) {
            Ent *c = func_3C8370(ctx->f018, o->f39E[i], 0, -1, 0, 0);

            cards[(u32)i] = c;
            if (cards[(u32)i] == 0) {
                o->f39E[i] = -1;
            }
        } else if (o->f39A[i] == 1) {
            items[i] = func_3ADA90(ent, o->f39E[i], 0);
            if (items[i] == 0) {
                o->f39E[i] = -1;
            }
        } else if (o->f39A[i] == 2) {
            items[i] = func_3AD940(ent, 0x86, 0);
            if (ent->v304() == 0) {
                items[i] = 0;
            }
            if (items[i] == 0) {
                o->f39E[i] = -1;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        if (o->f39E[i] != -1 && o->f39A[i] != -1) {
            cnt++;
        }
    }
    if (cnt == 0) {
        return 7;
    }
    if (cnt == 1) {
        if (o->f39E[0] == -1) {
            o->f39A[0] = o->f39A[1];
            items[0] = items[1];
            o->f39A[1] = -1;
            cards[0] = cards[1];
            items[1] = 0;
            o->f39E[0] = o->f39E[1];
            cards[1] = 0;
            o->f39E[1] = -1;
        }
    }
    func_1B9520(D_00484410, 0x1B, 0, 1.0f);
    func_3E0A20(o->f398);
    func_290010(o, 0x5F, 1, -1);
    func_291110(o, 0x6B, 0, 1);
    func_2905B0(o, 0x6F, 1.0f, 1.0f, 1.0f, -1.0f);
    func_2905B0(o, 0x70, 1.0f, 1.0f, 1.0f, -1.0f);
    func_2905B0(o, 0x68, 1.0f, 1.0f, 1.0f, -1.0f);
    o->f3A2 = 1;
    o->f3A4 = 0;
    o->f3A8 = -1;
    o->f3AA = 0;
    o->f3A6 = cnt;
    func_290F60(o, 0x60, 0x26, 0x17C);
    func_290F50(o, 0x60, 0x26, 0x12C, 0, D_0047D278);
    func_2905B0(o, 0x60, D_0047D34C, D_0047D34C, D_0047D34C, 0.0f);
    func_2904E0(o, 0x60, D_0047D35C, D_0047D35C, D_0047D35C, 1.0f, D_0047D1E8);
    func_2907A0(o, 0x65, 0.0f);
    h = func_290460(o, 0x63);
    if (h == 0) {
        return 0xC;
    }
    tt = h->f020;
    if (tt == 0) {
        return 0xD;
    }
    tt->f008 = 0x78;
    func_2907A0(o, 0x64, 0.0f);
    id = 0x74;
    for (i = 0; i < 5; i++) {
        h = func_290460(o, id);
        if (h != 0) {
            tt = h->f020;
            if (tt != 0) {
                tt->f004 = 0x22;
                tt->f006 = 0x22;
                o->f2D8[i].f000 = 0.785f;
                o->f2D8[i].f004 = 0;
                func_291110(o, id, 0, 1);
                id++;
            }
        }
    }
    w = func_206A40();
    if (cnt == 2) {
        u16 id2;
        s32 k;

        func_290F60(o, 0x66, 0xFE, 0x117);
        func_2907A0(o, 0x66, D_0047D288);
        func_290F60(o, 0x68, 0x157, 0x10A);
        func_290F60(o, 0x69, 0x129, 0x119);
        func_290F60(o, 0x67, 0x102, 0x119);
        h = func_290460(o, 0x6A);
        h->f020 = func_42C3A0(w, 0x4F42);
        func_290F60(o, 0x6A, 0x59, 0x12B);
        func_2907A0(o, 0x6A, D_0047D288);
        func_290F60(o, 0x6F, 0x68, 0x12F);
        func_290F60(o, 0x70, 0x68, 0x14A);
        func_291110(o, 0x70, 1, 1);
        func_291110(o, 0x72, 1, 1);
        func_290F60(o, 0x6E, D_005262C8[idx], 0x33);
        id2 = 0x71;
        for (k = 0; k < cnt; k++) {
            h = func_290460(o, id2);
            if (h != 0) {
                tn = h->f028;
                if (tn != 0) {
                    tt = h->f020;
                    if (tt != 0) {
                        ic = h->f024;
                        if (ic != 0) {
                            func_290F60(o, id2, 0x8C, D_005262D0[k]);
                            if (o->f39A[k] == 0) {
                                Ent **pc = &cards[k];

                                tn->f004 = (*pc)->f010->f00C;
                                tn->f00C = 0xFF404040;
                                ic->f000 = 0xDC;
                                ic->f002 = 8 - k;
                                ic->f010 = 2;
                                ic->f008 = 1;
                                ic->f020 = 0xE3;
                                ic->f022 = 0xA - k;
                                ic->f030 = 2;
                                n = func_3C78D0(ctx->f018, (*pc)->f010->f000, 0, 0);
                                if (n >= 0x63) {
                                    n = 0x63;
                                }
                                ic->f028 = n;
                                tt->f000 = 0xDC;
                                tt->f002 = 9 - k;
                                tt->f008 = 0x64;
                                tt->f00A = 0x62;
                                tt->f00C = 8;
                                tt->f004 = 8;
                                tt->f00E = 0xC;
                                tt->f006 = 0xC;
                            } else if (o->f39A[k] == 1) {
                                Item **pt = &items[k];

                                it = *pt;
                                tn->f004 = it->f008;
                                tn->f00C = 0xFF404040;
                                ic->f000 = 0xEB;
                                ic->f002 = 8 - k;
                                ic->f010 = 3;
                                n = func_3AD390(ent, (*pt)->f000);
                                if (n != 0) {
                                    ic->f008 = func_3A05C0(n);
                                } else {
                                    ic->f008 = func_3F5CA0(it);
                                }
                                ic->f020 = -1;
                                tt->f000 = 0xBB;
                                tt->f002 = 9 - k;
                                tt->f008 = 0xD8;
                                tt->f00A = 0xC4;
                                tt->f00C = 0x14;
                                tt->f004 = 0x14;
                                tt->f00E = 0xE;
                                tt->f006 = 0xE;
                            } else if (o->f39A[k] == 2) {
                                tn->f004 = items[k]->f008;
                                tn->f00C = 0xFF404040;
                                ic->f000 = -1;
                                ic->f020 = -1;
                                tt->f000 = -1;
                            } else {
                                continue;
                            }
                            id2++;
                        }
                    }
                }
            }
        }
    } else {
        func_290F60(o, 0x66, 0xFE, 0x12C);
        func_2907A0(o, 0x66, D_0047D288);
        func_290F60(o, 0x68, 0x157, 0x11F);
        func_290F60(o, 0x69, 0x129, 0x12E);
        func_290F60(o, 0x67, 0x102, 0x12E);
        h = func_290460(o, 0x6A);
        h->f020 = func_42C3A0(w, 0x4F43);
        func_290F60(o, 0x6A, 0x59, 0x140);
        func_2907A0(o, 0x6A, D_0047D288);
        func_2907A0(o, 0x6C, 1.0f);
        func_2907A0(o, 0x6D, 1.0f);
        func_290F60(o, 0x6F, 0x68, 0x144);
        func_291110(o, 0x70, 0, 1);
        func_291110(o, 0x72, 0, 1);
        func_290F60(o, 0x6E, D_005262C8[idx], 0x19);
        h = func_290460(o, 0x71);
        if (h == 0) {
            return 8;
        }
        tn = h->f028;
        if (tn == 0) {
            return 9;
        }
        tt = h->f020;
        if (tt == 0) {
            return 0xA;
        }
        ic = h->f024;
        if (ic == 0) {
            return 0xB;
        }
        func_290F60(o, 0x71, 0x8C, 0x144);
        if (o->f39A[0] == 0) {
            tn->f004 = cards[0]->f010->f00C;
            tn->f00C = 0xFF404040;
            ic->f000 = 0xCC;
            ic->f002 = 8;
            ic->f010 = 2;
            ic->f008 = 1;
            ic->f020 = 0xE3;
            ic->f022 = 0xA;
            ic->f030 = 2;
            ic->f028 = cards[0]->v018();
            tt->f000 = 0xDC;
            tt->f002 = 9;
            tt->f008 = 0x64;
            tt->f00A = 0x62;
            tt->f00C = 8;
            tt->f004 = 8;
            tt->f00E = 0xC;
            tt->f006 = 0xC;
        } else if (o->f39A[0] == 1) {
            tn->f004 = items[0]->f008;
            tn->f00C = 0xFF404040;
            ic->f000 = 0xEB;
            ic->f002 = 8;
            ic->f010 = 3;
            n = func_3AD390(ent, items[0]->f000);
            if (n != 0) {
                ic->f008 = func_3A05C0(n);
            } else {
                ic->f008 = func_3F5CA0(items[0]);
            }
            ic->f020 = -1;
            tt->f000 = 0xBB;
            tt->f002 = 9;
            tt->f008 = 0xD8;
            tt->f00A = 0xC4;
            tt->f00C = 0x14;
            tt->f004 = 0x14;
            tt->f00E = 0xE;
            tt->f006 = 0xE;
        } else if (o->f39A[0] == 2) {
            tn->f004 = items[0]->f008;
            tn->f00C = 0xFF404040;
            ic->f000 = -1;
            ic->f020 = -1;
            tt->f000 = -1;
        }
    }
    normal_FieldHudAllySuggestRefreshMaybe_4efb10(o, o->f398);
    return 0;
}
