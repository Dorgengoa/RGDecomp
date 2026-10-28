/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndWeaponGaugeUpdateMaybe_4ed890 1
#include "port/game_protos.h"
#line 1
/* === SESSION 97 (2026-09-23): 276 -> MATCH at exact 508 words.  Four edits
 * on the s94 coat (build/wf-normal/s97, bat.py arms p1, e2AB, r2/e2r1, r6/g2):
 *  1. `u8 *off = (u8 *)(idx * 16);` with EL = `*(Elem *)(off + (s32)o->f0EC)`.
 *     On ptr + int mwcc puts the POINTER-typed operand in rs
 *     ([[levers.d/mwcc-commutative-add-operand-order]] rule 2), so this flips
 *     every EL `addu` to retail's `addu rd,$16,f0EC` (274 -> 267).
 *  2. R1 SOLVED: the b0F read AFTER each struct copy is spelled
 *     `((Elem *)(off + (u32)o->f0EC))->b0F`.  The u32 tree is a DIFFERENT
 *     expression, so the o->f0EC load CSEs but the sum is recomputed after the
 *     copy loop -- retail's `addu $2,$16,$7` (+1 word each).  (s32)/(u32)
 *     sums, int+int forms and `(s32)(u8 *)` casts are one object.
 *  3. R2: the bufA block's [2]/[3] through the w/w2 value temps (-2 words),
 *     which the s94 note said would pay once R1 was found: 2 bad.
 *  4. the first block ends in `} else if (EL.f04 > 0.0f) {` instead of its own
 *     `return 0;` -- mwcc threads the shared return-0 join into ONE
 *     predecessor; the early return took it, so the b0F guard stole
 *     `move v0,zero` into a bnel.  `goto done;` and a result variable
 *     spelling are the same object.  Inert on that word: nested ifs, `!(<)`,
 *     `r = 0` placements, 8 pragmas (control armed).
 * Everything below predates this session. */
/* === SESSION 94 (2026-09-23): 447 -> 276 BAD at exact 508 words, and the
 * CALLEE-SAVED MAP IS RETAIL'S (off $16, id2 $17, p $18, RAW idx $19, o $20,
 * v $21).  NOT MERGED.  Three edits (build/wf-normal/s94 k3..k5):
 *  1. bufA/bufB are STRUCT-TYPED LOCALS (`typedef struct S24 { s16 h[2][4]; }`)
 *     assigned directly, `bufA = *(const S24 *)D_00480470;`, accessed
 *     `bufA.h[f][k]`.  The old `*(S8 *)bufA = ...` store went THROUGH A CAST
 *     POINTER, so the copy's stores aliased o->f0EC and we reloaded it after
 *     each copy (s43's "reload NOT reachable from the destination spelling":
 *     all 12 of its arms kept the cast).  -8 words alone.  ⚠ `const` on the
 *     two externs moves them out of gp -- retail addresses them off $28.
 *  2. `#pragma optimization_level 3` above the function (== opt_dead_
 *     assignments off here, one object): on the struct coat it stops the
 *     global propagation of the narrowed idx, so the three q-blocks RE-NARROW
 *     from the raw $19 exactly as retail does (dist 221 -> 137, 510 w).
 *  3. the bufB block's [2]/[3] elements through the `w`/`w2` value temps
 *     (-2 words, exact 508).  The same spelling in the bufA block is ALSO
 *     right locally but costs the alignment (304) until item R1 is found.
 * RESIDUE, three items (s94/k7..k9 are armed nulls on them):
 *  R1. after EACH copy, retail RECOMPUTES `addu $2,$16,$7` (off + f0EC, with
 *      the f0EC LOAD kept in $7 across the copy); we carry the sum itself
 *      (-1 word each).  Byte-identical: a named `Elem *el` re-assigned after
 *      the copy, the `(u8 *)o->f0EC + off` operand order; +1 each:
 *      `o->f0EC[idx].b0F`; +7: `[off / 16]`.  Explicit copy loops over the
 *      unused `s32 i` (h8/h8b/h4x2/rows/count-down, 15 arms) never produce
 *      retail's block-copy loop -- the struct copy is right.
 *  R2. bufA's `&bufA.h[f][2..3]` address CSE (+2), fixed by the value temps
 *      once R1 pays for them.
 *  R3. the entry schedule (id2 is computed AFTER the first EL load in
 *      retail): all six head-statement orders are worse (278-281).
 * Everything below predates this session. */
