/* rgp:protos */
#define RGP_SELF_CameraSetAtOffset_177410 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;
/*rgp*/
void CameraSetAtOffset_177410(u8 *p, u128 *src)
{
    *(u128 *)(p + 0xD0) = *src;
    VecAdd_13be20(p + 0xE0, p + 0xD0, p + 0x120);
}
