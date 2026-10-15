#include "types.h"

class Obj {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual s32 get5C();
};

extern "C" Obj *PartyFindItemHolder_3d4c20(void *);
extern "C" s32 ItemDefKindBelow4_40e430(void *);

extern "C" bool ItemIsEquippableBy_3d4750(void *arg0, Obj *arg1, s32 arg2, s32 arg3)
{
    u8 *p;
    bool ok;
    Obj *r;

    p = *(u8 **)((u8 *)arg0 + 0x10);
    if (p == NULL) {
        return 0;
    }
    if (ItemDefKindBelow4_40e430(p) != 0) {
        if (arg2 < 0) {
            ok = true;
        } else if (arg2 == *(s8 *)(p + 2)) {
            ok = true;
        } else {
            ok = false;
        }
    } else {
        ok = false;
    }
    if (ok) {
        if (*(s8 *)(p + 2) == 3) {
            if (arg3 == 0) {
                ok = true;
            } else {
                r = PartyFindItemHolder_3d4c20(arg0);
                if (r == NULL) {
                    ok = true;
                } else if (arg1 != NULL) {
                    if (r == arg1) {
                        ok = true;
                    } else {
                        ok = false;
                    }
                } else {
                    ok = false;
                }
            }
        } else if (arg1 != NULL) {
            if (*(s16 *)(p + 8) == arg1->get5C()) {
                ok = true;
            } else {
                ok = false;
            }
        } else {
            ok = true;
        }
    }
    return ok;
}
