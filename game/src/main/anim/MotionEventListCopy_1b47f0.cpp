#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct Node001b47f0 Node001b47f0;
typedef struct VT001b47f0 {
    u8 pad0[8];
    void (*unk8)(Node001b47f0 *);
} VT001b47f0;
struct Node001b47f0 {
    Node001b47f0 *unk0;
    Node001b47f0 *unk4;
    u8 pad8[0x20];
    VT001b47f0 *unk28;
};

extern void *MemStackNew_14e230(s32, s32);
extern void MotionEventBlockCopy_1b22a0(void *, void *, s32);
extern void MotionEventBlockInit_1b2520(void *);
extern VT001b47f0 D_004710D8;

class VC_0 {
public:
    u8 pad[0x28];
    VC_VPTR_MEMBER; void f() { VCM0(void, 0x8); }
};
void MotionEventListCopy_1b47f0(Node001b47f0 **arg0, Node001b47f0 **arg1, s32 arg2) {
    Node001b47f0 *var_18;
    Node001b47f0 *var_5;
    Node001b47f0 *var_4;
    void *temp_17;
    Node001b47f0 *temp_3;
    Node001b47f0 *temp_2;

    *arg1 = NULL;
    if (arg2 == 0) {
        *arg1 = *arg0;
        return;
    }
    var_18 = *arg0;
    while (var_18 != NULL) {
        temp_17 = (u8 *)var_18 + 0x10;
        temp_2 = (Node001b47f0 *)MemStackNew_14e230(0x2C, arg2);
        if (temp_2 != NULL) {
            temp_2->unk28 = &D_004710D8;
            MotionEventBlockInit_1b2520((u8 *)temp_2 + 0x10);
            ((VC_0 *)(temp_2))->f();
        }
        if (temp_2 == NULL) {
            var_5 = NULL;
        } else {
            var_4 = *arg1;
            if (var_4 != NULL) {
                while (var_4 != NULL) {
                    temp_3 = var_4->unk0;
                    if (temp_3 != NULL) {
                        var_4 = temp_3;
                        continue;
                    }
                    break;
                }
                var_4->unk0 = temp_2;
                if (temp_2 != NULL) {
                    temp_2->unk4 = var_4;
                }
            } else {
                *arg1 = temp_2;
            }
            var_5 = (Node001b47f0 *)((u8 *)temp_2 + 0x10);
        }
        if ((var_5 != NULL) && (temp_17 != NULL)) {
            MotionEventBlockCopy_1b22a0(temp_17, var_5, arg2);
        }
        var_18 = var_18->unk0;
    }
}

}
