/* rgp:protos */
#define RGP_SELF_MotionListSelectByNameAll_1720b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct N1720B0 { struct N1720B0 *f00; };
struct T1720B0 { u8 pad000[0x4]; struct N1720B0 *f04; };

/*rgp*/

void MotionListSelectByNameAll_1720b0(struct T1720B0 *p, void *a, void *b)
{
    struct N1720B0 *n;
    void *e;

    n = p->f04;
    while (n != 0) {
        e = (u8 *)n + 0x10;
        if (e != 0) {
            MotionPlayerSelectByName_173640(e, a, b);
        }
        n = n->f00;
    }
}
