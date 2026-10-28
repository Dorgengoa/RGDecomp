/* rgp:protos */
#define RGP_SELF_DataTableCmdTableParams_4078b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Pool {
    u8 pad000[0x94];
    u8 m94;
    u8 m95;
} Pool;

extern Pool *D_004830F8;
/*rgp*/

s32 DataTableCmdTableParams_4078b0(R8 *src)
{
    Pool *p = D_004830F8;

    p->m94 = VariantGetInt_15f780(src++);
    p->m95 = VariantGetInt_15f780(src);
    return 1;
}
