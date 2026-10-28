/* rgp:protos */
#define RGP_SELF_RecordPayloadInitKind3D_431f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S00431f60 {
    s32 unk0;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 pad5[0xF0 - 5];
    s32 unkF0;
    u8 padF4[0x34C - 0xF4];
    s8 unk34C[3];
    u8 pad34F[1];
    s32 unk350;
} S00431f60;

/*rgp*/
/*rgp*/
/*rgp*/

void RecordPayloadInitKind3D_431f60(S00431f60 *arg0) {
    u8 *var_18;
    u8 *var_17_2;
    u8 temp_9;
    u8 temp_7;
    u8 temp_5;
    u8 temp_11;
    s8 *var_5;
    s32 var_4;
    s32 var_17;
    s32 var_16;
    s32 temp_8;
    s32 temp_6;
    s32 temp_3;
    s32 temp_10;
    s32 z;

    arg0->unk0 = 0x264;
    arg0->b0 = 0;
    arg0->b1 = 0;
    arg0->b2 = 0;
    arg0->b3 = 0;
    arg0->b4 = 0;
    RecordStateSaveSlotInitMaybe_4324a0((u8 *)arg0 + 5);
    InsectTeamInit_4324d0((u8 *)arg0 + 0xC);
    RecordStateSaveSlotInitMaybe_4324a0((u8 *)arg0 + 0xEC);
    arg0->unkF0 = 0;
    var_18 = (u8 *)arg0 + 0xF4;
    var_17 = 0;
    do {
        InsectTeamMemberInit_4325b0(var_18);
        var_17 += 1;
        var_18 += 0x28;
    } while (var_17 < 0xF);
    var_5 = arg0->unk34C;
    var_4 = 0;
    do {
        var_4 += 1;
        *var_5 = -1;
        var_5 += 1;
    } while (var_4 < 3);
    arg0->unk350 = 0;
    var_17_2 = (u8 *)arg0 + 0x354;
    var_16 = 0;
    do {
        InsectTeamInit_4324d0(var_17_2);
        var_16 += 1;
        var_17_2 += 0xE0;
    } while (var_16 < 0x14);
}
