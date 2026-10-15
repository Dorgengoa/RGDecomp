#include "types.h"
/* === SESSION 43 (2026-09-07, SOLO): 16 bad -> MATCH.  ONE EDIT, and it is a
 * DECLARATION-ORDER edit of a kind no previous NORMAL sweep had tried.
 * Every screen was silent -- opscan.py, spscan.py and brscan.py all d=0 -- so
 * the whole residue was a clean THREE-CYCLE over the three call-result webs,
 * in creation order h, ow, hd:
 *     ours    h=$18  ow=$19  hd=$17
 *     retail  h=$19  ow=$17  hd=$18
 * ★★★★★★★ THE LEVER IS CONTIGUITY, NOT POSITION.  The three declarations were
 * SPLIT in the list (`Own *ow;` at index 3, `s32 h;`/`s32 hd;` at 8/9).
 * Declaring them as ONE CONTIGUOUS GROUP in the order h, hd, ow MATCHES, and
 * it matches at EVERY anchor tried -- positions 0, 2, 4, 6 and 8 in the
 * remaining list all give the byte-IDENTICAL object 7ed3b6eb.  Only anchor 10
 * (past `kind`/`nm`) differs, at 30.
 * The full 6 x 6 lattice (all orders of the trio x six anchors) was measured:
 *     h/hd/ow  MATCH at anchors 0-8, 30 at 10
 *     hd/h/ow  9       h/ow/hd 12      (the rest 16-30)
 * ⇒ on this unit the interfering group's INTERNAL order fixes the colouring
 * and its ABSOLUTE position is inert.  Sweep an interfering triple as a
 * CONTIGUOUS BLOCK before believing a whole-list single-move sweep's null
 * ([[levers.d/mwcc-gpr-decl-order-map]], [[levers.d/mwcc-callee-saved-creation-order]]). */
/* SESSION 30: 26 -> 16 bad, RIGHT LENGTH, residue PURE CALLEE-SAVED.
 * The pool-wide DEFINING-STATEMENT MOVE deck (build/wf-normal/s30/mkmove30.py)
 * took it there on ONE edit: `idx = (s16)(cu->f14 + ...)` moved ABOVE
 * `st = D_00484454;`.  s29's declaration deck was a 47-arm collapse to ONE
 * object on this unit and that is not a null -- a C++ point-of-declaration
 * local is NORMALISED, so DECL order cannot be the lever here and CREATION
 * (first-definition) order is.
 * The remaining 16 words are a clean THREE-CYCLE over three call results:
 *     h  (func_1F5BE0)  retail $s3, ours $s2
 *     ow (func_3C2FB0)  retail $s1, ours $s3
 *     hd (func_1FDB60)  retail $s2, ours $s1
 * c, tab, idx, nm, kind all agree.  The mechanism is WHICH web coalesces onto
 * c's register after c dies at 0x004FC07C: retail reuses $s1 for `ow` (the
 * next web created), we reuse it for `hd`.  All three are CALL results, so
 * the pure-statement deck cannot reach them -- the next lever is the order of
 * the CALL statements themselves, or a temp that changes when c dies.
 * Stage-2 swaps (22 arms) and the 197-arm exit sink found nothing better.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* normal 0x004FBF80 -- the equip/unequip confirm.  func_28E170 raises the
 * D_004B2570 dialog; answer 2 (cancel) or answer 1 on a locked slot just closes
 * it, answer 1 otherwise resolves the highlighted slot out of the 0x55F4 cursor
 * (row + 8*col + 8*page), swaps the item through the owner's slot-228 or
 * slot-229 handler depending on the gp 0x452 mode, and re-sends 0x5611.
 *
 * C++ virtuals: 0x398 -> slot 228, 0x39C -> slot 229.
 * `lui $5,0x4B / addiu $5,$5,0x2570` is a SYMBOL reference, not an integer
 * constant -- `lui/ori` is the integer spelling (LEVERS.md 8b). */
class Own {
public:
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
    virtual void s179();
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
    virtual void s228(void *e);
    virtual void s229(void *e);
    u8 pad04[0xC - 4];
    s32 f0C;
};

