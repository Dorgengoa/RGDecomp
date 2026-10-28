/* rgp:protos */
#define RGP_SELF_WorldSubsysSetupRankingRecs_3fd160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Table003fd160 {
    u8 pad0[0x7C];
    s16 unk7C;
    u8 pad7E[0x8C - 0x7E - 2];
    s32 unk8C;
} Table003fd160;

typedef struct Rec003fd160 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s16 unkC;
    s16 unkE;
    s16 unk10;
} Rec003fd160;

typedef struct Outer003fd160 {
    u8 pad0[0x10];
    s32 unk10;
    Rec003fd160 *unk14;
} Outer003fd160;

typedef struct S003fd160 {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[8];
    Table003fd160 *unk10;
    Outer003fd160 *unk14;
} S003fd160;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldSubsysSetupRankingRecs_3fd160(S003fd160 *arg0)
{
    Rec003fd160 *var_6;
    Table003fd160 *temp_4;
    Outer003fd160 *temp_2_2;
    Table003fd160 *temp_2;
    s32 var_5;
    s32 var_2;
    s32 var_16;

    temp_2 = arg0->unk10;
    var_16 = 0;
    if (temp_2 != NULL) {
        var_16 = temp_2->unk7C;
    }
    temp_2_2 = ((Outer003fd160 *)MemStackNew_14e130(0x18, arg0->unk4));
    if (temp_2_2 != NULL) {
        RankingHolderClear_3fdac0(temp_2_2);
    }
    arg0->unk14 = temp_2_2;
    if (temp_2_2 != NULL) {
        RankingHolderClear_3fdac0(temp_2_2);
        arg0->unk14->unk10 = (s32) var_16;
        arg0->unk14->unk14 = (Rec003fd160 *) ConstructNewArray_100710(((s32)MemStackNew_14e0b0((var_16 * 0x14) + 0x10, arg0->unk4)), (void *)RankingEntryCtor_3fd2a0, 0, 0x14, (s32) var_16);
        var_6 = arg0->unk14->unk14;
        var_5 = 0;
        while (var_5 < var_16) {
            temp_4 = arg0->unk10;
            if (var_5 >= 0) {
                if (var_5 >= temp_4->unk7C) {
                    var_2 = 0;
                } else {
                    var_2 = temp_4->unk8C + (var_5 * 0x14);
                }
            } else {
                var_2 = 0;
            }
            var_6->unk0 = var_2;
            var_5 += 1;
            var_6->unk4 = -1;
            var_6->unk8 = -1;
            var_6->unkC = -1;
            var_6->unkE = -1;
            var_6->unk10 = 0;
            var_6 = (Rec003fd160 *) ((u8 *) var_6 + 0x14);
        }
    }
    return 1;
}
