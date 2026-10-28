/* rgp:protos */
#define RGP_SELF_DListPushBack_42e5a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node0042e5a0 {
    struct Node0042e5a0 *unk0;
    struct Node0042e5a0 *unk4;
    void *unk8;
} Node0042e5a0;

typedef struct S0042e5a0 {
    Node0042e5a0 *unk0;
    Node0042e5a0 *unk4;
    u16 unk8;
    u16 unkA;
} S0042e5a0;

s32 DListPushBack_42e5a0(S0042e5a0 *arg0, Node0042e5a0 *arg1)
{
    Node0042e5a0 *temp_2;
    Node0042e5a0 *temp_3;
    Node0042e5a0 *temp_3_2;
    Node0042e5a0 *temp_3_3;
    s32 var_2;
    u16 var_2_2;
    s16 var_2_3;

    if (arg1 == NULL) {
        return 0;
    }
    var_2 = arg1 != NULL;
    if (var_2 != 0) {
        var_2 = arg1->unk8 == arg0;
    }
    if (var_2 != 0) {
        if (arg0->unk0 == arg1) {
            arg0->unk0 = arg1->unk4;
        }
        if (arg0->unk4 == arg1) {
            arg0->unk4 = arg1->unk0;
        }
        temp_3 = arg1->unk0;
        if (temp_3 != NULL) {
            temp_3->unk4 = arg1->unk4;
        }
        temp_3_2 = arg1->unk4;
        if (temp_3_2 != NULL) {
            temp_3_2->unk0 = arg1->unk0;
        }
        arg1->unk8 = NULL;
        var_2_2 = 1;
        arg1->unk0 = NULL;
        arg1->unk4 = NULL;
        arg0->unk8 = (u16) (arg0->unk8 - 1);
        arg0->unkA = 1;
        while (arg0->unkA < arg0->unk8) {
            arg0->unkA *= 2;
        }
    }
    temp_3_3 = arg0->unk4;
    if (temp_3_3 != NULL) {
        if (arg1 != NULL) {
            arg1->unk8 = temp_3_3->unk8;
            arg1->unk4 = temp_3_3->unk4;
            arg1->unk0 = temp_3_3;
            temp_2 = arg1->unk4;
            if (temp_2 != NULL) {
                temp_2->unk0 = arg1;
            }
        }
        temp_3_3->unk4 = arg1;
    } else {
        arg0->unk0 = arg1;
        arg0->unk8 = 0;
    }
    arg1->unk8 = arg0;
    var_2_3 = 1;
    arg0->unk4 = arg1;
    arg0->unk8 = (u16) (arg0->unk8 + 1);
    arg0->unkA = 1;
    while (arg0->unkA < arg0->unk8) {
        arg0->unkA *= 2;
    }
    return 1;
    return 0;
}
