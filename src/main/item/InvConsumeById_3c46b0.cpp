#include "types.h"
extern "C" {
extern s32 InvCountById_3c78d0(s32 xa0, s32 xa1, s32, s32);
class VObj {
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
    virtual s32 size();
};
extern VObj *InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);
extern s32 ItemConsume_3d41b0(VObj *, s32, s32);

s32 InvConsumeById_3c46b0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 temp_2;
    VObj *p;
    s32 n;
    s32 var_19;
    s32 var_5;

    temp_2 = InvCountById_3c78d0(arg0, arg1, 0, 0);
    if (temp_2 < arg2) {
        return arg2 - temp_2;
    }
    for (var_19 = arg2; var_19 > 0; ) {
        p = InvFindInCategoryRange_3c8370(arg0, arg1, arg3, -1, 0, 0);
        if (p == NULL) {
            break;
        }
        n = p->size();
        var_5 = n;
        if (var_19 < n) {
            var_5 = var_19;
        }
        if (!(ItemConsume_3d41b0(p, var_5, arg4) & 0xFF)) {
            break;
        }
        var_19 -= n;
    }
    return var_19;
}

}