/* === SESSION 93 ADDENDUM 2 (s93/gh.py): NAMING THE NARROW COSTS THE SEVENTH
 * CALLEE-SAVED REGISTER.  `s32 nx; nx = idx; if (nx < 0) nx = 0;` (a real
 * second def, so the name DOES survive promotion) and its `s32`-parameter twin
 * are ONE OBJECT at 506 w (-2) with SIX registers and map
 * [48,19,39,13,38,5,0] against retail's [29,13,38,7,46,18,5]; `s32 nx = (s16)
 * idx;` alone is 503 w, same shape.  So the seventh register is BOUGHT BY THE
 * NARROW BEING A TEMP, and the index fix and the register count pull opposite
 * ways -- that is the real tension on this unit, and it is a LENGTH+MAP cross
 * ([[levers.d/two-edit-cross-beats-count-ranking]]), not a single edit. */
/* === SESSION 93 ADDENDUM: THE MAP ASK IS NOW EXACT, AND IT IS AN INDEX ASK.
 * s93/hd.py: simplify pass 7 is {32=o, 70=p, 72=(s16)idx, 73=id2, 80=off},
 * removal ASCENDING, so select is [off, id2, narrow, p, o] = $16 $17 $18 $19
 * $20.  Retail is [off, id2, p, idx, o].  s93/pick2.py: giving NODE 72 ANY
 * INDEX BELOW 70 reproduces retail's whole per-register mention pattern (IR
 * totals [28,10,36,6,44,12,3] where base is [28,10,6,36,44,12,3], and retail's
 * reghist minus the same prologue offsets is [26,10,34,5,42,12,3] -- every
 * column within the unit's known 2-word source delta).
 * ==> THE ASK IS NOT "reproduce retail's per-block re-narrow".  It is: THE
 * NARROW MUST BE A NAMED WEB WITH A DECLARED-LOCAL INDEX.  Everything else
 * about this unit's 447 words is downstream of that one node's position.
 * ARMED NULLS on that ask (s93/gf.py, gg.py):
 *   h_ptr / h_ptr_last / h_ptr_rt   `u8 *nx = (u8 *)(s32)idx;` used as
 *       `(s32)nx` everywhere, at two declaration positions, with and without
 *       the round trip            ALL BYTE-IDENTICAL -- the s93 un-promotion
 *       lever does NOT reach a value derived from a PARAMETER (the same bound
 *       00512070 measured)
 *   h_s32   `s32 nx = idx;`                     503 w (-5), the name CSEs more
 *   j_s32 / j_u32  the parameter itself widened  501 w (-7) and only SIX
 *       callee-saved registers -- the narrow's disappearance costs a register,
 *       so node 34 does not simply inherit node 72's role
 *   j_u16   512 w (+4)      j_s32_cast2  (`(s16)idx` kept at off and id2 only)
 *       510 w (+2), SEVEN registers, map [25,21,13,38,48,8,9,5] -- the closest
 *       LENGTH to retail of the four and the natural next cross partner
 * NEXT: a second static def of the narrow is what would name it (that is what
 * `if (n < 0) n = 0;` did on 004fa3c0, +3 words) -- look for one that pays for
 * itself against j_s32's -7. */
