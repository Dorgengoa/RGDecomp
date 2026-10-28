/* rgp:protos */
#line 1
/* === SESSION 98 (2026-09-23): MATCH (122 w, 0 bad; open since s32).
 * Three edits on top of s97's g001 control flow (`if (q == 0) goto done;`):
 *  1. THE DEAD `$19` HOME AND THE 1.0f `$f20` WEB ARE ONE CONSTRUCT:
 *         one = 1.0f;  if (b) { one = 1.0f; }      (after `id = ...`)
 *     `if (b)` survives to the allocator, so b is live across every call ->
 *     $19, homed at entry; the redundant def empties the branch and the empty
 *     branch is deleted AFTER RA -- b is never read.  The two-def `one` is a
 *     web the front end cannot propagate -> $f20 across calls.  Ternary and
 *     if/else forms fold early (s98/a4).  121 -> 122 w, 19 bad.
 *  2. `sel` declared before `i`: retail's $18/$17 map.  19 -> 3 bad (a5).
 *  3. `#pragma opt_dead_assignments off` (s98/a31, the ix52 table re-run on
 *     THIS body; s97 ran it on the 121 w body, where it was inert): call 2's
 *     `mtc1 $f15` now issues after `move a0; move a1` like retail.  3 -> 0.
 * Instruments: s96/sch2.py trace + s98/perm.py / pred.py / ev.py (IR-order
 * replay through s96/sim.py) located the residue to ONE list-order pick.
 */
/* === SESSION 97 (2026-09-23): STILL 121 vs 122.  THREE PARTIAL LEVERS, each
 * reproducing one piece of retail; arms in build/wf-normal/s97/f2..f14
 * (s97/batx.py = bat.py for .cpp arms, `@listfile` for big decks).
 *  1. CONTROL FLOW (f2/g001.cpp, 120 w): `if (q == 0) goto done;` + `done:`
 *     before the final return.  Retail threads the shared return-0 join into
 *     the q==0 guard (`beql $17,$0; daddu $2`) and leaves `bne $20,$18; nop`
 *     at a==sel -- g001 reproduces both.  The other 7 goto/return combos and
 *     the nested form are 118-120 w.
 *  2. THE DEAD $19 HOME IS A COALESCED COPY (f9/l_ne.cpp, 126 w): `x = b;`
 *     before the first call + `for (i = 0; i < n || x != b; i++)` gives
 *     RETAIL'S WHOLE PROLOGUE incl. `daddu $19,$5,$0` and retail's exact
 *     callee-saved map (b $19, a $20, c $16, n $21, sel $18, i $17): the
 *     allocator coalesces x into b.  Left over: `bne s3,s3; nop` (+2).  Only
 *     a LOOP-CONDITION compare survives to the allocator -- every x/b use
 *     outside the loop condition, every copy cycle, arithmetic (x-b, x^b)
 *     and branch-to-fallthrough form is folded first (f7-f11, ~60 arms);
 *     relational forms survive but never fold after colouring.
 *  3. THE 1.0f WEB (f13/pun_p.cpp, 120 w, dist 100 -> 78): `ob = 0x3F800000;
 *     one = *(f32 *)&ob;` makes 1.0f a real web in $f20 like retail, but
 *     through a stack slot (sw/lwc1) instead of lui/mtc1.  (f32)1.0,
 *     (f32)1, int->float, f64 local, union pun: no.
 * Inert on g001: `register` (params and locals), multi-def float reuse,
 * inline helpers, local aggregates/objects with dtors, empty asm, the whole
 * ix52 pragma table off+on on both coats (live near length: peephole off 122
 * and dividefix off on l_ne 122 -- both coincidental, measured).
 * Unique in the corpus: no other matched listing homes an unread argument
 * (s97/deadhome.py, deadsave.py).
 * Everything below predates this session. */
