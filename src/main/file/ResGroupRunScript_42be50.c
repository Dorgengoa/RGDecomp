#include "types.h"

/* A bind / do-work / unbind sequence around a 0x830-byte stack object.

   The thirteen gp-relative globals are written TWICE with identical values
   apart from the first, which is the owner going in and NULL coming out --
   that repeated block is a `static inline` helper (mwcc's C mode takes the
   keyword; an un-inlined helper would cost every call site its whole body).

   `ori $2, $0, 0xFFFF` and `addiu $2, $0, -0x1` are the same sixteen bits
   stored the same way, so the two spellings are not interchangeable: the
   halfword at 0x164 is written as the POSITIVE constant 0xFFFF and the five
   s16 globals as -1. */

extern void CfgVmReset_42fc10(void *);
extern void CfgVmRegisterCmds_42fb00(void *, const void *);
extern void CfgVmLoad_42fac0(void *, s32, s32);
extern void CfgVmRun_42fa20(void *);
extern void ResGroupArenaBegin_42c6e0(void *);
extern void ArenaSync_370540(void *, s32);
extern void ArenaCommit_370490(void *);
extern void ArenaCtxInit_370610(void *, s32);

extern const u8 D_004685C0[];

extern void *D_00483FE0;
extern s32 D_00483FE4;
extern s32 D_00483FE8;
extern s32 D_00483FEC;
extern s32 D_00483FF0;
extern s32 D_00483FF4;
extern s32 D_00483FF8;
extern s32 D_00483FFC;
extern s16 D_00484000;
extern s16 D_00484004;
extern s16 D_00484008;
extern s16 D_0048400C;
extern s16 D_00484010;

static inline void dvbind(void *owner)
{
    D_00483FE0 = owner;
    D_00483FE4 = 0;
    D_00483FE8 = 0;
    D_00483FEC = 0;
    D_00483FF0 = 0;
    D_00483FF4 = 0;
    D_00483FF8 = 0;
    D_00483FFC = 0;
    D_00484000 = -1;
    D_00484004 = -1;
    D_00484008 = -1;
    D_0048400C = -1;
    D_00484010 = -1;
}

s32 ResGroupRunScript_42be50(u8 *arg0, s16 arg1, s32 arg2, s32 arg3)
{
    u8 sp50[0x830];

    CfgVmReset_42fc10(sp50);
    CfgVmRegisterCmds_42fb00(sp50, D_004685C0);
    CfgVmLoad_42fac0(sp50, arg2, arg3);
    dvbind(arg0);
    *(s16 *)(arg0 + 0x164) = arg1;
    ResGroupArenaBegin_42c6e0(arg0);
    ArenaSync_370540(arg0 + 0x168, 0);
    CfgVmRun_42fa20(sp50);
    ArenaCommit_370490(arg0 + 0x168);
    *(u16 *)(arg0 + 0x164) = 0xFFFF;
    ArenaCtxInit_370610(arg0 + 0x168, 0);
    dvbind(0);
    return 1;
}
