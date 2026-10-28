/* rgp:protos */
#define RGP_SELF_EffectResCreateHandle_2e0f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R002e0f10 {
    s16 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} R002e0f10;

typedef struct Elem002e0f10 {
    u8 pad0[0x174];
    s32 unk174;
    s32 unk178;
    u8 pad17C[0x1D0 - 0x17C];
    s32 unk1D0;
    u8 pad1D4[0x1E0 - 0x1D4];
} Elem002e0f10;

typedef struct A2_002e0f10 {
    u8 pad0[4];
    s32 unk4;
    s32 unk8;
} A2_002e0f10;

/*rgp*/

void EffectResCreateHandle_2e0f10(R002e0f10 *out, u8 *arg1, A2_002e0f10 *arg2)
{
    R002e0f10 r __attribute__((aligned(16)));
    s32 sp6C;
    s32 i;
    s32 x;
    Elem002e0f10 *e;

    i = arg2->unk4;
    if (i < 0 || i >= 48) {
        r.unk0 = 1;
        r.unk8 = -1;
        r.unkC = 0;
        out->unk0 = r.unk0;
    out->unk4 = r.unk4;
    out->unk8 = r.unk8;
    out->unkC = r.unkC;
    out->unk10 = r.unk10;
    return;
    }
    e = (Elem002e0f10 *)((u8 *)(i * 0x70) + (u32)arg1);
    if (e->unk1D0 != 1) {
        r.unk0 = 1;
        r.unk8 = -1;
        r.unkC = 0;
        out->unk0 = r.unk0;
    out->unk4 = r.unk4;
    out->unk8 = r.unk8;
    out->unkC = r.unkC;
    out->unk10 = r.unk10;
    return;
    }
    if (e->unk174 < 0) {
        r.unk0 = 1;
        r.unk8 = -1;
        r.unkC = 0;
        out->unk0 = r.unk0;
    out->unk4 = r.unk4;
    out->unk8 = r.unk8;
    out->unkC = r.unkC;
    out->unk10 = r.unk10;
    return;
    }
    EffTableCreateInstance_1a0df0(&sp6C, arg1 + 0x58, e->unk178, 0);
    x = sp6C;
    arg2->unk8 = x;
    r.unk0 = 1;
    r.unk8 = arg2->unk4;
    r.unkC = x;
    out->unk0 = r.unk0;
    out->unk4 = r.unk4;
    out->unk8 = r.unk8;
    out->unkC = r.unkC;
    out->unk10 = r.unk10;
    return;
}
