/* rgp:protos */
#define RGP_SELF_HashTableClear_1a9f20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

struct Node_1a9f20 {
    struct Node_1a9f20 *m00;
};

struct Obj_1a9f20 {
    s32 m00;
    u8 pad004[0x4];
    struct Node_1a9f20 **m08;
};

void HashTableClear_1a9f20(struct Obj_1a9f20 *h)
{
    s32 i;
    struct Node_1a9f20 *p;
    struct Node_1a9f20 *nx;

    if (h->m08 != 0) {
        for (i = 0; i < h->m00; i++) {
            p = h->m08[i];
            while (p != 0) {
                nx = p->m00;
                OperatorDelete_100840(p);
                p = nx;
            }
            h->m08[i] = 0;
        }
        OperatorDeleteArray_100820(h->m08);
        h->m08 = 0;
        h->m00 = 0;
    }
}
