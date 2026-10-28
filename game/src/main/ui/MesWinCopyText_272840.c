/* rgp:protos */
#define RGP_SELF_MesWinCopyText_272840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void MesWinCopyText_272840(s8 *src, s8 *dst)
{
    s32 i;
    s8 c;

    for (i = 0; i < 800;) {
        c = *src;
        if (c == 0x5C && src[1] == 0x6E) {
            src += 2;
            dst[i] = 0x0A;
            i++;
        } else if (c == 0x0A) {
            if (src[1] == 0x40) {
                dst[i] = 0;
                dst[++i] = 0;
                return;
            }
            src += 1;
            dst[i] = 0x0A;
            i++;
        } else if (c == 0x0D && src[1] == 0x0A) {
            if (src[2] == 0x40) {
                dst[i] = 0;
                dst[++i] = 0;
                return;
            }
            src += 2;
            dst[i] = 0x0A;
            i++;
        } else {
            src++;
            dst[i] = c;
            i++;
        }
        if (*src == 0) {
            dst[i] = 0;
            return;
        }
    }
}
