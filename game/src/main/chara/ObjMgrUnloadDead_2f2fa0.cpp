/* MATCH (s41a5): the loop compare is SIGNED (`slt`) but the counter web is
   s32 and the bound u32, compared as `var_18 < (s32)temp_17`.  u32 counter
   gave `sltu` (the old 1-bad residue); s32 both re-scheduled (4 bad). */
#include "types.h"
extern "C" {

typedef struct S2F2 {
    u8 pad0[0x1C];
    void *unk1C;
} S2F2;

extern void *GetGameData_1fede0(void);
extern void CharaUnloadById_2f3090(s32 arg0, s32 arg1);
extern void *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern s32 ObjMgrGetPoolCapacity_3bb0a0(void *arg0);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0xC0); }
};
void ObjMgrUnloadDead_2f2fa0(s32 arg0)
{
    s32 var_19;
    s32 temp_4;
    s32 var_16;
    s32 var_18;
    u32 temp_17;
    S2F2 *temp_2;
    void *temp_3;
    s32 sp[0x10] __attribute__((aligned(16)));
    void *var_21;

    var_19 = 0;
    temp_2 = (S2F2 *)GetGameData_1fede0();
    temp_17 = ObjMgrGetPoolCapacity_3bb0a0(temp_2->unk1C);
    var_18 = 0;
    while (var_18 < (s32)temp_17) {
        temp_4 = *(s32 *)((u8 *)temp_2->unk1C + 0x10);
        if (temp_4 != 0) {
            var_21 = PoolGetUsedElem_36acb0(temp_4, var_18);
        } else {
            var_21 = NULL;
        }
        if ((var_21 != NULL) && (((VC_0 *)(var_21))->f() != 0)) {
            sp[var_19] = *(s32 *)((u8 *)var_21 + 0xC);
            var_19 += 1;
        }
        var_18 += 1;
    }
    var_16 = 0;
    while (var_16 < var_19) {
        CharaUnloadById_2f3090(sp[var_16], arg0);
        var_16 += 1;
    }
}

}
