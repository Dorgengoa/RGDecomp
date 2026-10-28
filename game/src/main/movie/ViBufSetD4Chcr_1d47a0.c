/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_ViBufSetD4Chcr_1d47a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

void ViBufSetD4Chcr_1d47a0(u32 h)
{
    DisableIntr_120660();
    HW_W32(0x1000F590u, ((u32)HW_R32(0x1000F520u)) | 0x10000);
    HW_W32(0x1000B400u, h);
    HW_W32(0x1000F590u, ((u32)HW_R32(0x1000F520u)) & 0xFFFEFFFF);
    EnableIntr_1206b0();
}
