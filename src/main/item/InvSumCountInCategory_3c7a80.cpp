/* MATCH (s41m). Stale pre-match note follows -- PARK: length 0x12C vs retail 0x11C (0x10 over) after 1 round. Not re-tried. */
#include "types.h"
#pragma opt_common_subs off
extern "C" {

extern void *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern s32 InvCategoryMatches_3c8720(void *arg0, s32 arg1, s32 arg2);
extern s32 InvIdGetMajorIndex_3d55f0(s16 arg0);
extern s32 InvGetCategoryOfId_3d56f0(s16 arg0);
extern s32 D_00465B50[4];

class VC_0 {
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
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual s32 f();
};
s32 InvSumCountInCategory_3c7a80(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 var_22;
    s32 var_21;
    s32 temp_19;
    void *temp_2;
    s32 t;

    if (*(s32 *)((u8 *)arg0 + 0x168) == 0) {
        return 0;
    }
    var_22 = 0;
    var_21 = 0;
    temp_19 = D_00465B50[0];
    while (var_21 < temp_19) {
        temp_2 = PoolGetUsedElem_36acb0(*(s32 *)((u8 *)arg0 + 0x168), var_21);
        if ((temp_2 != NULL) &&
            ((arg3 != 0) || (((u64) ((s64) *(u8 *)((u8 *)temp_2 + 0xA) << 0x3E) >> 0x3F) == 0)) &&
            (t = InvGetCategoryOfId_3d56f0(*(s16 *)((u8 *)temp_2 + 0x6)), InvCategoryMatches_3c8720(arg0, arg1, t) != 0) &&
            ((arg2 < 0) || (arg2 == InvIdGetMajorIndex_3d55f0(*(s16 *)((u8 *)temp_2 + 0x6))))) {
            var_22 += ((VC_0 *)(temp_2))->f();
        }
        var_21 += 1;
    }
    return var_22;
}

}
