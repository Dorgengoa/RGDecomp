#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 get5C() { return VCM0(s32, 0x5C); }
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
