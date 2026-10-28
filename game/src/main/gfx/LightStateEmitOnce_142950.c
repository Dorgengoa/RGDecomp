/* rgp:protos */
#define RGP_SELF_LightStateEmitOnce_142950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* beql with the zero in the delay slot = the `if/else`; the plain beqz with
   the zero in the delay slot = the ternary.
   Callee-saved order is declaration order descending from the highest:
   $18 q, $17 nd, $16 s. */

struct Node {
    u8 pad000[0x28];
    u8 *m28;   /* 0x28 */
    s32 m2C;   /* 0x2C */
};

struct Slot {
    u8 pad000[4];
    void *m04; /* 0x04 */
};

struct Ctx {
    s32 m00;              /* 0x00 */
    void *m04;
    void *m08[6];         /* 0x08 */
    u8 pad020[0x3694];
    struct Slot *m36B4;   /* 0x36B4 */
};

/*rgp*/
/*rgp*/

void LightStateEmitOnce_142950(struct Ctx *a)
{
    struct Node *nd;
    void *q;
    struct Slot *s;
    void *e;
    s32 n;

    s = a->m36B4;
    if (s->m04 == 0) {
        e = a->m08[a->m00];
        nd = e ? (struct Node *)((u8 *)e + 8) : 0;
        q = 0;
        if (nd != 0) {
            q = (void *)(nd->m28 + nd->m2C * 16);
        }
        if (q != 0) {
            n = LightStateWritePacket_1484a0(a, q);
            if (n > 0) {
                MemStackAllocQw_14d950(nd, n);
                s->m04 = q;
            }
        }
    }
}
