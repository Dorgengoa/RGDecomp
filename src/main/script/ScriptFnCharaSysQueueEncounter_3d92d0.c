#include "types.h"

/* s44g clone pair (ScriptFnPartySetActiveCount_3d84d0 / ScriptFnCharaSysQueueEncounter_3d92d0). MATCH.

   Identical shape to ScriptFnPartySetActiveCount_3d84d0.c -- see that file's header for the
   guard-grouping levers. Differences from the pair partner: the global
   registry field read is ->unk20 (not ->unk18) and the tail callee is
   CharaSysQueueEncounter_3a5730 (not PartySetActiveCount_3c1ec0). */

union Val003d92d0 {
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

typedef struct Var003d92d0 {
    s32 tag;
    u8 pad004[0x4];
    union Val003d92d0 u;
} Var003d92d0;

typedef struct Reg003d92d0 {
    u8 pad00[0x20];
    s32 unk20;
} Reg003d92d0;

extern Reg003d92d0 *D_00483960;
extern s32 D_00483964;

extern void VariantSetS32_36f040(s32 a0, s32 a1, s32 a2);
extern s16 VariantGetS16_36fcc0(Var003d92d0 *p0);
extern s32 CharaSysQueueEncounter_3a5730(s32 a0, s32 a1);

void ScriptFnCharaSysQueueEncounter_3d92d0(s32 self, s32 unused, s32 count, Var003d92d0 *arg3)
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
    VariantSetS32_36f040(self, CharaSysQueueEncounter_3a5730(D_00483960->unk20, id) & 0xFF, 1);
}