/* === SESSION 93 (2026-09-22): STILL 121 vs 122, ONE WORD SHORT.  The s93
 * PROMOTION lever does NOT resurrect the dead parameter home either.
 * s73 proved `s32 bb = b;` is killed by the FRONT END and that none of the 68
 * opt_* passes keeps it.  s93 adds the INTEGER->POINTER cast, which is the one
 * def shape the propagator will not fold ([[levers.d/mwcc-propagated-temp-
 * colouring]]; it is what closed 004fa3c0 and 00502250 this session).
 * Deck build/wf-normal/s93/g9.py, 6 arms, EVERY ONE BYTE-IDENTICAL (675ace8a):
 *     u8 *bb;  bb = (u8 *)b;                        (before and after the
 *     u8 *bb;  bb = (u8 *)b; bb = (u8 *)(s32)bb;     first call)
 *     void *bb = (void *)b;    s32 bb = b;  (s73's control, re-confirmed)
 *     the same with a READ at the tail (`return (s32)bb & 0;`) -- NOT ARMED,
 *     the read folds to 0, so that cell measures nothing.
 * ==> a def whose RESULT IS NEVER READ is deleted before the allocator sees
 * it, whatever its type.  This agrees with [[levers.d/mwcc-named-local-dead-
 * assignment]]'s own warning ("it does NOT resurrect a DEAD seed") and closes
 * the type axis on this unit for good: the sixth callee-saved register cannot
 * come from spelling `b`.
 * Everything below predates this session. */
/* === SESSION 73 (2026-09-21, SOLO): STILL 121 vs 122, ONE WORD SHORT.  THREE
 * NEW AXES, ALL ARMED NULLS -- the s72 named-local x `opt_dead_assignments off`
 * cross ([[levers.d/mwcc-named-local-dead-assignment]]) DOES NOT REACH THIS
 * UNIT.  Sweeps build/wf-normal/s73/a1.py, a3.py, a5.py, a6.py.
 *  - `s32 bb = b;` (decl-init / separate store / before or after the first
 *    call) x {base, dassign, dassign+prop, dassign+dead_code}: 24 cells, and
 *    the object depends ONLY on the pragma column -- every source shape is
 *    byte-identical within a column.  â‡’ the copy is killed by the FRONT END.
 *  - â˜… CONFIRMED BY THE WHOLE 68-NAME `opt_*` TABLE on the `s32 bb = b;`
 *    source: ONE live cell (`opt_common_subs` +4 w), 64 byte-identical.
 *    ARMED: bogus name == base, opt_unroll_count / opt_full_unroll_limit /
 *    opt_unroll_instr_count fail to build.  NO OPTIMISER PASS KEEPS THE COPY.
 *  - THE PARAMETER-TYPE AXIS IS DEAD (a5.py): s64, u64, f32, s16, u8, bool,
 *    a 4-byte struct BY VALUE, a 4-byte union by value, `s32 &`, `const s32 &`,
 *    `s32 *`, a third unused parameter -- all still 0x1e4.  Only `, ...`
 *    moves it (+5 w, 0x1fc).  A struct/union arg2 is a NEW OBJECT at the same
 *    short length, so the deck discriminates.
 *  - MULTI-BLOCK DEAD DEFS (a6.py, s71's `004ee080` homing rule: what homes a
 *    local is a DEF IN A SECOND BASIC BLOCK) x 4 pragma columns = 12 cells,
 *    still 0x1e4, again one object per column.  ARMING control: one READ of
 *    `bb` in the `a == sel` guard is 0x200 (+6 w).
 *  â˜… THE ONE CONSTRUCT THAT REACHES 122 WORDS IS `volatile s32 bb = b;`
 *    (any decl position; the store MUST be before the first call) -- and it is
 *    THE WRONG MECHANISM: it spends the word on `sw $5,0x7C($29)`, a STACK
 *    home, where retail has `daddu $19,$5,$0`, a REGISTER home.  Crossed with
 *    `opt_propagation off` it is 122 w / 68 bad and the whole call/branch
 *    skeleton lines up with retail -- but prop_off also buys a SECOND
 *    callee-saved FPR (`swc1 $f21`) against retail's one, so the length is a
 *    COINCIDENCE (5 GPR + 2 FPR + 1 stack store == 6 GPR + 1 FPR).  Do not
 *    install it; it cannot close.
 *  â‡’ s64's question is UNCHANGED and now much better fenced: retail homes a
 *  parameter that is provably never read, and neither a source spelling, nor a
 *  parameter type, nor any of the 68 optimiser passes reproduces it.  The next
 *  mechanism must come from OUTSIDE this unit -- a compiler INVOCATION flag, or
 *  a whole-TU property (a second function in the same file).  KEEP OUT OF
 *  config/ocunits/normal.txt. */
