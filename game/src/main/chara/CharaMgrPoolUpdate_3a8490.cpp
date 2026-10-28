#include "types.h"

/* Same "vptr at object offset +0" shape as include/worldobj_cpp.h's
   WorldEntity, used locally (per the project convention seen in
   src/s13o/CharaGetEquippedWeapon_3acd40.cpp etc.) since only the one used slot needs a real
   signature. Used slot is +0xD0 -> virtual index (0xD0-8)/4 = 50, taking the
   function's own f32 argument. */

class V {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void slot0D0(f32 arg1) { VCM(void, (void *, f32), 0xD0, arg1); }
};

typedef struct ObjFUN_003a8490 {
    u8 pad0[0x8];
    s32 unk8;
} ObjFUN_003a8490;

extern "C" V *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern "C" s32 D_004659B8;

extern "C" s32 CharaMgrPoolUpdate_3a8490(ObjFUN_003a8490 *arg0, f32 fparg0)
{
    s32 temp16;
    s32 i;
    V *temp2;

    if (arg0->unk8 == 0) {
        return 0;
    }
    temp16 = D_004659B8;
    for (i = 0; i < temp16; i++) {
        temp2 = PoolGetUsedElem_36acb0(arg0->unk8, i);
        if (temp2 != NULL) {
            temp2->slot0D0(fparg0);
        }
    }
    return 1;
}
