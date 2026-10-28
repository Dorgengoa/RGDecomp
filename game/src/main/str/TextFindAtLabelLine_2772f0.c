/* rgp:protos */
#define RGP_SELF_TextFindAtLabelLine_2772f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 TextFindAtLabelLine_2772f0(u32 base, s32 len, s32 arg2)
{
    s8 *p;
    s8 *end;

    end = (s8 *)base + len;
    p = (s8 *)base;
    while (p < end) {
        if (*p == 0x40 && arg2 == atoi((const char *)(p + 1))) {
            while (p < end) {
                if (*p == 0xA) {
                    return (s32)(p + 1);
                }
                p++;
            }
            return 0;
        }
        p++;
    }
    return 0;
}
