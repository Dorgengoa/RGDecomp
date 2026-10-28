/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3
#undef NULL
#define NULL 0
#pragma opt_common_subs off
#pragma opt_propagation off
class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    void f20() { VCM0(void, 0x20); }
    
    
    
    
    
    
    
    
    
    s32 f48() { return VCM0(s32, 0x48); }
    
    
    
    
    
    
    void f64() { VCM0(void, 0x64); }
};
struct BF { u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; };
extern "C" {
s32 CfgVmCopyStringPoolMaybe_42f500(s32 *, u8 *, s32, s32);
s32 CfgVmLoad_42fac0(void *, int, int);
s32 CfgVmReset_42fc10(void *);
s32 DelayThread_117618(s32);
void MemStackReset_14d830(s32);
s32 DataTableBuildHashIndex_3686c0(Obj *, int, int, int);
s32 ArenaCommit_370490(u8 *);
s32 ArenaSync_370540(u8 *, s32);
s32 CfgVmRun_42fa20(s32 *);
s32 CfgVmRegisterCmds_42fb00(s32 *, s32);
extern Obj *D_004830F8;
extern s16 D_004830FC;

s32 DataTableRunCfg_3683e0(Obj *arg0, s32 arg1, s32 arg2, s32 arg3) {
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(s32[521])) + (0x829) + (0x6) + (0x420)];
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
    CfgVmReset_42fc10((void *)((*(s32 (*)[521])(rgp_blk1 + 0x0))));
    CfgVmRegisterCmds_42fb00((*(s32 (*)[521])(rgp_blk1 + 0x0)), t);
    CfgVmLoad_42fac0((void *)((*(s32 (*)[521])(rgp_blk1 + 0x0))), arg1, arg2);
    *(s32 **)((u8 *)arg0 + 4) = (*(s32 (*)[521])(rgp_blk1 + 0x0));
    D_004830F8 = arg0;
    D_004830FC = 0;
    DelayThread_117618(0xA);
    ArenaSync_370540((u8 *)arg0 + 0x6C, 0);
    if (((BF *)((u8 *)arg0 + 0x7A))->b1) {
        m = -1;
        CfgVmCopyStringPoolMaybe_42f500((*(s32 (*)[521])(rgp_blk1 + 0x0)), (u8 *)arg0 + 0x6C, m, m);
    }
    CfgVmRun_42fa20((*(s32 (*)[521])(rgp_blk1 + 0x0)));
    D_004830F8 = NULL;
    *(s32 **)((u8 *)arg0 + 4) = NULL;
    DelayThread_117618(0xA);
    if (((BF *)((u8 *)arg0 + 0x7A))->b0) {
        arg0->f64();
        DelayThread_117618(0xA);
    }
    if (((BF *)((u8 *)arg0 + 0x7A))->b2) {
        DataTableBuildHashIndex_3686c0(arg0, 0, 0, 0);
        DelayThread_117618(0xA);
    }
    ArenaCommit_370490((u8 *)arg0 + 0x6C);
    return 1;
}

}
