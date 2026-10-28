/* rgp:protos */
#define RGP_SELF_WorldDataCmdSetMoney_3b9ec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    u8  pad000[0x18];
    s32 m18;
} Node;

typedef struct Pool {
    u8    pad000[0x94];
    Node *m94;
    u8    pad098[0x2];
    u8    b0 : 1;
    u8    b1 : 1;
    u8    b2 : 1;
    u8    b3 : 5;
} Pool;

extern Pool *D_004830F8;
/*rgp*/
/*rgp*/

s32 WorldDataCmdSetMoney_3b9ec0(void *rgp_a0)
{
    Pool *p = D_004830F8;
    s32 t;

    if (!p->b2) return 1;
    t = VariantGetInt_15f780((void *)rgp_a0);
    PartySetMoney_3c9720(p->m94->m18, t);
    return 1;
}
