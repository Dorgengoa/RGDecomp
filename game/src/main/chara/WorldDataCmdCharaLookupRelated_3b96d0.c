/* rgp:protos */
#define RGP_SELF_WorldDataCmdCharaLookupRelated_3b96d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Node { u8 pad000[0x14]; s32 m14; } Node;
typedef struct Pool {
    u8    pad000[0x94];
    Node *m94;
    u8    pad098[0x2];
    u8    b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 5;
    u8    pad09B[0x1];
    s16   m9C;
} Pool;
extern Pool *D_004830F8;
/*rgp*/
s32 WorldDataCmdCharaLookupRelated_3b96d0(void) {
    Pool *p = D_004830F8;
    s16 t;
    if (!p->b2) return 1;
    t = p->m9C;
    if (t < 0) return 1;
    CharaMgrPoolFindById_3a8c60(p->m94->m14, t);
    return 1;
}
