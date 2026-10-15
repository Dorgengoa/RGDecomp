#include "types.h"

typedef struct {
    u8 pad0[0x7E];
    s16 unk7E;
    u8 pad80[0x82 - 0x80];
    s16 unk82;
} Sub18_003A54F0;

typedef struct {
    u8 pad0[8];
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 pade[0x10 - 0xE];
    s16 *unk10;
    u8 pad12[0x40 - 0x14];
    s32 unk40;
} Obj238_003A54F0;

typedef struct {
    u8 pad0[0x24C];
    u8 unk24C;
} Sub20_003A54F0;

typedef struct {
    u8 pad0[0x18];
    Sub18_003A54F0 *unk18;
    u8 pad1c[0x20 - 0x1c];
    Sub20_003A54F0 *unk20;
} Obj18_003A54F0;

typedef struct {
    u8 pad0[4];
    u8 unk4;
    u8 pad8[0x14 - 5];
    s32 unk14;
    u8 pad18[0x238 - 0x18];
    Obj238_003A54F0 *unk238;
} Obj00483897;

s32 CharaSysEncounterSetupMaybe_3a4440(Obj00483897 *, s32, s16, s16, s16, s32);
s32 CharaSysEncounterStartGroupMaybe_3a5010(Obj00483897 *, s16, s16, s16, s32);
void CharaSysEncounterDistRoll_3a59d0(Obj00483897 *, s32);
s16 *PartyGetEncounterRec_3cb040(Sub18_003A54F0 *, s32);
extern Obj18_003A54F0 *D_004837C0;

s32 CharaSysStartQueuedEncounterMaybe_3a54f0(Obj00483897 *arg0)
{
    s16 *p;
    Obj238_003A54F0 *q;
    Sub18_003A54F0 *s;
    s16 a;
    s16 b;
    s16 c;
    s32 r;

    if (D_004837C0 == NULL) {
        return 0;
    }
    if (D_004837C0->unk20->unk24C & 1) {
        return 0;
    }
    if (((u64)((s64)arg0->unk4 << 0x3D) >> 0x3F) == 0) {
        return 0;
    }
    if (arg0->unk14 != 0) {
        q = arg0->unk238;
        r = CharaSysEncounterSetupMaybe_3a4440(arg0, arg0->unk14, q->unkC, q->unk8, q->unkA, 0);
    } else {
        p = PartyGetEncounterRec_3cb040(D_004837C0->unk18, arg0->unk14);
        if (p == NULL) {
            CharaSysEncounterDistRoll_3a59d0(arg0, 1);
            return 0;
        }
        q = arg0->unk238;
        s = D_004837C0->unk18;
        a = s->unk7E;
        b = s->unk82;
        c = *p;
        if (arg0->unk238 != NULL) {
            arg0->unk238->unk8 = a;
            arg0->unk238->unkA = b;
            arg0->unk238->unkC = c;
            arg0->unk238->unk10 = p;
            arg0->unk238->unk40 = 0;
        }
        r = CharaSysEncounterStartGroupMaybe_3a5010(arg0, a, c, b, 0);
        if (r <= 0) {
            CharaSysEncounterDistRoll_3a59d0(arg0, 1);
        }
    }
    return r;
}
