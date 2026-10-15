#include "types.h"

typedef struct Node001a89c0 Node001a89c0;
struct Node001a89c0 {
    u8 pad0[4];
    void *unk4;
    u8 pad8[4];
    Node001a89c0 *unkC;
};

typedef struct Bucket001a89c0 {
    u8 pad0[4];
    void **unk4;
    u8 pad8[8];
    s32 unk10;
} Bucket001a89c0;

typedef struct S001a89c0 {
    u8 pad0[0x100];
    s32 unk100;
    void **unk104;
    Bucket001a89c0 *unk108;
} S001a89c0;

extern void MemStackHeapFree_14dcb0(s32, Node001a89c0 *);

void HashTableFreeNodes_1a89c0(s32 pd0, s32 arg1, S001a89c0 *arg2) {
    s32 var_10;
    Node001a89c0 *var_9;
    Node001a89c0 *nx;
    Node001a89c0 *var_5;
    Bucket001a89c0 *temp_5;
    Node001a89c0 *temp_20;
    void **temp_7;
    void **temp_19;
    s32 var_16;
    s32 temp_3_2;
    s32 temp_3;

    if (arg2->unk108 != 0) {
        var_10 = 0;
        while (var_10 < arg2->unk100) {
            temp_7 = arg2->unk104 + var_10;
            var_9 = (Node001a89c0 *)*temp_7;
            while (var_9 != NULL) {
                temp_5 = arg2->unk108 + var_10;
                temp_3 = temp_5->unk10;
                nx = var_9->unkC;
                if (temp_3 > 0) {
                    temp_3_2 = temp_3 - 1;
                    temp_5->unk10 = temp_3_2;
                    temp_5->unk4[temp_3_2] = var_9;
                }
                var_9 = nx;
            }
            *temp_7 = NULL;
            var_10 += 1;
        }
        return;
    }
    var_16 = 0;
    while (var_16 < arg2->unk100) {
        temp_19 = arg2->unk104 + var_16;
        var_5 = (Node001a89c0 *)*temp_19;
        while (var_5 != NULL) {
            temp_20 = var_5->unkC;
            MemStackHeapFree_14dcb0(arg1, var_5);
            var_5 = temp_20;
        }
        *temp_19 = NULL;
        var_16 += 1;
    }
}
