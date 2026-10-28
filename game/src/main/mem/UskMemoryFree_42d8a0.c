/* rgp:protos */
#define RGP_SELF_UskMemoryFree_42d8a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct {
    u8 pad0[0x10];
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
} Buf;

typedef struct {
    u8 pad0[0x40];
    s32 x40;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 UskMemoryFree_42d8a0(Obj *self, u8 *arg1, s32 arg2)
{
    Buf b __attribute__((aligned(16)));
    Buf *pb;
    s32 r;
    s32 f;

    if (arg1 == NULL) {
        return 0;
    }
    f = self->x40;
    if (f & 2) {
        return 0;
    }
    if (f & 1) {
        return 0;
    }
    self->x40 = f | 1;
    if (arg1 == NULL) {
        r = 0;
    } else {
        pb = &b;
        DListNodeInit_42ec10(pb);
        DListNodeInit_42ec10(pb);
        pb->x14 = 0;
        pb->x10 = 0;
        arg1 -= (u8 *)(&b + 1) - (u8 *)&b;
        pb->x18 = 0;
        DListNodeDetach_42eb50(&b);
        b.x14 = 0;
        b.x10 = 0;
        b.x18 = 0;
        DListNodeDetach_42eb50(pb);
        if (arg1 == NULL) {
            r = 0;
        } else if (DListContains_42e9d0(self, arg1) == 0) {
            r = 0;
        } else {
            r = ((s32)HeapBlockFreeCoalesce_42d9c0(self, arg1, arg2, 0)) != 0;
        }
    }
    self->x40 &= ~1;
    return r;
}
