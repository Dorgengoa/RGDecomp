/* rgp:protos */
#line 1
#include "types.h"

extern "C" s32 ItemInInvCategory9_3d48e0(void *arg0);
extern "C" s32 ItemInInvCategory0_3d4960(void *arg0);

class Obj3ACF20 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    void slot38() { VCM0(void, 0x38); }
};

extern "C" s32 CharaSetEquipId242_3acf20(Obj3ACF20 *arg0, void *arg1)
{
    if (arg1 == NULL) {
        return 0;
    }
    if ((((unsigned char)ItemInInvCategory0_3d4960(arg1)) == 0) && (((unsigned char)ItemInInvCategory9_3d48e0(arg1)) == 0)) {
        return 0;
    }
    *(s16 *)((u8 *)arg0 + 0x242) = *(s16 *)((u8 *)arg1 + 0x4);
    arg0->slot38();
    return 1;
}
