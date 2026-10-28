/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

extern void FieldHudLogOpen_203fb0(void);
extern void CharaSysEventLogRecord_3a3320(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void CharaSysEventLogKeyRemove_3a3380(s32, s32, int);
extern void CharaSysEventLogKeyAdd_3a33b0(s32 arg0, s32 arg1, s32 arg2);
extern s32 UnitBaseKillStampTime_3b1400(void *, int, int, int);
extern s32 D_00483824;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x3D0); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(s32 x0, s32 x1, s32 x2) { VCM(void, (void *, s32, s32, s32), 0x2B0, x0, x1, x2); }
};
s32 UnitKillStampTime_3bc9e0(void *arg0, s32 pdB, s32 arg2, int rgp_a3)
{
    s32 var_17;
    void *vtbl;
    void **temp_4;

    if (UnitBaseKillStampTime_3b1400((void *)arg0, (int)pdB, (int)arg2, (int)rgp_a3) == 0) {
        return 0;
    }
    if (arg2 != 0) {
        vtbl = *(void **)arg0;
        if ((((VC_0 *)(arg0))->f() == 0) && (D_00483824 != 0)) {
            CharaSysEventLogKeyAdd_3a33b0(D_00483824, 0x7FFB, 0);
            CharaSysEventLogRecord_3a3320(D_00483824, 0x7FFB, *(s32 *)((u8 *)arg0 + 0xC), 0x3D, 1);
            CharaSysEventLogKeyRemove_3a3380(D_00483824, 0x7FFB, 0);
            FieldHudLogOpen_203fb0();
        }
    }
    var_17 = 0;
    while (var_17 < *(s16 *)((u8 *)arg0 + 0x3E6)) {
        temp_4 = *(void ***)((u8 *)arg0 + 0x3E8 + var_17 * 4);
        if (temp_4 != NULL) {
            ((VC_1 *)(temp_4))->f(0, 0, 0);
        }
        var_17 += 1;
    }
    return 1;
}

}
