/* rgp:protos */
#define RGP_SELF_insect_InsectPieceItemDefGetSpecies_5166d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005166D0 -- 152 bytes, 38 instructions. */

typedef struct A {
    u8  pad00[0x4];
    s16 f4;                         /* +0x04 */
} A;

typedef struct B {
    u8  pad00[0x4];
    struct C *f4;                   /* +0x04 */
} B;

typedef struct C {
    u8  pad00[0x4];
    s16 *f4;                        /* +0x04 */
    s16 f8;                         /* +0x08 */
} C;

/*rgp*/

void insect_InsectPieceItemDefGetSpecies_5166d0(A *a, s32 *o1, s32 *o2, s32 *o3)
{
    B *b;
    C *c;
    s16 *d;

    *o1 = -1;
    *o2 = -1;
    if (a != 0) {
        b = ((B *)ItemDefGetInsectData_40e0b0((void *)a));
        if (b != 0) {
            c = b->f4;
            if (c != 0) {
                d = c->f4;
                if (d != 0) {
                    *o1 = a->f4 - 0x7D0;
                    *o2 = c->f8;
                    *o3 = *d;
                }
            }
        }
    }
}
