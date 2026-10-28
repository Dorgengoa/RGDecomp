/* rgp:protos */
#define RGP_SELF_HeadLookInit_1c5c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[0x3C - 0x2C];
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    u8 pad48[0x60 - 0x48];
    s16 unk60;
    u8 pad62[0x70 - 0x62];
} Obj001C5C50;

typedef struct {
    u8 pad0[0x2C];
    s32 unk2C;
} Elem001C5C50;

void HeadLookInit_1c5c50(Obj001C5C50 *arg0) {
    s32 i;
    Elem001C5C50 *p;

    arg0->unk3C = 2;
    arg0->unk3E = 0;
    arg0->unk44 = 0;
    arg0->unk28 = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0x3F800000;
    arg0->unk10 = 0;
    arg0->unk14 = 0;
    arg0->unk18 = 0;
    arg0->unk1C = 0x3F800000;
    i = 0;
    do {
        p = (Elem001C5C50 *)((u8 *)arg0 + (i * 4));
        i += 1;
        p->unk2C = 0x41000000;
    } while (i < 4);
    arg0->unk42 = 0;
    arg0->unk40 = 0;
    arg0->unk44 = 0;
    arg0->unk46 = -1;
    *(u128 *)((u8 *)arg0 + 0x70) = *(u128 *)((u8 *)arg0 + 0x0);
    arg0->unk60 = 0;
}
