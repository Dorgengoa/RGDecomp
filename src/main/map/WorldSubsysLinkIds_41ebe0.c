#include "types.h"

typedef struct Arg1_0041ebe0 {
    u8 pad0[0x80];
    s32 unk80;
} Arg1_0041ebe0;

typedef struct Item0041ebe0 {
    u8 pad0[4];
    s32 unk4;
    s32 unk8;
} Item0041ebe0;

extern Item0041ebe0 *IterNext_370040(void *arg0);
extern void IterInit_370170(void *arg0, s32 arg1);
extern s32 GroupGetRecordById_41e040(s32 arg0, s16 arg1, s16 arg2);

s32 WorldSubsysLinkIds_41ebe0(s32 arg0, Arg1_0041ebe0 *arg1, s16 **arg2) {
    u8 sp48[8];
    s32 temp_18;
    s16 temp_17;
    s16 *temp_2;
    s32 var_5;
    Item0041ebe0 *temp_2_2;

    if (arg1 == NULL) {
        return 0;
    }
    temp_18 = arg1->unk80;
    if (temp_18 == 0) {
        return 0;
    }
    if (arg2 == NULL) {
        return 0;
    }
    temp_2 = *arg2;
    if (temp_2 == NULL) {
        return 0;
    }
    temp_17 = *temp_2;
    var_5 = arg0;
    if (arg0 != 0) {
        var_5 += 0x88;
    }
    IterInit_370170(sp48, var_5);
    while ((temp_2_2 = IterNext_370040(sp48)) != NULL) {
        temp_2_2->unk4 = GroupGetRecordById_41e040(temp_18, temp_17, temp_2_2->unk4);
        temp_2_2->unk8 = GroupGetRecordById_41e040(temp_18, temp_17, temp_2_2->unk8);
    }
    return 1;
}
