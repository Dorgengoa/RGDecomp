#include "types.h"
/* normal 0x004F9F80 -- tear the 0x00527820 widget set down, then hand the
 * scene handle to normal_BtlChgPageDraw_506120. */

extern const u8 D_00527820[];
extern void    *D_00484454;       /* gp - 0xD1C */

extern void func_291910(const void *p);
extern void normal_BtlChgPageDraw_506120(void *p);

void normal_BtlChgMenuDraw_4f9f80(void)
{
    func_291910(D_00527820);
    normal_BtlChgPageDraw_506120(D_00484454);
}
