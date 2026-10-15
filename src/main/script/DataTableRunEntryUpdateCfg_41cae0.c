#include "types.h"

typedef struct Rdr { u8 b[0x830]; } Rdr;

typedef struct Pool {
    u8    pad000[0x4];
    void *m4;
    u8    pad008[0x64];
    u8    m6C[0x10];
} Pool;

extern Pool *D_004830F8;
extern s32   D_00483E44;
extern void *DataTableEntryUpdateCmdTable_41cda0(void);
extern void  CfgVmReset_42fc10(Rdr *r);
extern void  CfgVmRegisterCmds_42fb00(Rdr *r, void *t);
extern void  CfgVmLoad_42fac0(Rdr *r, void *b, s32 c);
extern void  CfgVmRun_42fa20(Rdr *r);
extern void  ArenaSync_370540(void *m, s32 v);
extern void  ArenaCommit_370490(void *m);

s32 DataTableRunEntryUpdateCfg_41cae0(Pool *p, void *b, s32 c)
{
    Rdr loc;
    void *t;

    if (b == 0 || c <= 0) return 0;
    t = DataTableEntryUpdateCmdTable_41cda0();
    CfgVmReset_42fc10(&loc);
    CfgVmRegisterCmds_42fb00(&loc, t);
    CfgVmLoad_42fac0(&loc, b, c);
    p->m4 = &loc;
    D_004830F8 = p;
    D_00483E44 = 0;
    ArenaSync_370540(p->m6C, 0);
    CfgVmRun_42fa20(&loc);
    ArenaCommit_370490(p->m6C);
    D_004830F8 = 0;
    D_00483E44 = 0;
    p->m4 = 0;
    return 1;
}
