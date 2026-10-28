/* rgp:protos */
#define RGP_SELF_WorldDataCmdSectionBegin_3b9f20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Node {
    u8   pad000[0x18];
    s32  m18;
} Node;

typedef struct Pool {
    u8    pad000[0x4];
    void *m4;
    u8    pad008[0x8C];
    Node *m94;
    s16   m98;
    u8    b0 : 1;
    u8    b1 : 1;
    u8    b2 : 1;
    u8    b3 : 5;
    u8    pad09B[0x1];
    s16   m9C;
} Pool;

extern Pool *D_004830F8;
/*rgp*/
extern void DelayThread_117618(s32 a);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 WorldDataCmdSectionBegin_3b9f20(R8 *a)
{
    Pool *p = D_004830F8;
    s32 old;
    s32 t;

    DelayThread_117618(0xA);
    t = VariantGetInt_15f780(a);
    old = p->b2 == 1;
    if (t == p->m98) p->b2 = 1; else p->b2 = 0;
    if (p->b2) {
        PartySetMoney_3c9720(p->m94->m18, (long long)(0));
        InvPoolClear_3c8e40(p->m94->m18);
        PartyMembersReset_3c31b0(p->m94->m18);
    } else if (old) {
        CfgVmSkipToEnd_42f600(p->m4);
    } else {
        CfgVmFindOp_42f650(p->m4, 0x64, 1);
    }
    p->m9C = -1;
    return 1;
}
