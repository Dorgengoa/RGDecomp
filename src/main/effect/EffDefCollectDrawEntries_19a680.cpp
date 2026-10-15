/* MATCH (s41a5): the element cursor (var_20) is a `u8 *` and XformPairComposeOffset_19a010 /
   the virtual take pointers.  As an s32 web the `+0xD0` argument was
   hoisted ahead of $a0 (argument-order residue). */
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct VT8 {
    u8 pad[8];
    s32 (*unk8)(void *, s32, s32, s32);
} VT8;

void XformPairComposeWithParent_199d60(void *, void *);
void XformPairComposeOffset_19a010(void *, void *, void *);
void XformInitIdentity_1a86a0(void *);

class VC_0 {
public:
    u8 pad[0x40];
    virtual s32 f(s32 x0, void *x1, void *x2);
};
s32 EffDefCollectDrawEntries_19a680(u8 *arg0, s32 arg1, u8 *arg2) {
    u8 sp90[0x50];
    s32 var_22;
    u8 **var_21;
    u8 *var_20;
    s32 var_19;
    u8 *temp_18;
    u8 *temp_2;
    VT8 **temp_4;

    XformInitIdentity_1a86a0(&sp90);
    XformPairComposeWithParent_199d60(arg2, &sp90);
    var_20 = *(u8 **)(arg2 + 0xC4);
    var_21 = *(u8 ***)(arg0 + 0xA0);
    var_22 = 0;
    if (var_20 == 0) {
        return 0;
    }
    var_19 = 0;
    while (var_19 < *(s32 *)(arg0 + 0x9C)) {
        temp_18 = *var_21;
        if (*(u8 **)(temp_18 + 0xC) != NULL) {
            temp_2 = *(u8 **)(temp_18 + 0);
            if (temp_2 != NULL) {
                XformPairComposeOffset_19a010(var_20, var_20 + 0xD0, *(u8 **)(arg2 + 0xC4) + (*(s32 *)(temp_2 + 0x14) * 0x120) + 0xD0);
            } else {
                XformPairComposeOffset_19a010(var_20, var_20 + 0xD0, &sp90);
            }
            temp_4 = (VT8 **)*(u8 **)(temp_18 + 0xC);
            var_22 += ((VC_0 *)(temp_4))->f(arg1, var_20, var_20 + 0xD0);
        }
        var_19 += 1;
        var_21 += 0x1;
        var_20 += 0x120;
    }
    return var_22;
}

}
