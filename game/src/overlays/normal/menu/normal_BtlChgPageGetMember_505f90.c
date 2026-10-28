/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageGetMember_505f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00505F90 -- `jr $31 / lw $2, 0x68($4)` */
s32 normal_BtlChgPageGetMember_505f90(void *p)
{
    return *(s32 *)((u8 *)p + 0x68);
}