/* === SESSION 93 (2026-09-22): STILL 447 BAD at exact 508 words.  THE ROOT
 * CAUSE THIS FILE NAMED IN ITS OWN HEADER IS NOW READ OFF mwcc's ALLOCATOR,
 * and the axis that was expected to move it is a measured null.
 *
 * THE WEBS (build/wf-normal/s93/irf.py on ra/u890.raf.json, class 0):
 *     32 = o      33 = arg1   34 = idx (the RAW parameter)   35 = arg3
 *     70 = p      72 = (s16)idx   73 = id2   80 = off   78 = v
 * Node 34's ONLY appearance after the prologue copy is `c0:72D <- c0:34UL`,
 * a LAST USE: the raw parameter dies at the first narrow, and 72 then lives to
 * the end and is SHIFTED AGAIN at blocks 17, 36 and 45 (the three q-block
 * `o->f0EC[idx]` sites).  Retail keeps the RAW value in $19 and recomputes
 * BOTH the narrow and the shift per block -- so the ask is to stop mwcc CSE-ing
 * `(s16)idx`, not to move any degree.
 * ** THE SAME UNIT ALREADY DOES WHAT RETAIL WANTS, FOR A DIFFERENT VALUE:
 * `s16 v = arg3 * 111` is node 78 and is RE-NARROWED to node 129 at block 12.
 * Whatever distinguishes 78 from 72 is the whole lever; read those two.
 *
 * ARMED NULL (s93/g6.py) -- do not re-run:
 *   y_loc    parameter `s32 idxp` + a NARROW LOCAL `s16 idx;` with
 *            `idx = idxp;` after the p==0 return          BYTE-IDENTICAL
 *   y_loc2   the same assignment BEFORE the func_28FE10 call   509 w (+1)
 *   y_p      `p = (Ent *)func_28FE10(...); p = (Ent *)(s32)p;`
 *            the s93 promotion round trip                 BYTE-IDENTICAL
 *   y_locp   both                                         BYTE-IDENTICAL
 * ==> mwcc normalises the s16-parameter and the s16-local-from-s32-parameter
 * forms onto the SAME IR, and `p`'s web is not reachable by the round trip
 * here (contrast 00502250, where the identical construct on `ctx` was one of
 * the three edits that closed it).
 * Everything below predates this session. */
/* === SESSION 87 (2026-09-22): STILL 447 BAD.  TWO ARMED NULLS.
 *  - s87/e1.py: the whole 68-name boolean `opt_*` table spelled `off` -- this
 *    unit had NO pragma sweep on record at all.  Armed (bogus == base,
 *    opt_unroll_count / full_unroll_limit / unroll_instr_count fail to build).
 *    FIVE live columns and every one is LENGTH-WRONG: common_subs +129 w,
 *    dead_assignments +6, propagation +1, treetransformation and
 *    addtogetherconstantparts -2.  Nothing at 508 words beats base.
 *  - s87/i1.py: the INDEX CAST, which closed 004fb280's root cause A this same
 *    session (`&normal_D_005275A0[(s32)j]`, levers.d/mwcc-index-cast-defeats-cse).
 *    It does NOT transfer: `o->f0EC[(s32)idx]` and `[(s16)idx]` at all 20
 *    sites, with and without matching casts on `off`/`id2`, are
 *    BYTE-IDENTICAL to base; `(u32)` is +8 words and `(u16)` +5, so the deck
 *    fires.  mwcc's CSE of the narrow is not an address CSE.
 * Everything below predates this session. */
/* === SESSION 71 (2026-09-21, SOLO): 456 -> 447.  The two hand-written
 * 8-short copy loops are mwcc's own 16-byte AGGREGATE copies
 * (`bufA = *(const S24 *)D_00480470;`) -- no pointer stores, so
 * o->f0EC is no longer reloaded after them.  K&R `short idx`, `s32 idx` with
 * `(s16)idx` at every use, and the prototype form are ONE object: s69's
 * rematerialisation verdict stands. */
