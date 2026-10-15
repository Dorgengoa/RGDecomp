#include "types.h"
#pragma opt_propagation off
extern "C" s32 *ObjRecTableGet_1c3f60(void *, s32);
extern "C" s32 ObjRecBind_1c4630(s32 *, s32, void *);
extern "C" s32 D_0047E258;

typedef struct {
    u8 pad0[0x3b14];
    s32 unk3B14;
    u8 pad3B18[0x82c];
    s32 unk4344;
} T1c3c10_arg0;

extern "C" s32 ObjRecTableBindSlot_1c3c10(T1c3c10_arg0 *arg0, s32 arg1, s32 arg2, void *arg3) {
    void *var_17;
    s32 *temp_2;
    s32 *temp_2_2;
    s32 var_17_2;

    var_17 = arg3;
    if (arg1 < 0) {
        for (var_17_2 = 0; var_17_2 < arg0->unk3B14; var_17_2++) {
            temp_2 = ObjRecTableGet_1c3f60(arg0, var_17_2);
            if (temp_2 != NULL) {
                bool z = *temp_2 == 0;
                if (z) {
                    break;
                }
            }
        }
        return -1;
    }
    temp_2_2 = ObjRecTableGet_1c3f60(arg0, arg1);
    if (temp_2_2 == NULL) {
        return -1;
    }
    if (var_17 == NULL) {
        var_17 = &D_0047E258;
    }
    if (arg0->unk4344 < 0) {
        arg0->unk4344 = arg1;
    }
    if (!(ObjRecBind_1c4630(temp_2_2, arg2, var_17) == 0)) {
        return arg1;
    }
    return -1;
}
