#include "types.h"

union Val003d8d30 {
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

typedef struct Var003d8d30 {
    s32 tag;
    u8 pad004[0x4];
    union Val003d8d30 u;
} Var003d8d30;

typedef struct Reg003d8d30 {
    u8 pad00[0x10];
    s32 unk10;
} Reg003d8d30;

extern Reg003d8d30 *D_00483960;
extern s32 D_00483964;

extern void VariantSetS32_36f040(s32 a0, s32 a1, s32 a2);
extern s32 VariantGetS32_36fb30(Var003d8d30 *p0);
extern s16 VariantGetS16_36fcc0(Var003d8d30 *p0);
extern s32 ProgressSetByCode_3ccf10(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

void ScriptFnProgressSetByCode_3d8d30(s32 self, s32 unused, s32 count, Var003d8d30 *arg3)
{
    s32 id;

    if (self == 0) {
        return;
    }
    VariantSetS32_36f040(self, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0) {
        return;
    }
    if (arg3 == 0 || count < 2) {
        return;
    }
    id = VariantGetS32_36fb30(arg3);
    VariantSetS32_36f040(self, ProgressSetByCode_3ccf10(D_00483960->unk10, id, VariantGetS16_36fcc0((Var003d8d30 *)((u8 *)arg3 + 0x38)), 1, 1) & 0xFF, 1);
}
