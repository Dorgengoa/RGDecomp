#include "types.h"
#pragma opt_propagation off

typedef struct Node Node;
typedef struct Payload {
    u8 pad0[8];
    s32 unk8;
} Payload;
struct Node {
    Node *unk0;
    u8 pad4[0xC];
    Payload *unk10;
};
typedef struct Obj002da140 {
    Node *unk0;
    Node *unk4;
    s32 unk8;
} Obj002da140;
typedef struct Arg1_2da140 {
    u8 pad0[0x10];
    s32 unk10;
} Arg1_2da140;

Payload *EffectEntryFindNodeById_2da140(Obj002da140 *arg0, Arg1_2da140 *arg1) {
    Node *temp_2;
    Node *temp_2_2;
    Payload **var_6;
    Payload *temp_2_3;
    s32 k;
    s32 m;

    if (arg0->unk4 == NULL) {
        arg0->unk4 = arg0->unk0;
        arg0->unk8 = 0;
    }
loop_2:
    temp_2 = arg0->unk4;
    if (temp_2 == NULL) {
        var_6 = NULL;
    } else {
        var_6 = &temp_2->unk10;
        temp_2_2 = temp_2->unk0;
        arg0->unk4 = temp_2_2;
        if (temp_2_2 == NULL) {
            arg0->unk8 = 1;
        }
    }
    if (var_6 != NULL) {
        temp_2_3 = *var_6;
        if ((temp_2_3 != NULL) && ((m = temp_2_3->unk8, k = arg1->unk10), k == m)) {
            arg0->unk4 = NULL;
            arg0->unk8 = 0;
            return *var_6;
        }
        goto loop_2;
    }
    arg0->unk4 = NULL;
    arg0->unk8 = 0;
    return NULL;
}
