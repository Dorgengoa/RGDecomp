/* rgp:protos */
#define RGP_SELF_StrVectorClear_1a5140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

struct Sub_1a5140 {
    s32 m00;
    u8 pad004[0x4];
    void *m08;
};

struct Ent_1a5140 {
    u8 pad000[0x4];
    struct Sub_1a5140 s04;
};

struct Obj_1a5140 {
    u8 pad000[0x4];
    s32 m04;
    struct Ent_1a5140 *m08;
};

void StrVectorClear_1a5140(struct Obj_1a5140 *o)
{
    struct Ent_1a5140 *base;
    struct Ent_1a5140 *p;

    base = o->m08;
    p = o->m08 + o->m04;
    while (base < p) {
        p -= 1;
        if (p != 0) {
            if (&p->s04 != 0) {
                if ((p->s04.m00 & 1) != 0) {
                    OperatorDelete_100840(p->s04.m08);
                }
            }
        }
    }
    o->m04 = 0;
}
