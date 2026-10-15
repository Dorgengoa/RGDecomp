#include "types.h"
#pragma opt_common_subs off
class V3c8cc0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void v10();
};
extern "C" {
void PoolFreeElem_36a8e0(s32, s32);
V3c8cc0 *PoolGetUsedElem_36acb0(s32, s32);
extern s32 D_00465B50[0x100];
}

extern "C" s32 InvPurgeRemoved_3c8cc0(void *arg0)
{
    s32 temp_16;
    s32 var_17;
    V3c8cc0 *temp_2;

    if (*(s32 *)((u8 *)arg0 + 0x168) == 0) {
        return 0;
    }
    temp_16 = D_00465B50[0];
    var_17 = 0;
    while (var_17 < temp_16) {
        temp_2 = PoolGetUsedElem_36acb0(*(s32 *)((u8 *)arg0 + 0x168), var_17);
        if ((temp_2 != NULL) && (((u64)((u64)(*((u8 *)temp_2 + 0xA)) << 0x3E) >> 0x3F) != 0)) {
            temp_2->v10();
            PoolFreeElem_36a8e0(*(s32 *)((u8 *)arg0 + 0x168), var_17);
        }
        var_17 += 1;
    }
    return 1;
}
