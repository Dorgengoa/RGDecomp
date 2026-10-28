/* rgp:protos */
#define RGP_SELF_DrawListAddLightPacket_146b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Node {
    u8  pad000[0x28];
    u8  *m28;
    s32 m2C;
};

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void DrawListAddLightPacket_146b00(void *p0)
{
    struct Node *n;
    u8 *q;
    s32 cnt;

    n = ((struct Node *)DrawListGetCurBuf_142790(p0));
    if (n != 0) {
        q = n->m28 + n->m2C * 16;
        if (q != 0) {
            cnt = LightStateWritePacket_1484a0(p0, q);
            if (cnt > 0) {
                MemStackAllocQw_14d950(n, cnt);
                DmaPktAddCallTagIfSet_141bb0(p0, q);
            }
        }
    }
}
