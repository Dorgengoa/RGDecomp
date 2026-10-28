/* rgp:protos */
#define RGP_SELF_TextEntryBuildTemplateText_4356d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 TextEntryBuildTemplateText_4356d0(u8 *arg0, s32 arg1, s8 *arg2)
{
    s8 *dst;
    s8 *src;
    s32 col;
    s32 i;
    s8 c;

    dst = (s8 *)(arg0 + 0x30);
    src = (s8 *)(arg0 + 0x197);
    col = 0;
    i = 0;
    do {
        if (col == 29) {
            *dst = '\n';
            col = 0;
            goto next;
        }
        c = *src;
        if (c == '1') {
            if (arg1 != 0) {
                *dst = '*';
            } else {
                c = *arg2;
                *dst = c;
                if (c == 0) {
                    *dst = '*';
                }
            }
            arg2++;
        } else if (c == '_') {
            *dst = '*';
        }
        col++;
        src++;
next:
        i++;
        dst++;
    } while (i < 0xAE);
    TextEntryMarkStarCells_4357b0(arg0, -1, -1);
    return 0;
}
