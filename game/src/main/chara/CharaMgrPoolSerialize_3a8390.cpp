#pragma opt_propagation off
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct VT8390 {
    u8 pad[0x14];
    s32 (*unk14)(void *, s32, s32);
} VT8390;

void **PoolGetUsedElem_36acb0(s32, s32);
s32 SerialWriteChunkHeader_370e50(s32, s32, s32, s32, s32 **);
extern s32 D_004659B8[];

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    s32 f(s32 x0, s32 x1) { return VCM(s32, (void *, s32, s32), 0x14, x0, x1); }
};
s32 CharaMgrPoolSerialize_3a8390(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_20;
    s32 var_19;
    s32 temp_16;
    s32 temp_2_3;
    VT8390 **temp_2_2;
    s32 rem;
    s32 var_17;
    s32 *sp7C;
    s32 temp_2;

    if (arg1 == 0) goto ret0;
    if (arg2 > 0) goto body;
ret0:
    return 0;
body:
    {
        rem = arg2;
        sp7C = NULL;
        var_20 = 0;
        temp_2 = SerialWriteChunkHeader_370e50(arg1, rem, 3, 0, &sp7C);
        var_19 = arg1 + temp_2;
        var_20 += temp_2;
        rem -= temp_2;
        temp_16 = D_004659B8[0];
        for (var_17 = 0; var_17 < temp_16; var_17++) {
            temp_2_2 = (VT8390 **)PoolGetUsedElem_36acb0(*(s32 *)(arg0 + 8), var_17);
            if (temp_2_2 != NULL) {
                temp_2_3 = ((VC_0 *)(temp_2_2))->f(var_19, rem);
                var_20 += temp_2_3;
                var_19 += temp_2_3;
                rem -= temp_2_3;
                if (sp7C != NULL) {
                    *sp7C += temp_2_3;
                }
            }
        }
        return var_20;
    }
}

}
