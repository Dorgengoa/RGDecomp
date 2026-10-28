/* rgp:protos */
#line 1
#include "types.h"

struct Sub162 {
    u8 pad0[4];
    s16 x4;
};

struct Rec {
    s8 unk0;
    s8 unk1;
    s8 unk2;
    s8 unk3;
    Sub162 *unk4;
    Sub162 *unk8;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    f32 unk20;
    f32 unk24;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s8 unk30;
    s8 unk31;
    s8 unk32;
    u8 unk33;
    u8 unk34[4];
};

extern "C" u8 * TexAnimSeqNewKey_162d00(s32, s8, int);

extern "C" s32 TexAnimSeqAddKey_162b70(s32 arg0, Rec *arg1, int rgp_a2)
{
    u8 *p;
    Rec *r;

    p = TexAnimSeqNewKey_162d00(arg0, arg1->unk1, (int)rgp_a2);
    if (p == NULL) {
        return 0;
    }
    r = (Rec *)(p + 0x10);
    if (r == NULL) {
        return 0;
    }
    *r = *arg1;
    if (r->unk4 != NULL && r->unk8 != NULL) {
        r->unkE = r->unk4->x4 * 16 - arg1->unkE - arg1->unk12;
        r->unk16 = r->unk8->x4 * 16 - arg1->unk16 - arg1->unk1A;
    }
    return 1;
}
