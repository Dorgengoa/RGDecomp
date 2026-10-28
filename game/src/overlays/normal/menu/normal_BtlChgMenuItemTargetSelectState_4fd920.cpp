/* rgp:protos */
#line 1
/* MATCHED -- session 32, lane nc32d.  204 words, 0 bad, BYTE-IDENTICAL.
 * Closed on ONE word pair via mwcc-branch-likely-duplication FIX 3 read from
 * the other side: the residue was @0x004FD98C ours `bnel $16,$2 / addiu $2,$0,1`
 * (threaded, target bumped past the shared tail) where retail has the plain
 * `bne $16,$2,.L004FDC28 / nop`.  mwcc threads only the FIRST predecessor of a
 * shared `return K` block; the early explicit `return 1;` in the r == 2 arm was
 * compiled as its OWN return block, so the r != 1 test became the first
 * predecessor and stole the threaded slot.  Making that early exit a
 * `goto done;` to the ONE shared `return 1` hands the threading back to it and
 * every later predecessor gets the plain branch + nop.
 * Deck: 6 arms, 1 round trip, identity arm reproduced the 2-bad baseline.
 * Four other spellings are the SAME object (71dcab2b7ec1): else-if with a
 * single trailing return, else-if + goto, goto + `if (r != 1) goto done;`
 * flattened, and `done: ; return 1;`.  The declaration order below is s31's
 * best (it took the unit 29 -> 22 -> 11 -> 2 bad) and must not be disturbed. */
#include "types.h"
/* normal 0x004FD920 -- the item/skill target confirm step of the field menu.
 * func_28E170 runs the cursor, mode 2 backs out to 0x5606, mode 1 confirms:
 * it re-reads the selected roster slot out of normal_D_00527910[D_0048051C], builds
 * the aim matrix (func_3A7940/func_3A7430 + virtual slot 158) for the caster,
 * fires it through func_2EEF60 and then plays either the 0x4A or the 0x6 SE
 * depending on the byte func_2EEF60 wrote back.
 *
 * TWO `lw $25,0($x) / lw $25,K($25) / jalr $25` sites -> C++ virtual, vptr 0,
 * slots (0x280-8)/4 = 158 and (0xBC-8)/4 = 45.  Same Ent class, same
 * func_3A7940/func_3A7430/func_2EEF60 aim block, as normal_BtlChgMenuItemListState_4ff6c0.
 * `daddiu $3,$0,1` for the 0x40DA..0x40DF range flag is a C++ `bool` -- no
 * integer width reaches the `daddiu`.
 * `lui $5,0x4B / addiu $5,$5,0x2570` is a SYMBOL reference (D_004B2570), not
 * an integer constant: `lui/ori` would be the integer spelling. */

struct Ent {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 kind() { return VCM0(s32, 0xBC); }                           /* slot 45 -> vtable +0xBC */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void aim(void *m) { VCM(void, (void *, void *), 0x280, m); }                     /* slot 158 -> vtable +0x280 */
    u8   pad04[0x0C - 4];
    s32  f0C;
};

typedef struct Slot { s32 f00; s32 f04; s32 f08; s16 f0C; s16 f0E; } Slot;
typedef struct Info { s16 f00; } Info;
typedef struct Obj  { u8 pad00[4]; s16 f04; u8 pad06[0x10 - 6]; Info *f10; } Obj;
typedef struct Cur  { u8 pad00[0x10]; s16 f10; } Cur;
typedef struct Hdl  { u8 pad00[0x14]; s16 f14; s16 f16; u8 pad18[2]; s16 f1A; } Hdl;
typedef struct Root { u8 pad00[0x18]; s32 f18; } Root;
typedef struct Ctx  { u8 pad000[0x44E]; s16 f44E; } Ctx;

extern "C" u8 D_004B2570[];
extern "C" u8 normal_D_005278E0[];
extern "C" Slot     normal_D_00527910[];

extern "C" s16   D_0048051C;          /* gp - 0x4C54 */
extern "C" s32   D_00480500;          /* gp - 0x4C70 */
extern "C" s32   D_00480504;          /* gp - 0x4C6C */
extern "C" s32   D_00480508;          /* gp - 0x4C68 */
extern "C" Ctx  *D_00484454;          /* gp - 0xD1C */
extern "C" void *D_00484498;          /* gp - 0xCD8 */
extern "C" void *D_0048449C;          /* gp - 0xCD4 */
extern "C" void *D_004844A0;          /* gp - 0xCD0 */

