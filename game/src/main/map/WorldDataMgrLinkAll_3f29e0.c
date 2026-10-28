/* rgp:protos */
#define RGP_SELF_WorldDataMgrLinkAll_3f29e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub Sub;
struct Sub {
    u8 pad0[0x2C];
    s32 unk2C;
    u8 pad30[0x34 - 0x30];
    s32 unk34;
};

typedef struct {
    u8 pad0[0x4];
    Sub *unk4;
    u8 pad8[0x34 - 0x8];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    u8 pad88[0xAC - 0x88];
    s32 unkAC;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldDataMgrLinkAll_3f29e0(Obj *arg0, int rgp_a1, int rgp_a2, int rgp_a3) {
    s32 temp_16;
    s32 temp_4;
    s32 temp_4_2;
    s32 temp_4_3;
    s32 temp_4_4;
    s32 temp_4_5;
    s32 temp_4_6;
    s32 temp_4_7;
    s32 temp_4_8;
    s32 temp_4_9;
    s32 temp_4_10;
    s32 temp_4_11;
    s32 temp_4_12;
    s32 temp_4_13;
    s32 temp_4_14;
    s32 temp_4_15;
    s32 temp_4_16;
    s32 temp_4_17;
    s32 temp_4_18;
    s32 temp_4_19;
    s32 temp_4_20;
    s32 temp_4_21;
    Sub *temp_2;
    Sub *temp_4_22;

    temp_2 = arg0->unk4;
    temp_4 = arg0->unk34;
    temp_16 = temp_2->unk34 - temp_2->unk2C;
    if (temp_4 != 0) {
        WorldSubsysLinkAll_411d10(temp_4, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    }
    temp_4_2 = arg0->unk38;
    if (temp_4_2 != 0) {
        WorldSubsysLinkAllNop_405470();
    }
    temp_4_3 = arg0->unk3C;
    if (temp_4_3 != 0) {
        WorldSubsysLinkAllNop_428550();
    }
    temp_4_4 = arg0->unk40;
    if (temp_4_4 != 0) {
        WorldSubsysLinkAll_40c530(temp_4_4, 0, 0, 0);
    }
    temp_4_5 = arg0->unk44;
    if (temp_4_5 != 0) {
        WorldSubsysLinkAll_3f4360(temp_4_5, 0, 0, 0);
    }
    temp_4_6 = arg0->unk48;
    if (temp_4_6 != 0) {
        WorldSubsysLinkAll_3f9e60(temp_4_6, 0, 0, 0);
    }
    temp_4_7 = arg0->unk4C;
    if (temp_4_7 != 0) {
        WorldSubsysLinkAll_3fc2f0(temp_4_7, 0, 0, 0);
    }
    temp_4_8 = arg0->unk50;
    if (temp_4_8 != 0) {
        WorldSubsysLinkAllNop_3f7fa0();
    }
    temp_4_9 = arg0->unk54;
    if (temp_4_9 != 0) {
        WorldSubsysLinkAll_3f92e0(temp_4_9, 0, 0, 0);
    }
    temp_4_10 = arg0->unk58;
    if (temp_4_10 != 0) {
        WorldSubsysLinkAll_3fe2b0(temp_4_10, 0, 0, 0);
    }
    temp_4_11 = arg0->unk5C;
    if (temp_4_11 != 0) {
        WorldSubsysLinkAllNop_429400();
    }
    temp_4_12 = arg0->unk60;
    if (temp_4_12 != 0) {
        WorldSubsysLinkAll_400470(temp_4_12, 0, 0, 0);
    }
    temp_4_13 = arg0->unk64;
    if (temp_4_13 != 0) {
        WorldSubsysLinkAll_4199e0(temp_4_13, 0, 0, 0);
    }
    temp_4_14 = arg0->unk68;
    if (temp_4_14 != 0) {
        WorldSubsysLinkAll_40a490(temp_4_14);
    }
    temp_4_15 = arg0->unk6C;
    if (temp_4_15 != 0) {
        WorldSubsysLinkAllNop_41c610();
    }
    temp_4_16 = arg0->unk70;
    if (temp_4_16 != 0) {
        WorldSubsysLinkAll_402540(temp_4_16, 0, 0, 0);
    }
    temp_4_17 = arg0->unk74;
    if (temp_4_17 != 0) {
        WorldSubsysLinkAllNop_425940();
    }
    temp_4_18 = arg0->unk78;
    if (temp_4_18 != 0) {
        WorldSubsysLinkAllNop_427120();
    }
    temp_4_19 = arg0->unk7C;
    if (temp_4_19 != 0) {
        WorldSubsysLinkAllNop_41ff20();
    }
    temp_4_20 = arg0->unk80;
    if (temp_4_20 != 0) {
        WorldSubsysLinkAllNop_41e540();
    }
    temp_4_21 = arg0->unk84;
    if (temp_4_21 != 0) {
        WorldSubsysLinkAll_40eec0(temp_4_21, 0, 0, 0);
    }
    temp_4_22 = arg0->unk4;
    arg0->unkAC = arg0->unkAC + (temp_16 - (temp_4_22->unk34 - temp_4_22->unk2C));
    return 1;
}
