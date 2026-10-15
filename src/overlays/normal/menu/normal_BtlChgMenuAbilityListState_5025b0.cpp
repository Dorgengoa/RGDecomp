/* ******* CLOSED s29 (2026-09-04) -- BYTE-IDENTICAL, 872 B, on TWO DECLARATION
 * MOVES AND NOTHING ELSE (20 bad -> 7 -> MATCH):
 *   stage 1  `Sel *e;` moved from position 4 to position 7   (20 -> 7)
 *   stage 2  `Item *it;` <-> `s32 r;` swapped                (7  -> MATCH)
 * At 7 bad the residue was a PURE TWO-REGISTER CALLEE-SAVED TRANSPOSITION,
 * s0 <-> s2 over exactly two webs -- `o = func_1FEDE0()` (retail $s0) and
 * `e = func_3C2FB0(...)` (retail $s2) -- i.e. retail follows first-definition
 * order and we inverted it ([[mwcc-callee-saved-creation-order]],
 * [[residue-transposition-class]]).  s28's regswap28.py reported NORMAL had
 * ZERO pure two-register swaps to aim the degree work at; this unit BECAME one
 * after stage 1, so that census is a snapshot, not a property of the image.
 * !! Stage 2 is a PAIRWISE SWAP and stage 1 a SINGLE MOVE, and neither deck
 * finds the other's edit: the whole-list single-move deck gave 5 objects at
 * stage 1, and the swap only pays once the move is the base.  The STAGED deck
 * ([[mwcc-wholelist-decl-sweep]]) is the method, not a refinement of it.
 * build/wf-normal/s29/mkdeck29.py (pool deck, 1,120 arms over 20 units, every
 * unit's identity arm reproducing its recorded bad count) + the stage-2 rerun.
 */
#include "types.h"
/* normal 0x005025B0 -- the item-list screen's input frame.  func_28E170 over
 * the D_004B2570 pad map returns a mode: 1 = confirm, which walks the current
 * roster entry's iterator (func_3A8180 / func_370170 / func_36FFF0) to the row
 * the cursor is on and hands the found item to virtual slot 179, then either
 * refuses through 0x560E or opens the 0x55F4 sub-page and consumes the item
 * through slot 281; 2 = cancel; 6 = the sort toggle, which re-colours the
 * 0x1E / 0x1F headers according to normal_FUN_00505DB0.
 *
 * FOUR VIRTUAL calls, so the unit is .cpp -- a struct of function pointers
 * gives `jalr $v0`.  The slots are (0x5C-8)/4 = 21, (0x2D4-8)/4 = 179,
 * (0x46C-8)/4 = 281 and (0x470-8)/4 = 282; the dummy block is GENERATED so the
 * indices cannot drift.
 * `$4` is never read -- the f(void *, s32) state-handler family.
 * D_004B2570 is a main-image object and needs a declared size over the
 * small-data threshold, or it comes out GPREL16 instead of lui/%lo.
 * `daddu $18,$3,$2` sits in func_1FEDE0's DELAY SLOT: the row index is the
 * statement BEFORE that call, and `$16` is then re-used for its result. */

typedef struct Pos { u8 pad00[0x12]; s16 f12; u8 pad14[2]; s16 f16; } Pos;
typedef struct Ctx { u8 pad000[0x440]; s32 f440; } Ctx;
typedef struct Own { u8 pad00[0x18]; s32 f18; } Own;
typedef struct Cur { u8 b[8]; } Cur;
typedef struct Src { u8 b[0x18]; } Src;
typedef struct Item { u8 b[4]; } Item;

struct Sel {
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
    virtual s32   owner();                 /* slot 21  -> vtable +0x5C  */
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
    virtual s32   pick(Item *it);          /* slot 179 -> vtable +0x2D4 */
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
    virtual void  take(Item *it);          /* slot 281 -> vtable +0x46C */
    virtual s32   locked();                /* slot 282 -> vtable +0x470 */
};

extern "C" u8   D_004B2570[0x10];   /* main-image object, materialised as an ADDRESS */

extern "C" void *D_0048449C;      /* gp - 0xCD4  */
extern "C" void *D_004844A0;      /* gp - 0xCD0  */
extern "C" void *D_004844A4;      /* gp - 0xCCC  */
extern "C" void *D_00484498;      /* gp - 0xCD8  */
extern "C" Ctx  *D_00484454;      /* gp - 0xD1C  */
extern "C" f32   D_0047D278;      /* gp - 0x7EF8 */