typedef struct Rec { u8 pad00[0x10]; s16 f10; } Rec;
typedef struct Cur { u8 pad00[0x14]; s16 f14; s16 f16; u8 pad18[2]; s16 f1A; } Cur;
typedef struct St  { u8 pad000[0x7C]; void *f7C[1]; u8 pad2[0x452 - 0x80]; s16 f452; } St;
typedef struct Ctx { u8 pad00[0x18]; s32 f18; } Ctx;
typedef struct Slt { u8 pad00[0x10]; s16 *f10; } Slt;

extern const u8 D_004B2570[];
extern const u8 D_005278E0[];

extern "C" {
extern void *D_004844A0;          /* gp - 0xCD0 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern void *D_00484498;          /* gp - 0xCD8 */
extern St   *D_00484454;          /* gp - 0xD1C */

extern s32   func_28E170(void *p, const u8 *q, s32 c, s32 d);
extern Rec  *func_28EC60(void *p);
extern void  func_291110(void *p, s32 id, s32 c, s32 d);
extern void  func_28EDE0(void *p, s32 id, s32 c);
extern Ctx  *func_1FEDE0(void);
extern s32   func_1F5BE0(void);
extern Cur  *func_28EA40(void *p, s32 id);
extern Own  *func_3C2FB0(s32 w, s32 k);
extern void  func_2F46D0(void);
extern s32   func_1FDB60(void);
extern void  func_1F0E20(s32 h, s32 a, s32 b);
extern void  func_1F0E60(s32 h, s32 a, s32 b);
extern void  func_1F0EA0(s32 h, s32 b, s16 c);
extern void  func_1F0EE0(s32 h, s32 b, s16 c);
extern void  func_28DB90(s32 a);
extern void  func_2F40B0(s32 a);
extern void  func_28D820(const u8 *p, s32 a);
extern s32   normal_BtlChgPageGetMember_505f90(St *s);
}

extern "C" s32 normal_BtlChgMenuWeaponConfirmState_4fbf80(void)
{
    Rec *r;
    Ctx *c;
    Cur *cu;
    Slt *sl;
    St  *st;
    void **tab;
    s32  k;
    s32  idx;
    s32  h;
    s32  hd;
    Own *ow;
    s32  kind;
    s16  nm;

    k = func_28E170(D_004844A0, D_004B2570, 0, 0);
    r = func_28EC60(D_004844A0);
    if (k == 2) {
        func_291110(D_0048449C, 0x49, 0, 1);
        func_28EDE0(D_00484498, 0x5601, 0);
    } else if (k == 1) {
        if (r->f10 == 0) {
            c = func_1FEDE0();
            if (c == 0) {
                return 0;
            }
            h = func_1F5BE0();
            if (h == 0) {
                return 0;
            }
            cu = func_28EA40(D_004844A0, 0x55F4);
            idx = (s16)(cu->f14 + cu->f16 * 8 + cu->f1A * 8);
            st = D_00484454;
            tab = st->f7C;
            ow = func_3C2FB0(c->f18, normal_BtlChgPageGetMember_505f90(st));
            if (ow == 0) {
                return 0;
            }
            func_2F46D0();
            hd = func_1FDB60();
            sl = (Slt *)tab[(s16)idx];
            nm = sl->f10[0];
            kind = ow->f0C;
            if (D_00484454->f452 == 0) {
                ow->s228(sl);
                func_1F0E60(hd, h, kind);
                func_1F0EE0(hd, kind, nm);
                if (kind == 6) {
                    func_28DB90(kind);
                }
            } else {
                ow->s229(sl);
                func_1F0E20(hd, h, kind);
                func_1F0EA0(hd, kind, nm);
                if (kind != 6) {
                    func_28DB90(kind);
                }
            }
            func_2F40B0(1);
            func_28EDE0(D_00484498, 0x5611, 0);
        } else {
            func_291110(D_0048449C, 0x49, 0, 1);
            func_28EDE0(D_00484498, 0x5601, 0);
        }
    }
    func_28D820(D_005278E0, 0x28);
    return 1;
}