/* === SESSION 64 (2026-09-15, SOLO): STILL 121 vs 122, ONE WORD SHORT.  A WIDE
 * ARMED NULL on two axes s52/s54 had not covered, so do not re-run either:
 *  - THE COMPILER-KNOB AXIS IS DEAD HERE.  23 pragmas, each spelled ALONE at
 *    file scope, and each of the 23 ALSO crossed with a named `f32 one = 1.0f;`
 *    web shared by both calls and the subtraction (46 cells,
 *    build/wf-normal/s64/vfaf20.py): EVERY ONE is still 121 words.  Armed:
 *    `opt_unroll_count off` fails to build, and opt_propagation /
 *    opt_dead_assignments / opt_common_subs / no_branch_likely each give a NEW
 *    OBJECT (0x1f8 and 0x1f4 for the last two), so the deck discriminates.
 *    âš  `one` is byte-identical to the baseline WITH opt_propagation off too --
 *    the 1.0f web is not reachable by defeating propagation.
 *  - SEVEN STRUCTURAL ARMS, all still 121 (vfaf20b.py): `id` computed before
 *    the func_004f54d0 call and at the top of the function, `sel == a` instead
 *    of `a == sel`, the s058/s072 ratio split into two named f32 locals, a
 *    named `Ent *t` for the loop probe (the s64 "name the returned struct"
 *    lever), and a cached `w = c->f18`.  Only a BARE `if (func_3AE1A0(t))`
 *    moves the length, and the wrong way: 119 words (-2).
 * â‡’ nothing on the SOURCE or KNOB side reaches the sixth callee-saved
 * register.  The next lever has to make a SIXTH value genuinely live across
 * both calls; every spelling that only mentions `b` has now been refuted
 * (11 in s43, 6 in s52, 3 in s58, 7 here).
 */
/* === SESSION 54 (2026-09-12, SOLO): still ONE WORD SHORT (121 vs 122).
 * The missing word is NAMED: retail copies BOTH parameters into callee-saved
 * registers -- `daddu $20,$4,$0` (a) AND `daddu $19,$5,$0` (b) -- and saves
 * six GPRs where we save five (opscan `lq 6->5, sq 6->5`).
 * âš âš  `$19` IS NEVER READ AGAIN anywhere in retail's listing.  `b` is a
 * genuinely dead parameter that mwcc still homed, so the source must mention
 * it somewhere our draft does not -- our body does not use `b` at all.  That
 * is the lead: find the use that dead-code-eliminates.
 * Retail also holds `1.0f` in **$f20** and passes it as three arguments twice
 * (`mtc1 $2,$f20` at 0x004FB050, then `mov.s $f12/$f13/$f14,$f20` at both
 * call sites, and `sub.s $f1,$f20,$f1` for `1.0f - D_0047D35C`).
 * âš  6 arms (a_4faf20.py) say a NAMED `f32 one = 1.0f;` local shared by both
 * calls does NOT buy that: `one` declared and assigned at five different
 * points, with and without a companion `neg = -1.0f`, is BYTE-IDENTICAL to the
 * baseline every time -- mwcc propagates the constant back to each use.
 * The $f20 allocation follows from something else being live across the calls.
 */
