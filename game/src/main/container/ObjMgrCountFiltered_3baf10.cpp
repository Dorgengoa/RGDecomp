/* MATCH (s41m). Stale pre-match note follows -- PARK s16d: 1 round trip, same length as retail (100 words) but 69 bad --
   register/CSE residue, not structural. The 4 vtable calls per node reuse
   one cached `vtbl` local instead of re-deriving `(*node)->vtbl` fresh
   each time like the m2c draft's repeated `(*temp_2_2)->` shows retail
   doing; likely the fix. */
#include "types.h"
#include "vec.h"
#pragma opt_common_subs off
extern "C" {

extern void **PoolGetUsedElem_36acb0(void *, s32);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x434); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x5C); }
};
class VC_2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xBC); }
};
class VC_3 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xC0); }
};
s32 ObjMgrCountFiltered_3baf10(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 (*arg4)(void **))
{
    s32 lim;
    void *p10;
    s32 count;
    s32 i;
    void **node;
    u16 ok;
    void *obj;
    void *vtbl;

    if (arg2 == 0 && arg3 == 0) {
        return 0;
    }
    p10 = *(void **)((u8 *)arg0 + 0x10);
    if (p10 == NULL) {
        return 0;
    }
    count = 0;
    i = 0;
    lim = *(s32 *)((u8 *)p10 + 0x14);
    while (i < lim) {
        node = PoolGetUsedElem_36acb0(*(void **)((u8 *)arg0 + 0x10), i);
        if (node != NULL) {
            obj = *node;
            vtbl = *(void **)obj;
            if (((VC_0 *)(node))->f() == 0) {
                ok = 1;
                if (arg1 >= 0 && arg1 != ((VC_1 *)(node))->f()) {
                    ok = 0;
                }
                if (ok && arg2 == 0 && ((VC_2 *)(node))->f() != 0) {
                    ok = 0;
                }
                if (ok && arg3 == 0 && ((VC_3 *)(node))->f() != 0) {
                    ok = 0;
                }
                if (ok && arg4 != NULL) {
                    ok = arg4(node) & 0xFF;
                }
                if (ok) {
                    count += 1;
                }
            }
        }
        i += 1;
    }
    return count;
}

}
