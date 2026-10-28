/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x004F7EA0 -- C++ virtual dispatch, vptr at +0x1B0, slots 0x44, 0x50
 * and 0x5C = virtuals #15, #18 and #21.  [[jalr-is-cpp-virtual]]
 *
 * jalr.json calls this "vptr 0x1B0 + 0xA40 + 0x11D0" but there is only ONE
 * class: 0x890 + 0x1B0 == 0xA40 and 0x1020 + 0x1B0 == 0x11D0, so both extra
 * offsets are sub-objects whose base mwcc folded into the vptr load's
 * displacement.
 *
 * Five-arm `insect_InsectBattleGetStep_50d6a0(o, 1)` dispatch, chain 0xB, 0xA, 0x30, 0x2F, 1
 * with `beql`/`beq` INTO each arm, so the source order is the REVERSE
 * 1, 0x2F, 0x30, 0xA, 0xB -- and cases 0xA and 0xB have EMPTY bodies.
 *
 * `addiu $6,$0,0x1` at 0x004F7F58 serves BOTH the `beql $16,$6` compare for the
 * inner `case 1` and the literal `1` argument inside that arm -- the
 * compare-chain-constant-in-an-argument-register lever.
 */

class VE {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;  
      
      
      
      
    void s15(f32 a) { VCM(void, (void *, f32), 0x44, a); }          /* slot 0x44 */
    void s16() { VCM0(void, 0x48); } 
    void s18() { VCM0(void, 0x50); }               /* slot 0x50 */
     
    void s21() { VCM0(void, 0x5C); }               /* slot 0x5C */
};

struct Desc {
    void *f00;
    void *f04;
    void *f08;
    void *f0C;
    void *f10;
    s32   f14;
    s32   f18;
    u8    pad1C[0x2C - 0x1C];
    void *f2C;
    s32   f30;
    u8    pad34[4];
    void *f38;
    s32   f3C;
    u8    b40[0x20];
    u8    b60[0x30];
};

struct Ent {
    u8  pad000[0x38];
    s8  f38;                        /* +0x38 */
    s8  f39;                        /* +0x39 */
    u8  pad03A[0xDC - 0x3A];
    s16 fDC;                        /* +0xDC */
};

struct W {
    u8 pad000[0x1E4];
    u8 f1E4[4];                     /* +0x1E4 */
};

struct O {
    u8    pad000[0x138];
    u8    f138[0x884 - 0x138];      /* +0x0138 */
    void *f884;                     /* +0x0884 */
    u8    pad888[0x5000 - 0x888];
    u8    f5000[0x20];              /* +0x5000 */
};

extern "C" u8 insect_D_00524C78[];
extern "C" u8 insect_D_00524C88[];
extern "C" u8 insect_D_00524C90[];
extern "C" u8 insect_D_00524C98[];
extern "C" u8 insect_D_00524CA0[];

extern "C" void  memset(void *d, s32 c, s32 n);
extern "C" void  Sprintf_1343b8(void *d, const u8 *t, s32 v);
extern "C" void  strcpy(void *d, const u8 *s);
extern "C" u32   strlen(const u8 *s);
extern "C" void  MemStackInit_14d810(u8 *p, void *r, s32 n);
extern "C" void  MemStackReset_14d830(u8 *p);
extern "C" void *MemStackAllocQw_14d950(u8 *p, s32 n);
extern "C" void  MemStackReturnToOwnerMaybe_14dad0(u8 *p);
extern "C" void  MemStackHeapAlloc_14db10(u8 *p, s32 a, s32 b, s32 c);
extern "C" void  MemStackHeapReinit_14de90(u8 *p);
extern "C" void  MemStackClear_14dff0(u8 *p);
extern "C" W    *GetDrawCtxNameTable_15de40(void);
extern "C" void  ModelObjPlayMotionByName_1867a0(u8 *m, void *t, s32 k);
extern "C" void  InfoCfgParseAll_1afd00(void *m, Desc *d);
extern "C" void  ModelObjExCopy_1aff40(void *a, u8 *b, u8 *c);
extern "C" s32   insect_InsectBattleGetStep_50d6a0(O *o, s32 k);
extern "C" void  insect_InsectBattleSetStep_50d7a0(O *o, s32 a, s32 b, s32 c);
extern "C" void  insect_InsectBattleSetState_50d8c0(O *o, s32 a, s32 b, s32 c);
extern "C" void  insect_InsectBattleSetFlag_50dad0(O *o, s32 k);
extern "C" void  insect_InsectBattlePieceApplyColor_50fa30(u8 *m, Ent *p);
extern "C" void  insect_InsectBattlePieceSetDesignVisible_50fa80(u8 *m, Ent *p, s32 k);
extern "C" void *insect_InsectFileSlotGetData_511fa0(u8 *p, s32 *out);
extern "C" s32   insect_InsectFileSlotIsLoaded_512010(u8 *p);
extern "C" void  insect_InsectFileSlotRelease_512020(u8 *p);
extern "C" void  insect_InsectFileSlotRequest_512140(u8 *p, void *t, s32 k);
extern "C" void  insect_InsectPieceSetBaseMotion_5153e0(Ent *p, s32 a, s32 b, s8 c, void *e);