extern "C" {

extern void *SoundNextPlayHandle_1b81c0(void);
extern void  SoundPlayScaledVolume_1b9520(void *h, s32 id, void *p, f32 v);
extern void *GameSceneSoundSlot1GetHandle_1d07b0(s32 a);
extern s32   GetCurrentScene_1f5be0(void);
extern Root *GetGameData_1fede0(void);
extern void *SceneSoundGetSlot0HandleCur_207df0(void);
extern void  UiSelFrameSetRect_28db40(const u8 *p, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
extern s32   MenuGridCursorInput_28e170(void *w, const u8 *p, s32 c, s32 d);
extern Hdl  *UiEntryListFindByTag_28ea40(void *w, s32 id);
extern Cur  *UiEntryListGetCurrentData_28ec60(void *w);
extern void  StateMachineSetState_28ede0(void *w, s32 id, s32 a);
extern void  UiSetWidgetPos_290f60(void *w, u16 id, s32 x, s32 y);
extern void  ItemUseMaybe_2eef60(s32 a, void *m, void (*fn)(void *), s32 c, u8 *d);
extern void  ExecInfoInitFromInvItem_3a7430(void *m, s32 a, s16 b, s32 c);
extern void  ExecInfoInit_3a7940(void *m);
extern s32   PartyCountMembers_3c2010(s32 w, s32 a, s32 b);
extern Ent  *PartyGetLeaderChara_3c2820(s32 w);
extern Ent  *PartyGetSlotChara_3c2fb0(s32 w, s32 k);
extern s32   PartyGetSlotId_3c3120(s32 w, s16 k);
extern Obj  *InvFindInCategoryRange_3c8370(s32 w, s32 id, s32 c, s32 d, s32 e, s32 f);
extern s32   ItemGetUseEffectTargetModeMaybe_3d4f00(Obj *o);
extern void  normal_FieldHudItemUseFeedbackSeCb_4f2aa0(void *p);
extern void  normal_FieldHudItemUseSeReset_4f2d40(void);
extern void  normal_BtlChgMenuItemGridLayout_5000b0(void);
extern void  normal_BtlChgMenuItemListBuild_5002f0(void);
extern s32   normal_BtlChgPageGetMember_505f90(void *p);

}

extern "C" s32 normal_BtlChgMenuItemTargetSelectState_4fd920(void)
{
    u8    flag;
    s32   m[0x1B] __attribute__((aligned(16)));
    s32   k;
    Root *t;
    Obj  *o;
    Ent  *v;
    s32   id;
    s16   n;
    Cur  *q;
    s32   r;
    void *h;
    s32   sfx;
    Ent  *e;
    bool  ok;

    r = MenuGridCursorInput_28e170(D_004844A0, D_004B2570, 1, 0);
    q = UiEntryListGetCurrentData_28ec60(D_004844A0);
    if (r == 2) {
        StateMachineSetState_28ede0(D_00484498, 0x5606, 0);
        goto done;
    }
    if (r == 1) {
        t = GetGameData_1fede0();
        if (t == 0) {
            return 0;
        }
        v = PartyGetSlotChara_3c2fb0(t->f18, normal_BtlChgPageGetMember_505f90(D_00484454));
        if (v != 0) {
            o = InvFindInCategoryRange_3c8370(t->f18, normal_D_00527910[D_0048051C].f00, 0, -1, 0, 0);
            if (o != 0) {
                n = o->f04;
                k = o->f10->f00;
                PartyCountMembers_3c2010(t->f18, 1, 1);
                id = -1;
                if (ItemGetUseEffectTargetModeMaybe_3d4f00(o) == 0) {
                    id = PartyGetSlotId_3c3120(t->f18, q->f10);
                }
                ExecInfoInit_3a7940(m);
                ExecInfoInitFromInvItem_3a7430(m, v->f0C, n, 0);
                v->aim(m);
                flag = 0;
                normal_FieldHudItemUseSeReset_4f2d40();
                ItemUseMaybe_2eef60(id, m, normal_FieldHudItemUseFeedbackSeCb_4f2aa0, 0, &flag);
                ok = true;
                if ((u32)(k - 0x40DA) < 6U) {
                    ok = false;
                }
                if (ok) {
                    sfx = GetCurrentScene_1f5be0();
                    if (flag != 0) {
                        h = GameSceneSoundSlot1GetHandle_1d07b0(sfx);
                        SoundPlayScaledVolume_1b9520(h, 0x4A, SoundNextPlayHandle_1b81c0(), 1.0f);
                    } else {
                        h = SceneSoundGetSlot0HandleCur_207df0();
                        SoundPlayScaledVolume_1b9520(h, 6, SoundNextPlayHandle_1b81c0(), 1.0f);
                    }
                }
                normal_BtlChgMenuItemListBuild_5002f0();
                normal_BtlChgMenuItemGridLayout_5000b0();
                if (D_00484454->f44E != 0) {
                    e = PartyGetLeaderChara_3c2820(t->f18);
                    if (e != 0 && e->kind() != 0) {
                        D_00484454->f44E = 0;
                    }
                }
                {
                    Hdl *g = UiEntryListFindByTag_28ea40(D_004844A0, 0x55F3);
                    g->f1A = 0;
                    g->f16 = 0;
                    g->f14 = 0;
                }
                D_00480508 = 0;
                D_00480504 = 0;
                D_00480500 = 0;
                UiSelFrameSetRect_28db40(normal_D_005278E0, 0x28, 0x19, 0x17, 0x2A, 0x30, 0x2B, 0xD1);
                UiSetWidgetPos_290f60(D_0048449C, 0x29, 0x46, 0x46);
                UiSetWidgetPos_290f60(D_0048449C, 0x26, 0x1A, 0x1D);
                UiSetWidgetPos_290f60(D_0048449C, 0x27, 0x3C, 0x37);
                UiSetWidgetPos_290f60(D_0048449C, 0x25, 0x183, 0x1E);
                StateMachineSetState_28ede0(D_00484498, 0x5606, 0);
            }
        }
    }
done:
    return 1;
}
