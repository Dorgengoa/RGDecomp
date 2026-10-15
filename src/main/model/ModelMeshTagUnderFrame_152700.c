#include "types.h"

typedef struct Node {
    struct Node *next;      /* 0x0 */
    u8   pad04[0x10 - 4];
    s32  f10;
    s32  f14;
} Node;

typedef struct Self {
    u8    pad00[0x44];
    Node *list;              /* 0x44 */
} Self;

extern s32 FrameIsDescendantOf_149cb0(s32, s32);
extern s32 ArrayGetChecked_152fd0(s32, s32);

s32 ModelMeshTagUnderFrame_152700(Self *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Node *var_19;
    s32 temp_2;
    s32 temp_2_2;
    s32 *temp_16;
    s32 var_17;

    var_19 = arg0->list;
    temp_2 = ArrayGetChecked_152fd0(arg1, arg2);
    if (temp_2 == 0) {
        return 0;
    }
    var_17 = 0;
    while (var_19 != NULL) {
        temp_16 = &var_19->f10;
        if (temp_16 != NULL) {
            temp_2_2 = ArrayGetChecked_152fd0(arg1, temp_16[1]);
            if (temp_2_2 != 0 && (temp_2 == temp_2_2 || FrameIsDescendantOf_149cb0(temp_2_2, temp_2) != 0)) {
                *temp_16 = arg3;
                var_17 += 1;
            }
        }
        var_19 = var_19->next;
    }
    return var_17;
}