/* === SESSION 69 (2026-09-20, SOLO): STILL 456 BAD / 508 words, no install.
 * !! This unit has ZERO `SESSION N` lines but is NOT unread -- 161 arms are
 * recorded below.  Screening the board by `grep -c "SESSION [0-9]"` puts it at
 * the top of a "never read" ranking, and that ranking is wrong.
 * The header's ONE root cause ("retail keeps RAW idx in $19 and re-narrows
 * (s16)idx at every block; we keep the NARROW alive in $18") is CONFIRMED from
 * the object: retail re-narrows $19 at FOUR sites (0x004ED8E8, 0x004EDB4C,
 * 0x004EDD68, 0x004EDF64) and lets the entry narrow die in a caller-saved $3.
 * NEW MEASUREMENT -- THE INDEX-EXPRESSION AXIS IS A TWO-OBJECT NULL:
 *   `o->f0EC[idx]` at the q-blocks (the park)                  508 w, 456 bad
 *   q-blocks as `(*(Elem *)(idx * 16 + (u8 *)o->f0EC))`        507 w  (-1)
 *   same with the operands swapped; same with `(s16)idx`       507 w, SAME md5
 *   q-blocks through the NAMED `off` (the EL macro)            502 w  (-6)
 *   every site inline with `off` dropped from the macro        502 w  (-6)
 *   the EL macro written base-first instead of off-first       byte-identical
 * ==> all three inline spellings give ONE object, so mwcc CSEs the narrow
 * against the entry one however the address is written, and the header's
 * lever-3 mechanism ("mwcc will not cse against a NAMED USER VARIABLE") does
 * NOT extend to a compiler temp.  The re-narrow is a REMATERIALISATION choice
 * in the allocator, not a spelling.  Sweep: build/wf-normal/s69/p_ed890a.py
 */
