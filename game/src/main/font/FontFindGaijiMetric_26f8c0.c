/* rgp:protos */
#define RGP_SELF_FontFindGaijiMetric_26f8c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern u16 D_0044E680[];

u16 *FontFindGaijiMetric_26f8c0(s32 arg0, s32 arg1)
{
    u16 key;
    u16 *p;
    u16 temp;

    key = (u16)arg1;
    if (key == 0xFD3E && ((signed char)TextStyleGetFontType_26ede0((void *)arg0)) == 2) {
        key = 0xFD3F;
    }
    p = D_0044E680;
    while ((temp = *p) != 0) {
        if (temp == key) {
            return p;
        }
        p += 6;
    }
    return NULL;
}
