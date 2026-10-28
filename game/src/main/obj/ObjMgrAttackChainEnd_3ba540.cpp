#include "types.h"

/* jalr through vtable slot 0x454: virtual_index = (0x454 - 8) / 4 = 275.
 * [[jalr-is-cpp-virtual]] */

class VE_003ba540 {
public:
    VC_VPTR_MEMBER;   
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
      
    void v275(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0x454, a0, a1); }          /* slot 0x454 */
};

typedef struct S3_003ba540 {
    u8 pad0[0x24C];
    u8 unk24C;
} S3_003ba540;

typedef struct S2_003ba540 {
    u8 pad0[0x20];
    S3_003ba540 *unk20;
} S2_003ba540;

typedef struct S_003ba540 {
    u8 pad0[0x4];
    S2_003ba540 *unk4;
    u8 pad8[0x10 - 0x8];
    s32 unk10;
} S_003ba540;

extern "C" VE_003ba540 *PoolGetUsedElem_36acb0(s32, s32);
extern "C" u8 D_004659C8[];

extern "C" s32 ObjMgrAttackChainEnd_3ba540(S_003ba540 *arg0, s32 arg1, s32 arg2)
{
    s32 temp_20;
    s32 var_16;
    VE_003ba540 *temp_2_2;
    S2_003ba540 *temp_2;

    temp_2 = arg0->unk4;
    if (temp_2 == 0) {
        return 0;
    }
    if (!(temp_2->unk20->unk24C & 1)) {
        return 0;
    }
    if (arg0->unk10 == 0) {
        return 0;
    }
    temp_20 = *(s32 *)D_004659C8;
    var_16 = 0;
    while (var_16 < temp_20) {
        temp_2_2 = PoolGetUsedElem_36acb0(arg0->unk10, var_16);
        if (temp_2_2 != 0) {
            temp_2_2->v275(arg1, arg2);
        }
        var_16 += 1;
    }
    return 1;
}
