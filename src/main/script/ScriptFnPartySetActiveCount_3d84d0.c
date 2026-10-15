#include "types.h"

/* s44g clone pair (ScriptFnPartySetActiveCount_3d84d0 / ScriptFnCharaSysQueueEncounter_3d92d0).

   Same guard-grouping family as ScriptFnCharaSetCannotLeadMaybe_3d6960.c / ScriptFnCharaSetFlag234Related_3d83e0.c (see
   that file's header): the four early-return guards must be grouped as
   two `||` pairs -- (D_00483960==0 || D_00483964==0) and
   (arg3==0 || count<=0) -- for their SECOND terms to buy retail's
   expensive shapes (an inverted-branch+jump for the D_00483964 term, a
   branch-likely-with-duplicated-continuation for the count<=0 term;
   retail's own object keeps the resulting dead orphan `daddu` at
   003D8534). Unlike the other pair, arg3 here is used directly as the
   `Var` passed to VariantGetS16_36fcc0 with no second Var at +0x38. */

union Val003d84d0 {
    s8 vs8;
    u8 vu8;
    s16 vs16;
    u16 vu16;
    s32 vs32;
    u32 vu32;
    s64 vs64;
    u64 vu64;
    f32 vf32;
};

typedef struct Var003d84d0 {
    s32 tag;
    u8 pad004[0x4];
    union Val003d84d0 u;
} Var003d84d0;

typedef struct Reg003d84d0 {
    u8 pad00[0x18];
    s32 unk18;
} Reg003d84d0;

extern Reg003d84d0 *D_00483960;
extern s32 D_00483964;

extern void VariantSetS32_36f040(s32 a0, s32 a1, s32 a2);
extern s16 VariantGetS16_36fcc0(Var003d84d0 *p0);
extern s32 PartySetActiveCount_3c1ec0(s32 a0, s32 a1);

void ScriptFnPartySetActiveCount_3d84d0(s32 self, s32 unused, s32 count, Var003d84d0 *arg3)
{
    s32 id;

    if (self == 0) {
        return;
    }
    VariantSetS32_36f040(self, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || count <= 0) {
        return;
    }
    id = VariantGetS16_36fcc0(arg3);
    VariantSetS32_36f040(self, PartySetActiveCount_3c1ec0(D_00483960->unk18, id) & 0xFF, 1);
}