#include "types.h"
/* normal 0x004ED890 -- FRESH unit, written from nothing.  lane nf32c, s32.
 * 508 words / 0x7F0 bytes.
 *
 * !! PARKED at RETAIL LENGTH: 508 words = 0x7F0, EXACT.  456 bad.
 * 3 hand round trips + 8 bulk decks = 161 arms (every deck carried an identity
 * arm that reproduced the then-current count).
 *
 * WHAT IS ALREADY SOLVED (do not re-derive):
 *  - the 14 sq/lq the recon flagged are the PROLOGUE, not an aligned(16) local:
 *    retail saves s0-s6 (7 callee-saved) + ra in a 0xA0 frame, two 16-byte s16
 *    locals at sp+0x80 and sp+0x90.  We now emit the same 7 + the same frame.
 *  - the four gp float loads are LITERAL-POOL entries, not externs:
 *      gp-0x7F74 = 0x0047D1FC = 3.1415927f   gp-0x7E14 = 0x0047D35C = 1.9f
 *      gp-0x7868 = 0x0047D908 = -0.05f       gp-0x7864 = 0x0047D90C = 0.9f
 *    Written as literals; nscore reports lit4 ok/4.  1.0f / -1.0f / 60.0f are
 *    lui+mtc1 and must stay literals too.
 *  - D_00480470 / D_00480480 are the two 8-short tables the copy loops read.
 *    They are inside the gp window, so they MUST be declared [4] (8 bytes) or
 *    mwcc drops them out of small data and emits lui/%lo -- see
 *    levers.d/im-gp-array-sdata-threshold.md.  D_005261xx are outside it and
 *    are correctly lui/%lo as incomplete arrays indexed [k * 8].
 *  - callee signatures used: func_28FE10(void*, u16, s32) -> void*,
 *    func_291110(void*, u16, s32, s32), func_2907A0(void*, u16, f32),
 *    func_2905B0(void*, u16, f32 x4), func_2904E0(void*, u16, f32 x5),
 *    f32 func_128FD0(f32).  All consistent with the register set-up.
 *  - p->s04 in the f04 > 0 arm is retail adda.s/madd.s, i.e. the
 *    (a + b) + (c * d) accumulator shape: (0.0f + (f32)s08) + f04 * f00.
 *    The 0.0f is the SAME constant the f04 > 0.0f compare materialises.
 *
 * THE THREE LEVERS THAT PAID (measured):
 *  1. Dropping the `Elem *e` pointer and spelling every access
 *     o->f0EC[idx].X in full: 9 words short -> 5 short.  A live pointer keeps
 *     one addu in a register where retail recomputes it per block.
 *  2. Swapping BOTH `f00 < 1.0f` if/else arms so the `>= 1.0f` arm is INLINE:
 *     retail branch-likelies (bc1tl) into the `< 1.0f` arm.
 *  3. ***  A NAMED `s32 off = (u8 *)(idx * 16);` used through the EL macro in the
 *     OUTER regions ONLY (+4 words), plus spelling the trailing guard's float
 *     read as o->f0EC[idx].f00 while the b0E/b0F reads beside it keep the
 *     macro (+1 word).  That is what buys retail's 7th callee-saved register
 *     and the exact 508.  Mechanism: mwcc will NOT cse a recomputed
 *     expression against a value already stored in a NAMED USER VARIABLE, so
 *     naming the offset splits the web the way retail has it.
 *
 * THE RESIDUE.  The length is right GLOBALLY and wrong LOCALLY -- cancelling
 * intervals, so the byte compare disagrees over whole shifted regions (only 93
 * of the 456 bad words are same-opcode).  Per-region balance, ours vs retail:
 *   0x004ED8F0  -1   retail loads o->f0EC one slot EARLIER
 *   0x004ED904  +3 / 0x004ED910 -2   entry schedule: retail sinks id2 past the lb
 *   0x004ED958  +1   we RELOAD o->f0EC after the block-C copy loop, retail does not
 *   0x004ED9B0  +2   mwcc cse's the ADDRESS &bufA.h[f][2]; a value temp costs 2 more
 *   0x004EDB4C  -2   retail RE-NARROWS (s16)idx inside the q block; we cse it
 *   0x004EDD48  +1   same reload, block G
 *   0x004EDD68  -3 / 0x004EDD88 +3   same re-narrow + the bufB address cse
 *   0x004EDF64  -2   same re-narrow, block E q block
 *   0x004EDCF4   0   retail has bne + nop + a DUPLICATED addu, we have bnel
 * ONE root cause dominates: retail keeps RAW idx in $19 and re-narrows
 * (s16)idx at every block; we keep the NARROW alive in $18, which displaces
 * p to $19 and off into $16's second range.  Retail: $16 off, $17 id2,
 * $18 p, $19 idx.  Ours: $16 idx/off, $17 id2, $18 (s16)idx, $19 p.
 * Kill that one temp and the register map, and probably most of the 456,
 * should fall out.
 *
 * ARMED NULLS -- do not spend another round trip on these:
 *  - copy-destination spelling (s16[2][4] vs flat [8] vs bufA[0] vs an
 *    array-indexed for loop): 12 arms, byte-identical md5.  The reload after
 *    the loop is NOT reachable from the destination spelling.
 *  - inner-block index respellings: `s16 n = idx;` (copy-propagated, identical
 *    md5), `(s16)idx`, byte-offset casts, a block-local `off2 = idx * 16`,
 *    idx as an s16 LOCAL fed from an s32 param: all inert or worse. 14 arms.
 *  - naming the narrow (`s32 j = idx; off = j * 16; id2 = j + 0x39;`) costs an
 *    EIGHTH callee-saved register: 510 words.  7 head statement orders: 0 or +2.
 *  - parameter type sweep (arg1 s32/u16/s16 x arg3 s32/s16) x off spellings
 *    (idx*16, idx<<4, (s32)idx*16, idx*sizeof): 24 arms, nothing under 508.
 *    `sizeof` is UNSIGNED and costs 3 words.
 *  - a `static __inline` helper for the shared q-fill block compiles to the
 *    BYTE-IDENTICAL object -- mwcc inlines and re-cse's it.  Without `inline`
 *    it stays a call and the unit collapses to 42 words.
 *  - pragma sweep (14 names incl. a bogus control): opt_common_subs off is
 *    LIVE but far too coarse (639 words); optimization_level 3 and
 *    opt_dead_assignments off give l1 10 (better than our 16!) at 514 words --
 *    worth a look ONLY if someone finds the 6 words they add.
 *    opt_lifetimes off is a CROSS CANDIDATE: same 508/456, DIFFERENT md5.
 *
 * NOT MERGED.  A non-MATCH is never merged; this draft is here for the next
 * session to start from at zero cost. */

