/* rgp:protos */
#define RGP_SELF_CharaDataSubRecCollectNodes_1ee640 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node001ee640 {
    u8 pad0[0x4];
    struct Node001ee640 *unk4;
    s16 unk8;
} Node001ee640;

typedef struct S001ee640 {
    u8 pad0[0x64];
    Node001ee640 *unk64;
} S001ee640;

s32 CharaDataSubRecCollectNodes_1ee640(S001ee640 *arg0, s32 arg1, Node001ee640 **arg2, s32 arg3)
{
    Node001ee640 *node;
    s32 count;

    node = arg0->unk64;
    if (node == NULL) {
        return 0;
    }
    count = 0;
    while (node != NULL) {
        if (count >= arg3) {
            break;
        }
        if (arg1 == node->unk8) {
            arg2[count] = node;
            count++;
        }
        node = node->unk4;
    }
    return count;
}
