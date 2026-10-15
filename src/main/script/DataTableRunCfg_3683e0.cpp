#include "types.h"
#pragma optimization_level 3
#undef NULL
#define NULL 0
#pragma opt_common_subs off
#pragma opt_propagation off
class Obj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void f20();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual s32 f48();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void f64();
};
struct BF { u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; };
extern "C" {
s32 CfgVmCopyStringPoolMaybe_42f500(s32 *, u8 *, s32, s32);
s32 CfgVmLoad_42fac0(...);
s32 CfgVmReset_42fc10(...);
s32 DelayThread_117618(s32);
s32 MemStackReset_14d830(s32);
s32 DataTableBuildHashIndex_3686c0(Obj *);
s32 ArenaCommit_370490(u8 *);
s32 ArenaSync_370540(u8 *, s32);
s32 CfgVmRun_42fa20(s32 *);
s32 CfgVmRegisterCmds_42fb00(s32 *, s32);
extern Obj *D_004830F8;
extern s16 D_004830FC;

s32 DataTableRunCfg_3683e0(Obj *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp50[521];
    s32 t;
    s32 m;

    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    if (arg3 != 0) {
        MemStackReset_14d830(*(s32 *)((u8 *)arg0 + 0x10));
    }
    t = arg0->f48();
    arg0->f20();
    CfgVmReset_42fc10(sp50);
    CfgVmRegisterCmds_42fb00(sp50, t);
    CfgVmLoad_42fac0(sp50, arg1, arg2);
    *(s32 **)((u8 *)arg0 + 4) = sp50;
    D_004830F8 = arg0;
    D_004830FC = 0;
    DelayThread_117618(0xA);
    ArenaSync_370540((u8 *)arg0 + 0x6C, 0);
    if (((BF *)((u8 *)arg0 + 0x7A))->b1) {
        m = -1;
        CfgVmCopyStringPoolMaybe_42f500(sp50, (u8 *)arg0 + 0x6C, m, m);
    }
    CfgVmRun_42fa20(sp50);
    D_004830F8 = NULL;
    *(s32 **)((u8 *)arg0 + 4) = NULL;
    DelayThread_117618(0xA);
    if (((BF *)((u8 *)arg0 + 0x7A))->b0) {
        arg0->f64();
        DelayThread_117618(0xA);
    }
    if (((BF *)((u8 *)arg0 + 0x7A))->b2) {
        DataTableBuildHashIndex_3686c0(arg0);
        DelayThread_117618(0xA);
    }
    ArenaCommit_370490((u8 *)arg0 + 0x6C);
    return 1;
}

}
