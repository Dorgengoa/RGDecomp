/* rgp:protos */
#define RGP_SELF_PtalkTextCfgExec_41f6b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T_0041f6b0 {
    u8 pad0[0xC];
    s32 fC;
} T_0041f6b0;

typedef struct S_0041f6b0 {
    u8 pad0[0x20];
    s32 f20;
    void *f24;
} S_0041f6b0;

extern S_0041f6b0 *D_00483EA8;
extern u8 D_00467FB0[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 PtalkTextCfgExec_41f6b0(S_0041f6b0 *self, void *name, s32 n, T_0041f6b0 *t)
{
    u8 buf[0x2C] __attribute__((aligned(16)));
    u8 work[0x830] __attribute__((aligned(16)));
    s32 len;
    void *data;
    self->f20 = 0;
    if (name == 0) goto zero;
    if (n <= 0) goto zero;
    if (t != 0) goto g1;
zero:
    return 0;
g1:
    if (t->fC != 0) goto g2;
    return 0;
g2:
    if (PtalkTextCfgPath_41fa50(self, buf, t) == 0) return 0;
    len = 0;
    data = ArchiveGetFileByPath_1c2800(name, buf, &len);
    if (data == 0) goto done;
    if (len <= 0) goto done;
    self->f20 = 0;
    CfgVmReset_42fc10(work);
    CfgVmRegisterCmds_42fb00(work, D_00467FB0);
    CfgVmLoad_42fac0(work, data, len);
    self->f24 = work;
    D_00483EA8 = self;
    CfgVmRun_42fa20(work);
    D_00483EA8 = 0;
    self->f24 = 0;
done:
    return self->f20;
}
