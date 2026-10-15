#include "types.h"

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
} E003D8580;

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
    s32 unk18;
} D003D8580;

extern void VariantSetS32_36f040(s32, s32, s32);
extern s32 VariantGetS16_36fcc0(s32);
extern E003D8580 *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
extern u8 CharaIsInReserve_3ae0e0(E003D8580 *);
extern void CharaSetFlag234Bit2Related_3ae370(E003D8580 *, s32);
extern s32 PartySwapMembers_3c0ad0(s32, s32, s32, s32, s32);
extern D003D8580 *D_00483960;
extern s32 D_00483964;

void ScriptFnPartySwapByKind_3d8580(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    E003D8580 *e1;
    s32 b;
    s32 k1;
    E003D8580 *e2;
    s32 a;
    s32 k2;
    u8 f;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 < 2) {
        return;
    }
    a = (s16)VariantGetS16_36fcc0(arg3);
    b = (s16)VariantGetS16_36fcc0(arg3 + 0x38);
    e1 = CharaMgrPoolFindByDataId_3a8a70(D_00483960->unk14, a, 1, 1, 0, 0, 0);
    if (e1 == NULL) {
        return;
    }
    k1 = e1->unkC;
    e2 = CharaMgrPoolFindByDataId_3a8a70(D_00483960->unk14, b, 1, 1, 0, 0, 0);
    if (e2 == NULL) {
        return;
    }
    k2 = e2->unkC;
    f = CharaIsInReserve_3ae0e0(e1);
    if (f != CharaIsInReserve_3ae0e0(e2)) {
        CharaSetFlag234Bit2Related_3ae370(e1, 0);
        CharaSetFlag234Bit2Related_3ae370(e2, 0);
    }
    VariantSetS32_36f040(arg0, PartySwapMembers_3c0ad0(D_00483960->unk18, k1, k2, 1, 0) != 0, 1);
}
