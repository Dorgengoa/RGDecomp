/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuDraw_4f9f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9F80 -- tear the 0x00527820 widget set down, then hand the
 * scene handle to normal_BtlChgPageDraw_506120. */

extern u8 normal_D_00527820[];
extern void    *D_00484454;       /* gp - 0xD1C */

/*rgp*/
/*rgp*/

void normal_BtlChgMenuDraw_4f9f80(void)
{
    UiDrawWidgets_291910(normal_D_00527820);
    normal_BtlChgPageDraw_506120(D_00484454);
}
