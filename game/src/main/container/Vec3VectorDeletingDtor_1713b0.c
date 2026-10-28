/* rgp:protos */
#define RGP_SELF_Vec3VectorDeletingDtor_1713b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tear down, with the second release gated on a SIGNED 16-BIT argument: the
   `dsll32 16` / `dsra32 16` pair before the `blezl` is a 16-bit sign
   extension, which is what says the parameter is an `s16` and not an `s32`.

   The receiver comes back on every path, and the null guard has to reach it
   by `goto`, not by its own `return self`. Retail's `beqz` jumps straight
   into the shared `daddu v0, s1, zero` that the fall-through also uses; an
   inline return builds a second copy of it plus a `b`, two words long.
   Same lever as ObjRecHasFlags6_1c3eb0 and the guard-pair class -- a `goto` to a tail
   return beats an inline one whenever the value is already in place. */

typedef struct Obj001713b0 {
    u8 pad00[0x8];
    void *unk8;
} Obj001713b0;

/*rgp*/
/*rgp*/

Obj001713b0 *Vec3VectorDeletingDtor_1713b0(Obj001713b0 *self, s16 n)
{
    if (self == 0) {
        goto done;
    }
    Vec3VectorClear_171420((void *)self);
    if (self->unk8 != 0) {
        OperatorDelete_100840(self->unk8);
    }
    if (n > 0) {
        OperatorDelete_100840(self);
    }
done:
    return self;
}