typedef struct Elem {
    f32 f00;
    f32 f04;
    s16 s08;
    s16 s0A;
    s16 s0C;
    s8  b0E;
    s8  b0F;
} Elem;

typedef struct Ent {
    s16 s00;
    s16 s02;
    s16 s04;
    s16 s06;
    s16 s08;
    s16 s0A;
    s16 s0C;
    s16 s0E;
    s16 pad10[8];
    s16 s20;
    s16 s22;
} Ent;

typedef struct Obj {
    u8    pad000[0x14];
    s32   f014;
    u8    pad018[0xEC - 0x18];
    Elem *f0EC;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s16 D_00480470[4];
extern s16 D_00480480[4];
extern s16 normal_D_00526100[];
extern s16 normal_D_00526102[];
extern s16 normal_D_00526104[];
extern s16 normal_D_00526106[];
extern s16 normal_D_00526108[];
extern s16 normal_D_0052610A[];
extern s16 normal_D_0052610C[];
extern s16 normal_D_0052610E[];

#define EL (*(Elem *)(off + (s32)o->f0EC))

typedef struct S8 { s16 h[8]; } S8;
typedef struct S24 { s16 h[2][4]; } S24;

#pragma optimization_level 3
s32 normal_MenuBattleEndWeaponGaugeUpdateMaybe_4ed890(Obj *o, s32 arg1, s16 idx, s32 arg3)
{
    S24   bufA __attribute__((aligned(16)));
    S24   bufB __attribute__((aligned(16)));
    Ent  *p;
    Ent  *q;
    s16  *src;
    s16  *dst;
    s32   i;
    s16   f;
    s16   v;
    s32   id2;
    s16   w;
    s16   w2;
    f32   t;
    u8   *off;

    p = (Ent *)UiGetWidgetSprite_28fe10(&o->f014, arg1, 0);
    if (p == 0) {
        return 1;
    }
    id2 = idx + 0x39;
    v = arg3 * 111;
    off = (u8 *)(idx * 16);
    if (EL.b0E == 2 || EL.b0F == 2) {
        bufA = *(const S24 *)D_00480470;
        f = 0;
        if ((*(Elem *)(off + (u32)o->f0EC)).b0F == 2) {
            f = 1;
        }
        p->s00 = v + (0x28 - f * 4);
        p->s02 = 0x17;
        p->s08 = bufA.h[f][0];
        p->s0A = bufA.h[f][1];
        w = bufA.h[f][2];
        p->s0C = w;
        p->s04 = w;
        w2 = bufA.h[f][3];
        p->s0E = w2;
        p->s06 = w2;
        UiSetWidgetsVisibleById_291110(&o->f014, id2, 0, 1);
    } else if (EL.f04 > 0.0f) {
        p->s00 = v + 0x28;
        p->s02 = 0x1C;
        p->s06 = normal_D_00526106[EL.s0A * 8];
        p->s08 = normal_D_00526100[EL.s0A * 8];
        p->s0A = normal_D_00526102[EL.s0A * 8];
        p->s0C = normal_D_00526104[EL.s0A * 8];
        p->s0E = normal_D_00526106[EL.s0A * 8];
        p->s04 = (s16)(0.0f + (f32)EL.s08
                       + EL.f04 * EL.f00);
        if (p->s04 == 0) {
            p->s0C = 0;
        }
        q = (Ent *)UiGetWidgetSprite_28fe10(&o->f014, id2, 0);
        if (q != 0 && EL.s0A != 0) {
            q->s00 = v + 0x30;
            q->s02 = 2;
            q->s08 = normal_D_00526108[o->f0EC[idx].s0A * 8];
            q->s0A = normal_D_0052610A[o->f0EC[idx].s0A * 8];
            w = normal_D_0052610C[o->f0EC[idx].s0A * 8];
            q->s04 = w;
            q->s0C = w;
            w2 = normal_D_0052610E[o->f0EC[idx].s0A * 8];
            q->s06 = w2;
            q->s0E = w2;
            if (o->f0EC[idx].f00 >= 1.0f) {
                q->s20 = v + 0x44;
                q->s22 = 2;
            } else {
                q->s20 = -1;
            }
            UiSetWidgetAlpha_2907a0(&o->f014, id2, 1.0f);
            if (o->f0EC[idx].f00 >= 1.0f) {
                if (o->f0EC[idx].s0C == 0) {
                    UiSetWidgetColor_2905b0(&o->f014, id2, 1.9f, 1.9f, 1.9f, -1.0f);
                    UiFadeWidgetColor_2904e0(&o->f014, id2, 1.0f, 1.0f, 1.0f, -1.0f,
                                -0.05f);
                }
                o->f0EC[idx].s0C++;
            } else {
                UiSetWidgetColor_2905b0(&o->f014, id2, 1.0f, 1.0f, 1.0f, -1.0f);
            }
        }
        if ((EL.b0E == 1 || EL.b0F == 1)
            && o->f0EC[idx].f00 >= 1.0f) {
            bufB = *(const S24 *)D_00480480;
            f = 0;
            if ((*(Elem *)(off + (u32)o->f0EC)).b0F == 1) {
                f = 1;
            }
            p->s00 = v + (0x28 - f * 4);
            p->s02 = 0x17;
            p->s08 = bufB.h[f][0];
            p->s0A = bufB.h[f][1];
            w = bufB.h[f][2];
            p->s0C = w;
            p->s04 = w;
            w2 = bufB.h[f][3];
            p->s0E = w2;
            p->s06 = w2;
            t = 0.9f + Sinf_128fd0(3.1415927f * (f32)o->f0EC[idx].s0C / 60.0f);
            UiSetWidgetColor_2905b0(&o->f014, arg1, t, t, t, -1.0f);
            o->f0EC[idx].s0C++;
            if (o->f0EC[idx].s0C >= 0x3C) {
                o->f0EC[idx].s0C = 0;
            }
        }
    } else {
        p->s00 = v + 0x28;
        p->s02 = 0x1C;
        p->s06 = normal_D_00526106[EL.s0A * 8];
        p->s08 = normal_D_00526100[EL.s0A * 8];
        p->s0A = normal_D_00526102[EL.s0A * 8];
        p->s0C = normal_D_00526104[EL.s0A * 8];
        p->s0E = normal_D_00526106[EL.s0A * 8];
        p->s04 = EL.s08;
        if (p->s04 == 0) {
            p->s0C = 0;
        }
        q = (Ent *)UiGetWidgetSprite_28fe10(&o->f014, id2, 0);
        if (q != 0 && EL.s0A != 0) {
            q->s00 = v + 0x30;
            q->s02 = 2;
            q->s08 = normal_D_00526108[o->f0EC[idx].s0A * 8];
            q->s0A = normal_D_0052610A[o->f0EC[idx].s0A * 8];
            w = normal_D_0052610C[o->f0EC[idx].s0A * 8];
            q->s04 = w;
            q->s0C = w;
            w2 = normal_D_0052610E[o->f0EC[idx].s0A * 8];
            q->s06 = w2;
            q->s0E = w2;
            q->s20 = -1;
            UiSetWidgetAlpha_2907a0(&o->f014, id2, 1.0f);
            UiSetWidgetColor_2905b0(&o->f014, id2, 1.0f, 1.0f, 1.0f, -1.0f);
        }
    }
    return 0;
}
