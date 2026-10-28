/* rgp:protos */
#define RGP_SELF_StatusEntryClear_3a5f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S003A5F10 {
    u8 f0;                    /* +0x0 */
    u8 pad1[0x3];
    s32 f4;                   /* +0x4 */
} S003A5F10;

s32 StatusEntryClear_3a5f10(S003A5F10 *p, s32 flag)
{
    if (flag == 0) {
        if (p->f0 == 0) {
            return 0;
        }
    }
    p->f0 = 0;
    p->f4 = 0;
    return 1;
}
