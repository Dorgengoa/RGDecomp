/* rgp:protos */
#line 1
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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void s228(void *e) { VCM(void, (void *, void *), 0x398, e); }
    void s229(void *e) { VCM(void, (void *, void *), 0x39C, e); }
    u8 pad04[0xC - 4];
    s32 f0C;
};

typedef struct Rec { u8 pad00[0x10]; s16 f10; } Rec;
typedef struct Cur { u8 pad00[0x14]; s16 f14; s16 f16; u8 pad18[2]; s16 f1A; } Cur;
typedef struct St  { u8 pad000[0x7C]; void *f7C[1]; u8 pad2[0x452 - 0x80]; s16 f452; } St;
typedef struct Ctx { u8 pad00[0x18]; s32 f18; } Ctx;
typedef struct Slt { u8 pad00[0x10]; s16 *f10; } Slt;

extern "C" u8 D_004B2570[];
extern "C" u8 normal_D_005278E0[];

extern "C" {
extern void *D_004844A0;          /* gp - 0xCD0 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern void *D_00484498;          /* gp - 0xCD8 */
extern St   *D_00484454;          /* gp - 0xD1C */

extern s32   MenuGridCursorInput_28e170(void *p, const u8 *q, s32 c, s32 d);
extern Rec  *UiEntryListGetCurrentData_28ec60(void *p);
extern void  UiSetWidgetsVisibleById_291110(void *p, s32 id, s32 c, s32 d);
extern void  StateMachineSetState_28ede0(void *p, s32 id, s32 c);
extern Ctx  *GetGameData_1fede0(void);
extern s32   GetCurrentScene_1f5be0(void);
extern Cur  *UiEntryListFindByTag_28ea40(void *p, s32 id);
extern Own  *PartyGetSlotChara_3c2fb0(s32 w, s32 k);
extern void  PartyLoadSlotsFill_2f46d0(void);
extern s32   GetCharaResMgr_1fdb60(void);
extern void  CharaResReleaseWeapon2ById_1f0e20(s32 h, s32 a, s32 b);
extern void  CharaResReleaseWeapon1ById_1f0e60(s32 h, s32 a, s32 b);
extern void  CharaResLoadWeapon2ById_1f0ea0(s32 h, s32 b, s16 c);
extern void  CharaResLoadWeapon1ById_1f0ee0(s32 h, s32 b, s16 c);
extern void  WorkIconRefreshCharaWeaponMaybe_28db90(s32 a);
extern void  PartyRefreshMembersMaybe_2f40b0(s32 a);
extern void  UiSelFrameAnimStep_28d820(const u8 *p, s32 a);
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

    k = MenuGridCursorInput_28e170(D_004844A0, D_004B2570, 0, 0);
    r = UiEntryListGetCurrentData_28ec60(D_004844A0);
    if (k == 2) {
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x49, 0, 1);
        StateMachineSetState_28ede0(D_00484498, 0x5601, 0);
    } else if (k == 1) {
        if (r->f10 == 0) {
            c = GetGameData_1fede0();
            if (c == 0) {
                return 0;
            }
            h = GetCurrentScene_1f5be0();
            if (h == 0) {
                return 0;
            }
            cu = UiEntryListFindByTag_28ea40(D_004844A0, 0x55F4);
            idx = (s16)(cu->f14 + cu->f16 * 8 + cu->f1A * 8);
            st = D_00484454;
            tab = st->f7C;
            ow = PartyGetSlotChara_3c2fb0(c->f18, normal_BtlChgPageGetMember_505f90(st));
            if (ow == 0) {
                return 0;
            }
            PartyLoadSlotsFill_2f46d0();
            hd = GetCharaResMgr_1fdb60();
            sl = (Slt *)tab[(s16)idx];
            nm = sl->f10[0];
            kind = ow->f0C;
            if (D_00484454->f452 == 0) {
                ow->s228(sl);
                CharaResReleaseWeapon1ById_1f0e60(hd, h, kind);
                CharaResLoadWeapon1ById_1f0ee0(hd, kind, nm);
                if (kind == 6) {
                    WorkIconRefreshCharaWeaponMaybe_28db90(kind);
                }
            } else {
                ow->s229(sl);
                CharaResReleaseWeapon2ById_1f0e20(hd, h, kind);
                CharaResLoadWeapon2ById_1f0ea0(hd, kind, nm);
                if (kind != 6) {
                    WorkIconRefreshCharaWeaponMaybe_28db90(kind);
                }
            }
            PartyRefreshMembersMaybe_2f40b0(1);
            StateMachineSetState_28ede0(D_00484498, 0x5611, 0);
        } else {
            UiSetWidgetsVisibleById_291110(D_0048449C, 0x49, 0, 1);
            StateMachineSetState_28ede0(D_00484498, 0x5601, 0);
        }
    }
    UiSelFrameAnimStep_28d820(normal_D_005278E0, 0x28);
    return 1;
}
