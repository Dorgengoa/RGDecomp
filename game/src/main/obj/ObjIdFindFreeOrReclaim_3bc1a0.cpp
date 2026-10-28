#include "types.h"

class VC3bc1a0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f434() { return VCM0(s32, 0x434); }
};

extern "C" {
extern VC3bc1a0 *ObjFindById_3bb3a0(s32 arg0, s32 arg1);
extern void ObjFreeRecursive_3bb4f0(s32 arg0, s32 arg1, s32 arg2);

s32 ObjIdFindFreeOrReclaim_3bc1a0(s32 arg0)
{
    VC3bc1a0 *temp_2;
    s32 var_18;
    s32 var_17;
    s32 var_16;

    var_18 = -1;
    var_17 = 1;
    while (var_17 <= 2) {
        var_16 = 0x80;
        while (var_16 <= 0x9b) {
            temp_2 = ObjFindById_3bb3a0(arg0, var_16);
            if (temp_2 == NULL) {
                var_18 = var_16;
                break;
            }
            if ((temp_2->f434() != 0) && (var_17 == 2)) {
                ObjFreeRecursive_3bb4f0(arg0, var_16, 1);
                var_18 = var_16;
                break;
            }
            var_16 += 1;
        }
        if (var_18 < 0) {
            var_17 += 1;
            continue;
        }
        break;
    }
    return var_18;
}
}
