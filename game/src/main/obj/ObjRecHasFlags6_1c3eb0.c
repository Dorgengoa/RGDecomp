/* rgp:protos */
#define RGP_SELF_ObjRecHasFlags6_1c3eb0 1
#include "port/game_protos.h"
#line 1
#include "objrec.h"

/* Are BOTH flag bits 1 and 2 set?

   Two recipes at once. The xor/sltiu pair is the C++ bool idiom -- a u8 local
   assigned from an equality test. And the null case is reached by `goto` to a
   tail return, not by an inline `return 0`: retail's `beql` carries the zero
   in its own delay slot and jumps straight to the epilogue, which is one word
   shorter than the block an inline return produces. */

u8 ObjRecHasFlags6_1c3eb0(void *owner, s32 which, s32 index)
{
    ObjRec *r;
    u8 both;

    r = ObjRecLookup_1c3ef0(owner, which, index);
    if (r == 0) {
        goto none;
    }
    both = (r->flags & 6) == 6;
    return both;
none:
    return 0;
}
