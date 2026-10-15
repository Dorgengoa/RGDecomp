/* === SESSION 71 (2026-09-21, SOLO): 120 bad -> MATCH.  Four edits crossed
 * plus the frame (build/wf-normal/s71/g1.py, g2.py):
 *  - `m = 0x38;` moved back to right before `if (D_004844F4 != 0) m = 2;` --
 *    s31's move deck had hoisted it above the calls, which made m live across
 *    them and cost the EXTRA callee-saved register s67 could not find.
 *  - `D_004844F4 = 0;` right after the arr fill (retail's `sb $0` sits before
 *    the first call).  s67 measured this at 210 bad ALONE -- it only pays
 *    crossed with the m move.  A recorded null is a coat fact.
 *  - `s32 n` + `n = (s16)(hd->f016 + hd->f01A);` -- s67's re-narrow half.
 *  - arr fill as an 8-byte aggregate copy `*(S4 *)arr = *(const S4 *)
 *    D_004805A8;` (unrotated, as in normal_LeaderHudGaugeLevelRefresh_507ff0).
 *  - locals declared `tmp0, buf, tmp1, arr, it0, it1`: mwcc lays out the
 *    16-aligned group and the small group each in REVERSE declaration order,
 *    so retail's ascending tmp1/buf/tmp0 + it1/it0/arr pins this order.
 * Everything below predates this session. */
