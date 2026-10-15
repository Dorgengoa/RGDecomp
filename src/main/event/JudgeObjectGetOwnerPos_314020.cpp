#include "types.h"

struct Obj00314020 { u8 pad0[0x86];s16 unk86;u8 pad88[2];s16 unk8A;u8 pad8C[0x24];virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void method();};
extern "C" {
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s16);
extern void CharaGetPos_2388a0(s32, s32);

s32 JudgeObjectGetOwnerPos_314020(Obj00314020 *arg0, s32 arg1)
{
    s16 temp_3;
    s32 temp_2;

    temp_3 = arg0->unk8A;
    switch (temp_3) {
    case 1:
        temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), arg0->unk86);
        if (temp_2 != 0) {
            CharaGetPos_2388a0(temp_2, arg1);
            return 1;
        }
        break;
    case 2:
        arg0->method();
        return 1;
    case 5:
        arg0->method();
        return 1;
    }
    return 0;
}

}
