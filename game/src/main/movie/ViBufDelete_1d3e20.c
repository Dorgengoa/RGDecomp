/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_ViBufDelete_1d3e20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/*rgp*/
extern void DeleteSema(s32);
struct A { u8 pad000[0x40]; s32 m40; };
s32 ViBufDelete_1d3e20(struct A *p0)
{
    ViBufSetD4Chcr_1d47a0(5);
    HW_W32(0x1000B420u, 0);
    HW_W32(0x1000B410u, 0);
    HW_W32(0x1000B430u, 0);
    DeleteSema(p0->m40);
    return 1;
}
