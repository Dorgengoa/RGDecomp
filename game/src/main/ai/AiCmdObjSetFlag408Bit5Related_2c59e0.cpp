/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {
typedef s32 (*FN)();


void * GetGameData_1fede0(void);                               /* extern */
s32 ScriptSlotGetInt_2cc9c0(s32);                              /* extern */
void **ObjFindById_3bb3a0(s32, s32);                      /* extern */
extern u8 D_004DB928[0x400];

extern "C++" { class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template <class... VcA> s32 f(VcA... vc_va) { return VCM_FN(s32, (void *, ...), 0x414)((void *)this, vc_va...); }
}; }
s32 AiCmdObjSetFlag408Bit5Related_2c59e0(s32 arg0, s32 arg1) {
    s32 temp_4;
    s32 var_18;
    s32 var_2;
    void **temp_2;
    void *temp_16;

    var_18 = arg0;
    temp_16 = GetGameData_1fede0();
    var_2 = (*(s32 *)D_004DB928);
    if (arg1 == 2) {
        temp_4 = var_18;
        var_18 += 8;
        var_2 = ScriptSlotGetInt_2cc9c0(temp_4);
    }
    temp_2 = ObjFindById_3bb3a0((*(s32 *)((u8 *)(temp_16) + 0x1C)), var_2);
    if (temp_2 == NULL) {
        return 0;
    }
    ((VC_0 *)(temp_2))->f(ScriptSlotGetInt_2cc9c0(var_18) != 0);
    return 1;
    return 0;
}

}
