#include "types.h"

class Obj {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual s32 v30();
    virtual s32 v34(s32);
    virtual s32 v38(s32);
    u8 pad4[0x76];
    u8 unk7A;
    u8 pad7B;
    s16 unk7C;
};

extern "C" s32 DataTableFindByKey_3680a0(Obj *arg0, s32 arg1)
{
    s32 res;
    s32 lo;
    s32 hi;
    s32 mid;
    s32 v;
    s32 i;

    if (arg0->v30() == 0) {
        return 0;
    }
    if (arg0->unk7C <= 0) {
        return 0;
    }
    res = -1;
    if (arg0->unk7A & 1) {
        hi = arg0->unk7C - 1;
        lo = 0;
        while (lo <= hi) {
            mid = lo + (hi - lo + 1) / 2;
            v = arg0->v38(mid);
            if (v == arg1) {
                res = mid;
                break;
            }
            if (v < arg1) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (res >= 0) {
            while (res > 0) {
                v = arg0->v38(res - 1);
                if (v != arg1) {
                    break;
                }
                res--;
            }
        }
    } else {
        for (i = 0; i < arg0->unk7C; i++) {
            v = arg0->v38(i);
            if (v == arg1) {
                res = i;
                break;
            }
        }
    }
    if (res >= 0) {
        return arg0->v34(res);
    }
    return 0;
}
