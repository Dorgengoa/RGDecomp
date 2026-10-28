/* rgp:protos */
#line 1
/* PARK s16d: 3 round trips tried, length 0xF8 vs retail 0xF0 (2 words over).
   The extra words are a dsll32/dsra32 re-narrow of `v18` (s16) before the
   `v18 != ret` compare -- tried declaring the vtable-call return `ret` as
   s16 (to match the field width) instead of s32: that REMOVED the narrow
   pair but grew the file to 0x100 (4 words over) elsewhere, so reverted to
   s32. Register colouring (arg2/mode/arg0/v18 -> s3/s0/s1/s2 in retail) is
   also permuted versus mine (s0/s1/s2/s3 in param order) but untried since
   the narrow-pair issue dominates. */
#include "types.h"
extern "C" {

extern s32 ItemInInvCategory0_3d4960(void *);
extern s32 ItemInInvCategory9_3d48e0(void *);
extern s32 ItemGetWeaponKind_3d4f90(void *);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x5C); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x38); }
};
s32 CharaEquipWeapon_3ad140(void *arg0, s32 arg1, void *arg2)
{
    void *vtbl;
    void *p;
    s32 v18;
    s16 v3;
    s32 ret;

    if (arg1 != 0 && arg1 != 1) {
        return 0;
    }
    if (arg2 == NULL) {
        return 0;
    }
    if (((unsigned char)ItemInInvCategory0_3d4960(arg2)) == 0 && ((unsigned char)ItemInInvCategory9_3d48e0(arg2)) == 0) {
        return 0;
    }
    if (arg1 != ItemGetWeaponKind_3d4f90(arg2)) {
        return 0;
    }
    p = *(void **)((u8 *)arg2 + 0x10);
    v18 = *(s16 *)((u8 *)p + 0x8);
    vtbl = *(void **)arg0;
    ret = ((VC_0 *)(arg0))->f();
    if (v18 != ret) {
        return 0;
    }
    v3 = *(s16 *)((u8 *)arg2 + 0x4);
    ((s16 *)((u8 *)arg0 + 0x23E))[arg1] = v3;
    vtbl = *(void **)arg0;
    ((VC_1 *)(arg0))->f();
    return 1;
}

}
