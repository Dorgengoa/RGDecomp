/* rgp:protos */
#define RGP_SELF_ItemDataCmdSetWeaponScale_40dad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R8 { u8 b[8]; } R8;

typedef struct Pool {
    u8  pad000[0x94];
    f32 m94;
    f32 m98;
} Pool;

extern Pool *D_004830F8;
/*rgp*/

s32 ItemDataCmdSetWeaponScale_40dad0(R8 *src)
{
    Pool *p = D_004830F8;

    p->m94 = VariantGetFloat_15f740(src++);
    p->m98 = VariantGetFloat_15f740(src);
    return 1;
}
