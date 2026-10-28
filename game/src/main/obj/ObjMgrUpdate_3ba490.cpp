/* MATCH (s41a5): D_004659C8 declared as a real-sized array (lui/lo, not
   gp-relative) and the stray `#pragma optimize_for_size off` dropped. */
#include "types.h"
extern "C" {

extern void **PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern u8 D_004659C8[0x400];

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(f32 x0) { VCM(void, (void *, f32), 0xD0, x0); }
};
typedef struct {
    u8 pad0[0x4];
    void *unk4;
    u8 pad8[0x8];
    s32 unk10;
} T3ba490_arg0;

s32 ObjMgrUpdate_3ba490(T3ba490_arg0 *arg0, f32 fparg0)
{
    s32 temp_17;
    s32 var_18;
    void **temp_2;

    if (arg0->unk10 == 0) {
        return 0;
    }
    if (!(*(u8 *)((u8 *)*(void **)((u8 *)arg0->unk4 + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    temp_17 = *(s32 *)D_004659C8;
    var_18 = 0;
    while (var_18 < temp_17) {
        temp_2 = PoolGetUsedElem_36acb0(arg0->unk10, var_18);
        if (temp_2 != NULL) {
            ((VC_0 *)(temp_2))->f(fparg0);
        }
        var_18 += 1;
    }
    return 1;
    return 0;
}

}