/* === SESSION 52 (2026-09-08, SOLO): still 121 w vs retail's 122, ONE WORD
 * SHORT.  Six arms on the s43 header's single open question -- "what does
 * retail's source do with `b` that is live across func_1FEDE0() and yet emits
 * NO instruction?".  ALL NULL; four are BYTE-IDENTICAL to the baseline
 * (ad7e5b40): a C++ unused reference binding `s32 &rb = b;`, an unused
 * `s32 *pb = &b;`, an empty `static inline void keep_(s32 &x) {}` called with
 * `keep_(b)` before the first call, and widening the parameter to `s64`.
 * ONE NEW OBJECT, still short: passing `a`/`b` as an 8-byte STRUCT BY VALUE
 * (`struct Pair { s32 a; s32 b; };`, used as `p.a` directly or copied to a
 * local) gives 1844cce6 at 0x1e4 -- so mwcc passes the pair in $4/$5 and does
 * NOT home the unused half.  The struct-parameter hypothesis is refuted.
 * WARN read the retail listing before the next arm: $f20 is used for TWO
 * things (it holds `(f32)e->s058()` across the s072 virtual call at
 * 0x004FAFE8, then is reloaded with 1.0f at 0x004FB050 and reused by every
 * later mov.s and by `sub.s $f1,$f20,$f1`).  The `lui:6->7` half of the
 * missing word is that ONE 1.0f web spanning both func_2905B0/func_2904E0
 * calls; we rematerialise it.  The parameter homing and the 1.0f web may be
 * ONE allocator fact, not two -- do not keep attacking them separately. */
/* === SESSION 43 (2026-09-07): PARKED at 121 words vs retail's 122 -- ONE WORD
 * SHORT, and the word is now NAMED EXACTLY.  Two new board-wide screens agree:
 *   build/wf-normal/s43/opscan.py -> `sq:6->5  lq:6->5  lui:6->7`
 *   build/wf-normal/s43/spscan.py -> `0x70:2->0`
 * Retail's frame is 0x80 and saves SIX callee-saved GPRs ($16..$21) at
 * 0x10..0x60; ours is 0x70 and saves FIVE.  The sixth is `daddu $19,$5,$0` at
 * 0x004FAF3C -- PARAMETER `b`, homed at entry and then NEVER READ (grep the
 * listing: $19 appears exactly three times, the sq, that daddu and the lq).
 * Arithmetic: +1 sq +1 lq -1 lui = the missing word.
 *   retail  a=$20 b=$19 c=$16 n=$21 sel=$18 i=$17   (six)
 *   ours    a=$16 c=$18 n=$17 sel=$19 i=$20         (five)
 * The `lui:6->7` half is the same fact seen from the float side: retail
 * materialises 1.0f ONCE into the already-saved $f20 and reuses it across BOTH
 * func_2905B0/func_2904E0 calls (`mov.s $f12/$f13/$f14,$f20`, `sub.s $f1,$f20,$f1`);
 * we rematerialise `lui 0x3F80 / mtc1` a second time for `1.0f - D_0047D35C`.
 *
 * MEASURED NULLS (26 arms, all ARMED -- the baseline object is ad7e5b40 and a
 * live-use control moved it):
 *  - ELEVEN dead spellings of a `b` use, ALL BYTE-IDENTICAL to the baseline:
 *    `(void)b;`, `b = b;`, `if (b) {}`, `s32 bb = b;`, `b;`, `b = b + 0;`,
 *    `b = b | 0;`, `const s32 b` in the signature, `a == sel && b == b`,
 *    `return b * 0;`, `sel = b;` before `sel = -1;`.  mwcc's dead/constant
 *    propagation runs BEFORE parameter homing, so a dead use cannot buy it.
 *  - EIGHT spellings of a named `f32 one = 1.0f;` web (declared before/after
 *    `r`, assigned at the top / at the `id` statement / after it, as a
 *    declaration initialiser, `const`, and applied only to the subtraction):
 *    ALL BYTE-IDENTICAL to the baseline.  mwcc constant-propagates the local
 *    away before it can be coloured -- naming a float CONSTANT does not create
 *    a web here (contrast [[levers.d/mwcc-float-zero-seed-web]], where the web
 *    is created by a NEIGHBOURING statement, not by naming the constant).
 *  - ARMING / direction control: a LIVE use of `b` before the first call DOES
 *    buy the sixth register and the RIGHT LENGTH -- `sel = b - 1;` in place of
 *    `sel = -1;` is 122 words (114 bad).  `for (i = b; ...)` is still short.
 * â‡’ THE OPEN QUESTION IS EXACTLY ONE: what does retail's source do with `b`
 * that is live across `func_1FEDE0()` and yet emits NO instruction?  Do not
 * spend more arms on dead spellings or on naming the 1.0f; both channels are
 * closed.  KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x004FAF20 -- picks the row to highlight.  Scans the roster for the
 * last member whose func_3AE1A0 byte is 1, lets a positive `a` override that
 * choice, and when the chosen member's slot-58/slot-72 ratio clears 0.2 fades
 * the i*7+6 widget of panel normal_D_00527020 -- brighter still if it is the caller's
 * own row.
 *
 * C++ virtual: 0xF0 -> slot 58, 0x128 -> slot 72.
 * `andi 0xFF` on the return of func_3AE1A0 is the u8 -> s32 promotion at the
 * CALL, so the callee returns `u8`, not a mask written here. */
