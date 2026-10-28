/* rgp:protos */
#define RGP_SELF_WorldDataCmdMapMarkerSetAddMaybe_3b8ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Node {
    u8  pad000[0x10];
    s32 m10;
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

s32 WorldDataCmdMapMarkerSetAddMaybe_3b8ee0(R8 *a)
{
    Pool *p = D_004830F8;
    s32 n;
    s32 i;

    if (!p->b2) return 1;
    n = VariantGetInt_15f780(a++);
    for (i = 0; i < n; i++) {
        StateBlockMapMarkerSetAddMaybe_3cc170(p->m94->m10, VariantGetInt_15f780(a++), 0, 0);
    }
    return 1;
}
