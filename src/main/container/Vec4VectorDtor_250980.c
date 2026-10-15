#include "types.h"

/* Known-positive sibling shape of Vec3VectorDeletingDtor_1713b0 (byte-identical, in cunits):
   tear down, second release gated on a SIGNED 16-BIT argument; the null guard
   reaches the shared tail return by `goto`, not by its own `return self`. */

typedef struct ObjFUN_00250980 {
    u8 pad00[0x8];
    void *unk8;
} ObjFUN_00250980;

extern void Vec4VectorClear_250970(void);
extern void OperatorDelete_100840(void *p);

ObjFUN_00250980 *Vec4VectorDtor_250980(ObjFUN_00250980 *self, s16 n)
{
    if (self == 0) {
        goto done;
    }
    Vec4VectorClear_250970();
    if (self->unk8 != 0) {
        OperatorDelete_100840(self->unk8);
    }
    if (n > 0) {
        OperatorDelete_100840(self);
    }
done:
    return self;
}