extern "C" void insect_InsectBattleLoadPreviewModel_4f7ea0(O *o, s32 mode)
{
    s32   q;
    u8    buf[0x1C] __attribute__((aligned(16)));
    Desc  d __attribute__((aligned(16)));
    Ent  *s;
    u8   *t138;
    u8   *t818;
    u8   *t890;
    u8   *t1020;
    u8   *x138;
    u8   *x1020;
    void *p;
    void *r;
    W    *w;
    s32   v;

    s = (Ent *)((u8 *)o + 0x5B30);

    switch (insect_InsectBattleGetStep_50d6a0(o, 1)) {
    case 1:
        t138 = (u8 *)o + 0x138;
        t818 = (u8 *)o + 0x818;
        ((VE *)((u8 *)o + 0x890))->s21();
        ((VE *)((s32)o + 0x890))->s18();
        ((VE *)((u8 *)o + 0x1020))->s21();
        ((VE *)((s32)o + 0x1020))->s18();
        switch (mode) {
        case 0:
            MemStackHeapReinit_14de90(t138);
            MemStackHeapAlloc_14db10(t138, 2, 0, 0x40);
            MemStackClear_14dff0(t818);
            r = MemStackAllocQw_14d950(t138, 0x3FC0);
            MemStackInit_14d810(t818, r, 0x3FC0);
            if (strlen(insect_D_00524C90) < 0x10) {
                strcpy(t818, insect_D_00524C90);
            }
            MemStackReset_14d830(t818);
            MemStackReturnToOwnerMaybe_14dad0(t138);
            v = s->fDC;
            if (s->f38 == 0x11) {
                v = 0x13E;
            }
            Sprintf_1343b8(buf, insect_D_00524C88, v);
            insect_InsectFileSlotRequest_512140(o->f5000, buf, 2);
            insect_InsectBattleSetStep_50d7a0(o, 0x2F, 1, -1);
            break;
        case 1:
            insect_InsectBattleSetStep_50d7a0(o, 0x30, 1, -1);
            break;
        }
        break;
    case 0x2F:
        if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
            t890 = (u8 *)o + 0x890;
            t818 = (u8 *)o + 0x818;
            p = insect_InsectFileSlotGetData_511fa0(o->f5000, &q);
            memset(&d, 0, 0x88);
            d.f2C = d.b40;
            d.f30 = 8;
            d.f3C = 8;
            d.f38 = d.b60;
            d.f00 = p;
            d.f04 = insect_D_00524C78;
            d.f14 = 0x29D;
            d.f08 = t818;
            d.f0C = t818;
            d.f10 = t818;
            d.f18 = 0;
            w = GetDrawCtxNameTable_15de40();
            strcpy(w->f1E4, insect_D_00524C98);
            ((VE *)t890)->s21();
            InfoCfgParseAll_1afd00(t890, &d);
            w->f1E4[0] = 0;
            insect_InsectFileSlotRelease_512020(o->f5000);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 1, -1);
            insect_InsectBattlePieceSetDesignVisible_50fa80(t890, s, 0);
            insect_InsectPieceSetBaseMotion_5153e0(s, 0, 4, s->f39, t890);
            ((VE *)t890)->s15(1.0f);
            *(s32 *)(t890 + 0x448) = 0;
            insect_InsectBattlePieceApplyColor_50fa30(t890, s);
        }
        break;
    case 0x30:
        x138 = (u8 *)o + 0x138;
        x1020 = (u8 *)o + 0x1020;
        MemStackHeapReinit_14de90(x138);
        MemStackHeapAlloc_14db10(x138, 2, 0, 0x40);
        ((VE *)x1020)->s21();
        ((VE *)x1020)->s18();
        ModelObjExCopy_1aff40(o->f884, x1020, x138);
        MemStackReturnToOwnerMaybe_14dad0(x138);
        ModelObjPlayMotionByName_1867a0(x1020, insect_D_00524CA0, 4);
        ((VE *)x1020)->s15(1.0f);
        insect_InsectBattleSetFlag_50dad0(o, 0x1B);
        insect_InsectBattleSetState_50d8c0(o, 0x1C, 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xB, 1, -1);
        break;
    case 0xA:
        break;
    case 0xB:
        break;
    }
}
