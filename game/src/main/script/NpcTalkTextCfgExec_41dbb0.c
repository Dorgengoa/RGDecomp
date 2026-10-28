/* rgp:protos */
#define RGP_SELF_NpcTalkTextCfgExec_41dbb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_0041dbb0 {
    u8 pad0[0x24];
    s32 f24;
    void *f28;
} S_0041dbb0;

extern S_0041dbb0 *D_00483E78;
extern u8 D_00467F20[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NpcTalkTextCfgExec_41dbb0(S_0041dbb0 *self, void *name, s32 n, void *t, s32 p5)
{
    u8 buf[0x2C] __attribute__((aligned(16)));
    u8 work[0x830] __attribute__((aligned(16)));
    s32 len;
    void *data;
    self->f24 = 0;
    if (name == 0) goto zero;
    if (n <= 0) goto zero;
    if (t != 0) goto g1;
zero:
    return 0;
g1:
    if (NpcTalkTextCfgPath_41df70(self, buf, t, p5) == 0) return 0;
    len = 0;
    data = ArchiveGetFileByPath_1c2800(name, buf, &len);
    if (data == 0) goto done;
    if (len <= 0) goto done;
    self->f24 = 0;
    CfgVmReset_42fc10(work);
    CfgVmRegisterCmds_42fb00(work, D_00467F20);
    CfgVmLoad_42fac0(work, data, len);
    self->f28 = work;
    D_00483E78 = self;
    CfgVmRun_42fa20(work);
    D_00483E78 = 0;
    self->f28 = 0;
done:
    return self->f24;
}
