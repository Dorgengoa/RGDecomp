/* rgp:protos */
#define RGP_SELF_MapAreaApplyDef_1dc9f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 unk0;
    u8 pad2[6];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s16 unk20;
    u8 pad22[4];
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 pad2B;
    s16 unk2C;
} Src;

typedef struct {
    u8 pad0[0x54];
    u8 unk54[0x24];
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    u8 *unk84;
    s16 unk88;
    s16 unk8A;
} Dst;

extern void Sprintf_1343b8(void *, void *, s32, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0044B350[];
extern u8 D_0044B364[];
extern u8 D_0044B378[];
extern u8 D_0045B380[];

void MapAreaApplyDef_1dc9f0(Dst *arg0, Src *arg1, s32 arg2)
{
    if (arg1 == NULL) {
        return;
    }
    MapDataSetId_1e74e0(arg0, arg1->unk0);
    MapDataSetName_1e7500(arg0, arg1->unk14);
    MapDataSetFileName_1e74f0(arg0, arg1->unk14);
    MapDataSetMemFncFlags_1e74c0(arg0, arg1->unk8);
    if (arg1->unk26 & 1) {
        MapDataSetColor_1e72d0(arg0, arg1->unk27, arg1->unk28, arg1->unk29, arg1->unk2A);
    }
    Sprintf_1343b8(arg0->unk54, D_0045B380, arg2, arg1->unk10);
    arg0->unk78 = arg1->unkC;
    arg0->unk7C = arg1->unk18;
    arg0->unk80 = arg1->unk1C;
    arg0->unk88 = arg1->unk2C;
    arg0->unk8A = arg1->unk20;
    switch (arg1->unk2C) {
    case 2:
        arg0->unk84 = D_0044B350;
        break;
    case 3:
        arg0->unk84 = D_0044B364;
        break;
    }
    if (((short)MapDataGetId_1e7bd0(arg0)) == 1200) {
        arg0->unk84 = D_0044B378;
    }
}