class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s058() { return VCM0(s32, 0xF0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s072(s32 a) { return VCM(s32, (void *, s32), 0x128, a); }
};

typedef struct Ctx { u8 pad00[0x18]; s32 f18; } Ctx;

extern "C" u8 normal_D_00527020[];

extern "C" {
extern f32   D_0047D35C;          /* gp - 0x7E14 */
extern f32   D_0047D518;          /* gp - 0x7C58 */

extern Ctx  *GetGameData_1fede0(void);
extern s32   PartyCountMembers_3c2010(s32 w, s32 b, s32 c);
extern Ent  *PartyGetMemberChara_3c2420(s32 w, s32 i);
extern u8    CharaIsPartyLeader_3ae1a0(Ent *e);
extern void  UiFadeWidgetColor_2904e0(void *p, u16 id, f32 a, f32 b, f32 c, f32 d, f32 e);
extern void  UiSetWidgetColor_2905b0(void *p, u16 id, f32 a, f32 b, f32 c, f32 d);
extern void *normal_IdentityPtr_4f54d0(const u8 *p);
}

#pragma opt_dead_assignments off
extern "C" s32 normal_BtlChgMenuPanelGlowMaybe_4faf20(s32 a, s32 b)
{
    Ctx  *c;
    Ent  *e;
    void *q;
    s32   n;
    s32   sel;
    s32   i;
    u16   id;
    f32   r;
    f32   one;

    c = GetGameData_1fede0();
    n = PartyCountMembers_3c2010(c->f18, 1, 1);
    sel = -1;
    for (i = 0; i < n; i++) {
        if (CharaIsPartyLeader_3ae1a0(PartyGetMemberChara_3c2420(c->f18, i)) == 1) {
            sel = i;
        }
    }
    if (a > 0) {
        sel = a;
    }
    e = PartyGetMemberChara_3c2420(c->f18, sel);
    if (e == 0) {
        return 0;
    }
    r = (f32)e->s058() / (f32)e->s072(1);
    if (r <= D_0047D518) {
        return 0;
    }
    q = normal_IdentityPtr_4f54d0(normal_D_00527020);
    if (q == 0) {
        goto done;
    }
    id = (u16)(sel * 7 + 6);
    one = 1.0f;
    if (b) {
        one = 1.0f;
    }
    UiSetWidgetColor_2905b0(q, id, one, one, one, -1.0f);
    if (a == sel) {
        UiSetWidgetColor_2905b0(q, id, D_0047D35C, D_0047D35C, D_0047D35C, -1.0f);
        UiFadeWidgetColor_2904e0(q, id, one, one, one, -1.0f, (one - D_0047D35C) / 16.0f);
    }
done:
    return 0;
}