extern "C" s32   func_1839F0(const u8 *p, s32 a);
extern "C" void  func_1B9520(void *p, s32 a, s32 b, f32 c);
extern "C" Own  *func_1FEDE0(void);
extern "C" s32   func_2899B0(Ctx *p, s32 a);
extern "C" s32   func_28E170(void *p, const u8 *q, s32 c, s32 d);
extern "C" void  func_28EA90(void *p, s32 id, s32 a);
extern "C" Pos  *func_28EC60(void *p);
extern "C" void  func_28EDE0(void *p, s32 id, s32 a);
extern "C" void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern "C" void  func_290F50(void *p, u16 id, s32 x, s32 y, s32 c, f32 t);
extern "C" void  func_291110(void *p, u16 id, s32 c, s32 d);
extern "C" Item *func_36FFF0(Cur *c, s32 n);
extern "C" void  func_370170(Cur *c, Src *s);
extern "C" void  func_3A8180(Src *s, Sel *e, s32 c, s32 d);
extern "C" Sel  *func_3C2FB0(s32 a, s32 b);
extern "C" void  normal_BtlChgMenuAbilityDetailRefresh_503450(void);
extern "C" void  normal_LeaderHudBannerReshow_503720(void);
extern "C" void  normal_BtlChgPageSetAbilityReq_5052f0(Ctx *p, s32 a, s32 b);
extern "C" s32   normal_BtlChgPageIsDetailShown_505db0(Ctx *p);
extern "C" void  normal_BtlChgPageToggleDetail_505dc0(Ctx *p, s32 a, s32 b);
extern "C" s32   normal_BtlChgPageGetMember_505f90(Ctx *p);
extern "C" void  normal_BtlChgPageSetCloseCode_505fc0(Ctx *p, s32 a);

extern "C" s32 normal_BtlChgMenuAbilityListState_5025b0(void *a, s32 b);

s32 normal_BtlChgMenuAbilityListState_5025b0(void *a, s32 b)
{
    Cur   cur;
    Src   src;
    Pos  *q;
    Own  *o;
    s32   r;
    s32   mode;
    s32   row;
    Sel  *e;
    Item *it;
    const u8 *pad;

    if (b != 0) {
        func_291110(D_0048449C, 0x40, 1, 1);
        func_28EA90(D_004844A0, 0x55F1, 0);
    }
    mode = func_28E170(D_004844A0, D_004B2570, 1, 0);
    q = func_28EC60(D_004844A0);
    if (mode == 1) {
        func_1B9520(D_004844A4, 5, 0, 1.0f);
        if (q != 0) {
            row = q->f12 + q->f16;
            o = func_1FEDE0();
            if (o == 0) {
                return 0;
            }
            e = func_3C2FB0(o->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
            if (e == 0) {
                return 0;
            }
            func_3A8180(&src, e, 0, -1);
            func_370170(&cur, &src);
            it = func_36FFF0(&cur, row);
            if (it == 0) {
                return 0;
            }
            r = e->pick(it);
            if (r != 0) {
                if (e->locked() == 0) {
                    func_28EDE0(D_00484498, 0x55F4, 0);
                    normal_LeaderHudBannerReshow_503720();
                    normal_BtlChgPageSetAbilityReq_5052f0(D_00484454, e->owner(), r);
                    D_00484454->f440 = 1;
                    normal_BtlChgPageSetCloseCode_505fc0(D_00484454, 1);
                    e->take(it);
                } else {
                    func_28EDE0(D_00484498, 0x560E, 0);
                }
            }
        }
    } else if (mode == 2) {
        func_1B9520(D_004844A4, 6, 0, 1.0f);
        func_28EDE0(D_00484498, 0x55F5, 0);
    } else if (mode == 6) {
        pad = D_004B2570;
        if (q != 0 && func_1839F0(pad, 0x10) != 0
            && func_2899B0(D_00484454, 0x1F) != 0) {
            normal_BtlChgPageToggleDetail_505dc0(D_00484454, 0, 0);
            if (normal_BtlChgPageIsDetailShown_505db0(D_00484454) != 0) {
                func_1B9520(D_004844A4, 5, 0, 1.0f);
                func_290F50(D_0048449C, 0x1F, -0x6E, -0x7B, 0, D_0047D278);
                func_290690(D_0048449C, 0x1F, 1.0f, 0.125f, 0.0f);
                func_290690(D_0048449C, 0x1E, 0.0f, 0.125f, 1.0f);
            } else {
                func_1B9520(D_004844A4, 6, 0, 1.0f);
                func_290F50(D_0048449C, 0x1F, 0x32, -0x7B, 0, D_0047D278);
                func_290690(D_0048449C, 0x1F, 0.0f, 0.25f, 1.0f);
                func_290690(D_0048449C, 0x1E, 1.0f, 0.125f, 0.0f);
            }
        }
    }
    normal_BtlChgMenuAbilityDetailRefresh_503450();
    return 1;
}
