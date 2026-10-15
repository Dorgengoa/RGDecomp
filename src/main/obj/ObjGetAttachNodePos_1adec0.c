#include "types.h"
#include "vec.h"

/* Fill "out" with the default at +0x180, then try to replace it with the
   node the index selects. The default copy sits in the OUTER GUARD'S DELAY
   SLOT, so it happens before the bounds check and survives every failure
   path: "out" is always written, and the return value is what says whether
   the node was found. Guard pair, constant bound 3.

   The bounds test is spelled DIRECTLY in the if, with no u8 holding it:
   retail lands the compare in $at, and the recorded reading of $at is that
   the condition was never stored in a variable. The rest of the guard-pair
   class puts it in a u8 and lands in $v0 -- so the class recipe's shared
   label is right here and its "u8 ok" is not.

   RESIDUE: 2 words of 26, and they are only the REGISTER. Retail writes
   "slti at, a1, 3" / "bnezl at"; mwcc writes the same two instructions into
   $v0. Three spellings measured, all identical output: the u8 form, the
   direct "index < 3" form, and the reversed "3 > index" form. $2 is dead by
   then in both arms -- the Vec4 it carried was consumed by the sq in the
   outer guard's delay slot -- so this is not register pressure, and no lever
   for choosing $at has been found here. */

typedef struct Obj001adec0 {
    u8 pad000[0x180];
    Vec4 fallback;      /* +0x180 */
    u8 pad190[0x46C - 0x190];
    s32 id[3];          /* +0x46C */
} Obj001adec0;

extern void *ModelGetFrame_1511f0(Obj001adec0 *self, s32 id);
extern void FrameGetWorldPos_148f30(void *node, Vec4 *out);

s32 ObjGetAttachNodePos_1adec0(Obj001adec0 *self, s32 index, Vec4 *out)
{
    void *node;

    *out = self->fallback;
    if (index < 0) {
        goto none;
    }
    if (index <= 2) {
        goto found;
    }
none:
    return 0;
found:
    node = ModelGetFrame_1511f0(self, self->id[index]);
    if (node == 0) {
        return 0;
    }
    FrameGetWorldPos_148f30(node, out);
    return 1;
}
