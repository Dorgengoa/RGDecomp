#include "types.h"



typedef struct Self002a25c0 {
    u8 pad[0x5C];
    void *unk0;
} Self002a25c0;

typedef struct Res002a25c0 {
    u8 pad000[0x18];
    void *unk18;
} Res002a25c0;

typedef struct Rec002a25c0 {
    u8 pad000[0x08];
    s64 unk08;
    u8 pad010[0x06];
    s16 unk16;
    s16 unk18;
    u8 pad01A[0x0E];
    s64 unk28;
    u8 pad030[0x06];
    s16 unk36;
    s16 unk38;
    u8 pad03A[0x0E];
    s64 unk48;
    u8 pad050[0x06];
    s16 unk56;
    s16 unk58;
    u8 pad05A[0x0E];
    s64 unk68;
    u8 pad070[0x06];
    s16 unk76;
    s16 unk78;
    u8 pad07A[0x0E];
    s64 unk88;
    u8 pad090[0x06];
    s16 unk96;
    s16 unk98;
    u8 pad09A[0x0E];
    s64 unkA8;
    u8 pad0B0[0x06];
    s16 unkB6;
    s16 unkB8;
} Rec002a25c0;

class V002a25c0 {
public:
     VC_VPTR_MEMBER;
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     s32 slot0E8() { return VCM0(s32, 0xE8); }
     
     s32 slot0F0() { return VCM0(s32, 0xF0); }
     
     
     
     
     
     
     s32 slot10C() { return VCM0(s32, 0x10C); }
     
     
     
     
     
     
     s32 slot128(s32 a) { return VCM(s32, (void *, s32), 0x128, a); }
     
     s32 slot130(s32 a) { return VCM(s32, (void *, s32), 0x130, a); }
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     s32 slot420() { return VCM0(s32, 0x420); }
};

extern "C" Res002a25c0 *GetGameData_1fede0();
extern "C" s32 PartyCountMembers_3c2010(void *, s32, s32);
struct Item { u8 pad[0x24]; Rec002a25c0 *rec; };
extern "C" Item *UiFindWidget_290460(void *, u16);
extern "C" V002a25c0 *PartyGetMemberChara_3c2420(void *, s32);

extern "C" s32 MenuTacticsMemberStatValues_356d50(Self002a25c0 *self, s32 arg1)
{
    u32 j;
    s32 n;
    u16 base;
    s32 i;
    Res002a25c0 *r;
    Rec002a25c0 *e;
    V002a25c0 *o;
    Item *it;

    r = GetGameData_1fede0();
    n = PartyCountMembers_3c2010(r->unk18, 1, 1);
    base = (u16)arg1;
    for (i = 0; i < 3; i++) {
        it = UiFindWidget_290460(self->unk0,(u16)(base+i));
        if(it==0) continue;
        e=it->rec;
        if (e == 0) {
            continue;
        }
        e->unk18 = 0;
        e->unk16 = 0;
        e->unk38 = 0;
        e->unk36 = 0;
        e->unk58 = 0;
        e->unk56 = 0;
        e->unk78 = 0;
        e->unk76 = 0;
        e->unk98 = 0;
        e->unk96 = 0;
        e->unkB8 = 0;
        e->unkB6 = 0;
    }
    for (j = 0; (s32)j < (s32)n; j++) {
        it = UiFindWidget_290460(self->unk0,(u16)(base+j));
        if(it==0) continue;
        e=it->rec;
        if (e == 0) {
            continue;
        }
        o = PartyGetMemberChara_3c2420(r->unk18, j);
        if (o == 0) {
            continue;
        }

        e->unk08 = (s64)o->slot0F0();
        e->unk16 = 0xC;
        e->unk18 = 0xF;

        e->unk28 = (s64)o->slot10C();
        e->unk36 = 0xC;
        e->unk38 = 0xF;

        e->unk48 = (s64)o->slot420();
        e->unk56 = 0xC;
        e->unk58 = 0xF;

        e->unk68 = (s64)o->slot0E8();
        e->unk76 = 0xC;
        e->unk78 = 0xF;

        e->unk88 = (s64)o->slot128(1);
        e->unk96 = 0xA;
        e->unk98 = 0xC;

        e->unkA8 = (s64)o->slot130(1);
        e->unkB6 = 0xA;
        e->unkB8 = 0xC;
    }
    return 1;
}
