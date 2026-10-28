/* rgp:protos */
#define RGP_SELF_StrVectorDtor_1a21a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of Vec3VectorDeletingDtor_1713b0 (byte-identical, in cunits):
   tear down, second release gated on a SIGNED 16-BIT argument; the null guard
   reaches the shared tail return by `goto`, not by its own `return self`. */

typedef struct ObjFUN_001a21a0 {
    u8 pad00[0x8];
    void *unk8;
} ObjFUN_001a21a0;

/*rgp*/
/*rgp*/

ObjFUN_001a21a0 *StrVectorDtor_1a21a0(ObjFUN_001a21a0 *self, s16 n)
{
    if (self == 0) {
        goto done;
    }
    StrVectorClear_1a5140((void *)self);
    if (self->unk8 != 0) {
        OperatorDelete_100840(self->unk8);
    }
    if (n > 0) {
        OperatorDelete_100840(self);
    }
done:
    return self;
}
