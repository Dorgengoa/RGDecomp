#include "types.h"

typedef struct S003a59d0 {
    u8 pad0[6];
    s16 unk6;
    s16 unk8;
    s16 unkA;
    u8 padC[4];
    s16 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[4];
    s64 unk20;
    u8 pad28[0x24C - 0x28];
    u8 unk24C;
} S003a59d0;

typedef struct Rec003a59d0 {
    u8 pad0[0x18];
} Rec003a59d0;

typedef struct D004837C0Type {
    u8 pad0[0x18];
    Rec003a59d0 *unk18;
} D004837C0Type;

typedef struct RecFull {
    u8 pad0[0x7E];
    s16 unk7E;
    u8 pad80[2];
    s16 unk82;
} RecFull;

typedef struct Sub003a59d0 {
    s16 unk0;
    u8 pad2[0x14];
    s16 unk16;
    s16 unk18;
} Sub003a59d0;

extern s32 DoubleGreater_100260(s64 arg0, s32 arg1);
extern s64 litodp(s32 arg0);
extern f32 RandFloat_13c010(s16 arg0);
extern void CharaSysEncounterResetMaybe_3a5b10(S003a59d0 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern Sub003a59d0 *PartySelectEncounter_3c9c30(void *arg0);
extern D004837C0Type *D_004837C0;

s64 CharaSysEncounterDistRoll_3a59d0(S003a59d0 *arg0, s32 arg1)
{
    f32 temp_f20;
    s16 temp_17_2;
    s16 temp_4;
    s16 temp_5;
    s64 temp_17;
    Sub003a59d0 *temp_2;
    RecFull *temp_3;

    if (arg1 == 0) {
        temp_17 = arg0->unk20;
        if (DoubleGreater_100260(temp_17, 0) != 0) {
            return temp_17;
        }
    }
    if (arg1 == 0) {
        if ((arg0->unk10 >= 0) || ((arg0->unk14 != 0) || (arg0->unk18 != 0))) return 0;
    }
    if (D_004837C0 == NULL) {
        return 0;
    }
    if (arg0->unk24C & 1) {
        return 0;
    }
    CharaSysEncounterResetMaybe_3a5b10(arg0, 0, 0, 1);
    temp_2 = PartySelectEncounter_3c9c30(D_004837C0->unk18);
    if (temp_2 == NULL) {
        return 0;
    }
    temp_3 = (RecFull *) D_004837C0->unk18;
    temp_4 = temp_3->unk7E;
    temp_5 = temp_3->unk82;
    arg0->unk6 = temp_4;
    arg0->unk8 = temp_5;
    arg0->unkA = temp_2->unk0;
    temp_17_2 = temp_2->unk16;
    temp_f20 = (f32) ((temp_2->unk18 - temp_17_2) + 1);
    arg0->unk20 = litodp(temp_17_2 + (s32) (temp_f20 * RandFloat_13c010(temp_4)));
    return arg0->unk20;
}
