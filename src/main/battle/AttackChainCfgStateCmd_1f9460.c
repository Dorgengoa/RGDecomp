/* MATCH (s41m). Stale pre-match note follows -- PARKED s17b: type-tagged-value float getter + AttackChainAddState_382cf0 call. 1 round
   trip: 133 words, 39/133 bad (compiles, right length). Residue not yet
   isolated -- likely one of the four tag-switch blocks (unk10/14, unk18/1c,
   unk20/24, unk28/2c) has the wrong int<->float reinterpret-vs-convert
   shape, or the strcmp flag chain's word order. */
#include "types.h"

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F32(p, o) (*(f32 *)((u8 *)(p) + (o)))

typedef struct {
    s32 unk0;
    s8 *unk4;
    u8 pad8[8];
    s32 unk10;
    f32 unk14;
    s32 unk18;
    f32 unk1C;
    s32 unk20;
    f32 unk24;
    s32 unk28;
    f32 unk2C;
} S1;

extern s32 strcmp(const s8 *, const s8 *);
extern s32 AttackChainAddState_382cf0(void *, s32, f32, f32, f32, f32);
extern s8 D_0045BD00[];
extern s8 D_0045BD08[];
extern s8 D_0045BD10[];
extern s8 D_0045BD18[];
extern s32 D_0047E4B4;
extern s32 D_0047E4B8;
extern s32 D_0047E4BC;
extern s32 D_0047E4C0;
extern u8 D_004B86C0[];

s32 AttackChainCfgStateCmd_1f9460(S1 *arg0, s32 arg1)
{
    s32 flags;
    f32 f12;
    f32 f13;
    f32 f14;
    f32 f15;
    s8 *name;

    if (arg1 < 4) {
        return 0;
    }
    if ((D_0047E4B4 != D_0047E4BC) || (D_0047E4B8 != D_0047E4C0)) return 1;

    if (arg0->unk0 != 0) {
        name = NULL;
    } else {
        name = arg0->unk4;
    }
    flags = 0x40;
    if ((name != NULL) && (*name != 0)) {
        if (strcmp(name, D_0045BD00) == 0) {
            flags = 0x20;
        }
        if (strcmp(name, D_0045BD08) == 0) {
            flags = 0x40;
        }
        if (strcmp(name, D_0045BD10) == 0) {
            flags = 0x80;
        }
        if (strcmp(name, D_0045BD18) == 0) {
            flags = 0x10;
        }
    }

    f14 = -1.0f;
    f15 = -1.0f;
    if (arg1 >= 6) {
        switch (arg0->unk20) {
        case 1:
            f14 = (f32)S32(arg0, 0x24);
            break;
        case 2:
            f14 = arg0->unk24;
            break;
        default:
            f14 = 0.0f;
            break;
        }

        switch (arg0->unk28) {
        case 1:
            f15 = (f32)S32(arg0, 0x2C);
            break;
        case 2:
            f15 = arg0->unk2C;
            break;
        default:
            f15 = 0.0f;
            break;
        }
    }

    switch (arg0->unk10) {
    case 1:
        f12 = (f32)S32(arg0, 0x14);
        break;
    case 2:
        f12 = arg0->unk14;
        break;
    default:
        f12 = 0.0f;
        break;
    }

    switch (arg0->unk18) {
    case 1:
        f13 = (f32)S32(arg0, 0x1C);
        break;
    case 2:
        f13 = arg0->unk1C;
        break;
    default:
        f13 = 0.0f;
        break;
    }

    if (f13 <= 0.0f) {
        f13 = 8.0f + f12;
    }

    AttackChainAddState_382cf0(D_004B86C0, flags, f12, f13, f14, f15);
    return 1;
}
