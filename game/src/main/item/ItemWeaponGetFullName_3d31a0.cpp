#include "types.h"

/* jalr through vtable slot 0xB4: virtual_index = (0xB4 - 8) / 4 = 43.
 * [[jalr-is-cpp-virtual]] */

typedef struct S2_003d31a0 {
    u8 pad0[0xC];
    s8 *unkC;
} S2_003d31a0;

class VE_003d31a0 {
public:
    VC_VPTR_MEMBER;  
      
      
      
      
      
      
      
      
      
      
      
      
      
    
    s32 * v43() { return VCM0(s32 *, 0xB4); }          /* slot 0xB4 */

    u8 pad4[0xC];
    S2_003d31a0 *unk10;
};

extern "C" s8 *strcpy(s8 *, s8 *);
extern "C" s8 *strcat(s8 *, s8 *);

extern "C" s8 *ItemWeaponGetFullName_3d31a0(VE_003d31a0 *arg0, s8 *arg1)
{
    S2_003d31a0 *temp;
    s32 *temp2;

    if (arg1 == 0) {
        return 0;
    }
    temp = arg0->unk10;
    if (temp == NULL) {
        return 0;
    }
    strcpy(arg1, temp->unkC);
    temp2 = arg0->v43();
    if (temp2 != NULL) {
        strcat(arg1, (s8 *)*temp2);
    }
    return arg1;
}
