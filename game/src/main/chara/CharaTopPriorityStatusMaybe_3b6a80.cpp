#include "types.h"
extern "C" {

extern void *D_0048381C;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x19C, x0); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * f(s16 x0) { return VCM(void *, (void *, s16), 0x70, x0); }
};
s32 CharaTopPriorityStatusMaybe_3b6a80(void **arg0)
{
    s32 var_18;
    s32 var_17;
    s32 var_16;
    s32 temp_2;
    void **temp_4;
    void *var_2;

    var_18 = -1;
    var_17 = -1;
    var_16 = 1;
    do {
        if (((VC_0 *)(arg0))->f(var_16) != 0) {
            temp_4 = *(void ***)((u8 *)(*(void **)((u8 *)D_0048381C + 0x58)) + 8);
            if (temp_4 != NULL) {
                var_2 = ((VC_1 *)(temp_4))->f(var_16);
            } else {
                var_2 = NULL;
            }
            if (var_2 != NULL) {
                temp_2 = *(u8 *)((u8 *)var_2 + 5);
                if ((var_17 < 0) || ((s32)temp_2 < var_18)) {
                    var_18 = (s32)temp_2;
                    var_17 = var_16;
                }
            }
        }
        var_16 += 1;
    } while (var_16 <= 0x2f);
    return var_17;
}

}
