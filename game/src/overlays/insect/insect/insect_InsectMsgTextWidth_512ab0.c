/* rgp:protos */
#define RGP_SELF_insect_InsectMsgTextWidth_512ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00512AB0 -- 92 bytes.  $4 is overwritten with the frame buffer
 * before it is ever read, so the first parameter is unused. */

typedef struct Buf {
    u8 b[0x48];
} Buf;

/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectMsgTextWidth_512ab0(s32 unused, s32 n, s32 v)
{
    s32 x;
    s32 y;
    Buf t __attribute__((aligned(16)));

    TextStyleInit_26c610(&t);
    TextStyleInitWithFontType_2931c0(&t, (long long)((s8)v));
    FontMeasureString_26daf0(&t, n, &x, &y);
    return x;
}
