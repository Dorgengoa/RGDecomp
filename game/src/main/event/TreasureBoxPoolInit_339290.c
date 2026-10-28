/* rgp:protos */
#define RGP_SELF_TreasureBoxPoolInit_339290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 f0;
    s32 *f4;
    s16 f8;
    u8  b0 : 1;
    u8  b1 : 1;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TreasureBoxPoolInit_339290(Obj *self, s32 n)
{
    s32 r;
    s32 i;
    s32 *s;
    s32 j;

    if (n == 0) {
        return 0;
    }
    self->f0 = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e0b0(0x1010, n)), TreasureBoxCtor_3393a0, 0, 0x80, 0x20));
    if (self->f0 == 0) {
        return 0;
    }
    self->f4 = (s32 *)((s32)MemStackNew_14e0b0(0x80, n));
    if (self->f4 == 0) {
        return 0;
    }
    r = self->f0;
    i = 0;
    do {
        TreasureBoxReset_33b4c0(r);
        i++;
        r += 0x80;
    } while (i < 0x20);
    s = self->f4;
    j = 0;
    do {
        j++;
        *s = 0;
        s++;
    } while (j < 0x20);
    self->f8 = 0;
    self->b0 = 1;
    self->b1 = 1;
    return 1;
}