/* SESSION 67 (2026-09-20): 127 bad -> 120, still EXACT LENGTH (439 w).
 * Found from the [[mwcc-identity-cast-splits-cse]] sq screen
 * (build/wf-normal/s67/sqscan.py): FOUR callee-saved `sq`s to retail's THREE.
 * THE COPY WIDTH OF THE 448-BYTE STRUCT ASSIGNMENT IS THE LEVER
 * ([[mwcc-aggregate-fill-vs-elementwise]], "the width is a sweepable axis").
 * `buf = D_00525430;` on the natural `Blk`/`Cell` types makes mwcc copy in
 * 16-byte `lq`/`sq` units; retail's loop is `li $4,56` + `lw/lw/sw/sw` +
 * `addiu 8` -- EIGHT bytes per iteration.  Copying through a 4-byte-element
 * VIEW type, `*(Blk4 *)&buf = *(Blk4 *)&D_00525430;` with
 * `struct Blk4 { s32 w[112]; }`, reproduces retail's loop BYTE-IDENTICALLY
 * and removes the two quadword temps.
 * !! THE STRUCT'S OWN SHAPE IS INERT.  s64/f64 members in `Cell`, an all-u8
 * `Cell`, an all-s16 `Cell` and an `s64 w[56]` view are ALL 127 -- only the
 * s32 view moves it.  Do not sweep Cell's layout again.
 * THE 120 LEFT, from n_odiff:
 *   - ONE EXTRA CALLEE-SAVED REGISTER (sq at 0x004FC4B8, lq at 0x004FCB84):
 *     ours s0-s3, retail $16-$18, frame 0x250 vs 0x240.  Unfound.
 *   - TWO REDUNDANT NARROWING sites, 0x004FC694 and 0x004FCA84: retail
 *     re-narrows `n` with `dsll32/dsra32` AT the `func_36FFF0` call even
 *     though it is already s16-valued ([[insect-session91-levers]]).
 *     `s32 n` + `n = (s16)(hd->f016 + hd->f01A);` DOES emit both pairs but is
 *     +2 WORDS, so it is a cross half needing a -2 partner -- most likely the
 *     extra callee-saved register.  `(s16)` at the call site alone, and an
 *     `s32` parameter with the cast, are both inert/long.
 *   - !! `D_004844F4 = 0;` IS ALREADY IN THE RIGHT PLACE.  Moving it to the
 *     top of the `if (arg1 != 0)` block is 210 bad, before `root =` is 438 w,
 *     before `m = 0x38;` is 141 -- the session-31 MOVE install was correct
 *     and n_odiff's alignment of the `sb` is MISLEADING.  Do not re-run.
 * Sweeps in build/wf-normal/s67/gen4b0*.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* === SESSION 49 (2026-09-08): 128 -> 127 bad, exact 439 words.  A SYMBOL-NAME
 * TYPO, found by build/wf-normal/s49/relscan.py (the relocation-stream screen).
 * The four s16 loads read `D_00480598[0..3]` while the declaration's OWN
 * comment said it was gp minus 0x4BC8, and gp-0x4BC8 is 0x004805A8 -- a 98/A8
 * digit transposition that had been in the file since it was drafted.  Renamed
 * to D_004805A8 throughout.  NO OTHER SCREEN ON THIS BOARD CAN SEE IT: our
 * object carries 0 in the relocated word, so offscan/permscan/opscan mask it,
 * and mdiff compares the OPCODE only.
 * relscan's REMAINING two facts on this unit, both still open:
 *   - retail touches 0x004844F4 at reference 5 (an `sb $0,-0xC7C($28)` in the
 *     head) and we touch it at reference 42 -- the statement is ~37 references
 *     too late in source order;
 *   - retail touches 0x004844A0 once more than we do (reference 33).
 * WARN THAT FIRST ONE IS AN s31 INSTALL: `MV_D_004844F4_L398_T422_SAFE_mov`,
 * from the same 31,338-arm statement-move sweep that broke normal_TransWarpListState_51c2e0.
 * The deck moved a defining statement 24 lines to a better BAD COUNT and the
 * relocation stream says the position is wrong.  Re-screen every s31 install
 * with relscan before trusting it.
 * Everything below predates this. */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_D_004844F4_L398_T422_SAFE_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 439 words, 221 bad   after: 439 words, 134 bad   (retail 439 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_m_L430_T409_SAFE_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 437 words, ? bad   after: 439 words, 221 bad   (retail 439 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x004FC4B0 -- 1760 bytes, 440 instructions.  Written fresh in s31
 * (lane a6).  jalr $25 x5 => C++ virtual dispatch, vptr at offset 0,
 * slot = 8 + 4*N.  Slots used: 0x5C (21), 0x2D4 (179), 0x46C (281),
 * 0x470 (282), 0x47C (285).
 *
 * The 56-iteration 8-byte copy loop out of D_00525430 is a STRUCT
 * ASSIGNMENT of a 448-byte local aggregate (14 x 0x20), not a memcpy call
 * and not a local initialiser -- an initialiser would want the template in
 * the .rodata of this object.
 */

typedef struct Ent  { u8 pad000[8]; s32 f008; } Ent;
typedef struct Iter { u8 pad000[4]; s16 f004; u8 pad006[2]; } Iter;
typedef struct Hdl  { u8 pad000[0x16]; s16 f016; u8 pad018[2]; s16 f01A; } Hdl;
typedef struct Pos  { u8 pad000[0x10]; s16 f010; } Pos;
typedef struct Hold { u8 pad000[0x20]; void *f020; } Hold;
typedef struct Root { u8 pad000[0x18]; s32 f018; } Root;
typedef struct Ctx  { u8 pad000[0x440]; s32 f440; } Ctx;

typedef struct Cell {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
    s32 f008;
    s32 f00C;
    s32 f010;
    s32 f014;
    s32 f018;
    s32 f01C;
} Cell;

typedef struct Blk { Cell e[14]; } Blk;
/* SESSION 67: the 8-byte-granular view that drives the COPY WIDTH.  See
 * the session-67 note at the top of this file. */
typedef struct S4 { s16 a[4]; } S4;
typedef struct Blk4 { s32 w[112]; } Blk4;

struct Obj {
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
    virtual s32 m021();
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
    virtual void s101();
    virtual void s102();
    virtual void s103();
    virtual void s104();
    virtual void s105();
    virtual void s106();
    virtual void s107();
    virtual void s108();
    virtual void s109();
    virtual void s110();
    virtual void s111();
    virtual void s112();
    virtual void s113();
    virtual void s114();
    virtual void s115();
    virtual void s116();
    virtual void s117();
    virtual void s118();
    virtual void s119();
    virtual void s120();
    virtual void s121();
    virtual void s122();
    virtual void s123();
    virtual void s124();
    virtual void s125();
    virtual void s126();
    virtual void s127();
    virtual void s128();
    virtual void s129();
    virtual void s130();
    virtual void s131();
    virtual void s132();
    virtual void s133();
    virtual void s134();
    virtual void s135();
    virtual void s136();
    virtual void s137();
    virtual void s138();
    virtual void s139();
    virtual void s140();
    virtual void s141();
    virtual void s142();
    virtual void s143();
    virtual void s144();
    virtual void s145();
    virtual void s146();
    virtual void s147();
    virtual void s148();
    virtual void s149();
    virtual void s150();
    virtual void s151();
    virtual void s152();
    virtual void s153();
    virtual void s154();
    virtual void s155();
    virtual void s156();
    virtual void s157();
    virtual void s158();
    virtual void s159();
    virtual void s160();
    virtual void s161();
    virtual void s162();
    virtual void s163();
    virtual void s164();
    virtual void s165();
    virtual void s166();
    virtual void s167();
    virtual void s168();
    virtual void s169();
    virtual void s170();
    virtual void s171();
    virtual void s172();
    virtual void s173();
    virtual void s174();
    virtual void s175();
    virtual void s176();
    virtual void s177();
    virtual void s178();
    virtual s32 m179(Ent *e);
    virtual void s180();
    virtual void s181();
    virtual void s182();
    virtual void s183();
    virtual void s184();
    virtual void s185();
    virtual void s186();
    virtual void s187();
    virtual void s188();
    virtual void s189();
    virtual void s190();
    virtual void s191();
    virtual void s192();
    virtual void s193();
    virtual void s194();
    virtual void s195();
    virtual void s196();
    virtual void s197();
    virtual void s198();
    virtual void s199();
    virtual void s200();
    virtual void s201();
    virtual void s202();
    virtual void s203();
    virtual void s204();
    virtual void s205();
    virtual void s206();
    virtual void s207();
    virtual void s208();
    virtual void s209();
    virtual void s210();
    virtual void s211();
    virtual void s212();
    virtual void s213();
    virtual void s214();
    virtual void s215();
    virtual void s216();
    virtual void s217();
    virtual void s218();
    virtual void s219();
    virtual void s220();
    virtual void s221();
    virtual void s222();
    virtual void s223();
    virtual void s224();
    virtual void s225();
    virtual void s226();
    virtual void s227();
    virtual void s228();
    virtual void s229();
    virtual void s230();
    virtual void s231();
    virtual void s232();
    virtual void s233();
    virtual void s234();
    virtual void s235();
    virtual void s236();
    virtual void s237();
    virtual void s238();
    virtual void s239();
    virtual void s240();
    virtual void s241();
    virtual void s242();
    virtual void s243();
    virtual void s244();
    virtual void s245();
    virtual void s246();
    virtual void s247();
    virtual void s248();
    virtual void s249();
    virtual void s250();
    virtual void s251();
    virtual void s252();
    virtual void s253();
    virtual void s254();
    virtual void s255();
    virtual void s256();
    virtual void s257();
    virtual void s258();
    virtual void s259();
    virtual void s260();
    virtual void s261();
    virtual void s262();
    virtual void s263();
    virtual void s264();
    virtual void s265();
    virtual void s266();
    virtual void s267();
    virtual void s268();
    virtual void s269();
    virtual void s270();
    virtual void s271();
    virtual void s272();
    virtual void s273();
    virtual void s274();
    virtual void s275();
    virtual void s276();
    virtual void s277();
    virtual void s278();
    virtual void s279();
    virtual void s280();
    virtual void m281(Ent *e);
    virtual s32 m282();
    virtual void s283();
    virtual void s284();
    virtual void m285();
};

extern "C" const Blk D_00525430;
extern "C" u8  D_00527B60[];
extern "C" u8  D_00527BB0[];
extern "C" const u8 D_004B2570[];

extern "C" Ctx  *D_00484454;      /* gp - 0xD1C  */
extern "C" void *D_00484498;      /* gp - 0xCD8  */
extern "C" void *D_0048449C;      /* gp - 0xCD4  */
extern "C" void *D_004844A0;      /* gp - 0xCD0  */
extern "C" u8    D_004844F4;      /* gp - 0xC7C  */
extern "C" void *D_00481BB8;      /* gp - 0x35B8 */
extern "C" void *D_00481BBC;      /* gp - 0x35B4 */
extern "C" s16   D_004805A8[4];   /* gp - 0x4BC8 */

extern "C" void        func_1319A8(void *dst, const void *src, s32 n);
extern "C" void        func_1343B8(void *dst, const void *a, s32 b);
extern "C" s32         func_134950(s32 a, s32 b);
extern "C" Root       *func_1FEDE0(void);
extern "C" const void *func_28AA30(void *p, s32 id);
extern "C" s32         func_28E170(void *p, const u8 *q, s32 c, s32 d);
extern "C" Hdl        *func_28EA40(void *p, s32 id);
extern "C" void        func_28EA90(void *p, s32 id, s32 a);
extern "C" Pos        *func_28EC60(void *p);
extern "C" void        func_28EDE0(void *p, s32 id, s32 a);
extern "C" void        func_28F510(void *p, s32 id, const void *a, s32 b);
extern "C" void        func_28F590(void *p, s32 id, s32 a, s32 b);
extern "C" void        func_28F930(void *p, s32 id, s16 a, s32 b);
extern "C" void        func_28FBF0(void *p, s32 id, s32 a, s32 b);
extern "C" void        func_28FCD0(void *p, s32 id, s32 a, s32 b);
extern "C" void        func_290010(void *p, s32 id, s32 a, s32 b);
extern "C" Hold       *func_290460(void *p, s32 id);
extern "C" void        func_290B20(void *p, s32 id, const void *a, s32 b, s32 c, s32 d);
extern "C" void        func_290F60(void *p, s32 id, s32 a, s32 b);
extern "C" void        func_291110(void *p, s32 id, s32 a, s32 b);
extern "C" Ent        *func_36FFF0(Iter *it, s16 n);
extern "C" void        func_370170(Iter *it, void *src);
extern "C" s32         func_3A07A0(s32 a);
extern "C" void        func_3A8180(void *tmp, Obj *o, s32 a, s32 b);
extern "C" Obj        *func_3C2FB0(s32 a, s32 b);
extern "C" void        normal_LeaderHudBannerReshow_503720(void);
extern "C" void        normal_BtlChgPageSetAbilityReq_5052f0(Ctx *p, s32 a, s32 b);
extern "C" s32         normal_BtlChgPageGetMember_505f90(Ctx *p);
extern "C" void        normal_BtlChgPageSetCloseCode_505fc0(Ctx *p, s32 a);

extern "C" s32 normal_BtlChgMenuAbilityConfirmState_4fc4b0(s32 arg0, s32 arg1);

s32 normal_BtlChgMenuAbilityConfirmState_4fc4b0(s32 arg0, s32 arg1)
{
    u8    tmp0[0x10];
    Blk   buf;
    u8    tmp1[0x10];
    s16   arr[4];
    Iter  it0;
    Iter  it1;
    Root *root;
    Obj  *ob;
    Ent  *ent;
    Hdl  *hd;
    Pos  *pos;
    Hold *hold;
    void *dst;
    s32   x;
    s32   y;
    s32   k;
    s32   sel;
    s32   i;
    s32   n;
    s16   m;

    if (arg1 != 0) {
        *(S4 *)arr = *(const S4 *)D_004805A8;
        D_004844F4 = 0;
        func_291110(D_0048449C, 0x40, 0, 1);
        func_28F510(D_0048449C, 0x46, func_28AA30(D_00481BBC, 0x52), 2);
        func_28F510(D_0048449C, 0x46, func_28AA30(D_00481BBC, 0x53), 3);
        func_290010(D_0048449C, 0x45, 1, -1);
        func_290F60(D_0048449C, 0x45, 0x28, 0x84);
        func_28EA90(D_004844A0, 0x55F8, 1);
        k = func_28EC60(D_004844A0)->f010;
        func_28F930(D_0048449C, 0x46, arr[k * 2], 0);
        func_28F930(D_0048449C, 0x46, arr[k * 2 + 1], 1);
        func_290F60(D_0048449C, 0x48, k * 0x5F + 0x74, 0x38);
        root = func_1FEDE0();
        ob = func_3C2FB0(root->f018, normal_BtlChgPageGetMember_505f90(D_00484454));
        if (ob == 0) {
            return 0;
        }
        x = ob->m282();
        if (x != 0) {
            func_1343B8(D_00527B60, func_28AA30(D_00481BB8, 0x64), func_3A07A0(x));
        }
        hd = func_28EA40(D_004844A0, 0x55F1);
        n = (s16)(hd->f016 + hd->f01A);
        func_3A8180(tmp0, ob, 0, -1);
        func_370170(&it0, tmp0);
        ent = func_36FFF0(&it0, n);
        if (ent == 0) {
            return 0;
        }
        func_1343B8(D_00527BB0, func_28AA30(D_00481BB8, 0x65), ent->f008);
        if (func_134950(func_3A07A0(x), ent->f008) == 0) {
            D_004844F4 = 1;
        }
        m = 0x38;
        if (D_004844F4 != 0) {
            m = 2;
        }
        *(Blk4 *)&buf = *(Blk4 *)&D_00525430;
        buf.e[0].f002 = m + 0x10;
        buf.e[2].f006 = m;
        buf.e[3].f002 = m + 0x10;
        buf.e[4].f006 = m + 0x1B;
        buf.e[6].f006 = m;
        buf.e[7].f002 = m + 0x10;
        buf.e[9].f002 = m + 0x10;
        buf.e[11].f006 = m;
        buf.e[12].f002 = m + 0x10;
        hold = func_290460(D_0048449C, 0x45);
        if (hold != 0) {
            dst = hold->f020;
            if (dst != 0) {
                for (i = 0; i < 14; i++) {
                    func_1319A8((u8 *)dst + i * 0x20, &buf.e[i], 0x20);
                }
            }
        }
        if (D_004844F4 != 0) {
            func_290F60(D_0048449C, 0x45, 0x28, 0xA2);
            func_1343B8(D_00527B60, func_28AA30(D_00481BB8, 0x6B), func_3A07A0(x));
            func_290B20(D_0048449C, 0x46, D_00527B60, -1, -1, 0);
            func_290B20(D_0048449C, 0x46, 0, -1, -1, 1);
            func_28FCD0(D_0048449C, 0x46, -1, 0);
            func_28F590(D_0048449C, 0x46, -1, 1);
            func_291110(D_0048449C, 0x47, 0, 1);
            func_291110(D_0048449C, 0x48, 0, 1);
            func_28EA90(D_004844A0, 0x55F7, 1);
        } else {
            func_28FCD0(D_0048449C, 0x46, 0x98, 0);
            func_28FCD0(D_0048449C, 0x46, 0xF7, 1);
            func_28F590(D_0048449C, 0x46, 0xE3, 1);
            func_28F590(D_0048449C, 0x46, 0xB2, 2);
            func_28F590(D_0048449C, 0x46, 0x111, 3);
            func_28F510(D_0048449C, 0x46, D_00527B60, 0);
            func_28F510(D_0048449C, 0x46, D_00527BB0, 1);
            func_28FBF0(D_0048449C, 0x47, 0x186, 1);
            func_28FCD0(D_0048449C, 0x47, 0x19A, 2);
        }
    }
    sel = func_28E170(D_004844A0, D_004B2570, 0, 0);
    pos = func_28EC60(D_004844A0);
    if (sel == 2) {
        func_290010(D_0048449C, 0x45, 0, -1);
        func_28EDE0(D_00484498, 0x55F3, 0);
    } else if (sel == 1) {
        if (D_004844F4 != 0) {
            func_290010(D_0048449C, 0x45, 0, -1);
            func_28EDE0(D_00484498, 0x55F3, 0);
        } else if (pos->f010 == 0) {
            root = func_1FEDE0();
            if (root == 0) {
                return 0;
            }
            ob = func_3C2FB0(root->f018, normal_BtlChgPageGetMember_505f90(D_00484454));
            if (ob == 0) {
                return 0;
            }
            hd = func_28EA40(D_004844A0, 0x55F1);
            n = (s16)(hd->f016 + hd->f01A);
            func_3A8180(tmp1, ob, 0, -1);
            func_370170(&it1, tmp1);
            ent = func_36FFF0(&it1, n);
            if (ent == 0) {
                return 0;
            }
            y = ob->m179(ent);
            if (y != 0) {
                func_28EDE0(D_00484498, 0x55F4, 0);
                normal_LeaderHudBannerReshow_503720();
                normal_BtlChgPageSetAbilityReq_5052f0(D_00484454, ob->m021(), y);
                D_00484454->f440 = 1;
                normal_BtlChgPageSetCloseCode_505fc0(D_00484454, 1);
                ob->m285();
                ob->m281(ent);
            }
            func_290010(D_0048449C, 0x45, 0, -1);
        } else {
            func_290010(D_0048449C, 0x45, 0, -1);
            func_28EDE0(D_00484498, 0x55F3, 0);
        }
    }
    return 1;
}
