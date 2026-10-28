/* rgp:protos */
#define RGP_SELF_ObjRecLookup_1c3ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The dispatcher in front of the bounds-accessor family: kinds 3, 2 and 1 go
   to ObjRecTableGet_1c3f60, ObjRecTableGet_1c3fa0 and ObjRecTableGet_1c3fe0, anything else returns 0.
   Three of those four are already byte-identical units in this tree.

   ★ It is a `switch`, not an if-chain, and the layout is what says so:
   retail TESTS descending (3, then 2, then 1) and lays the BODIES out
   ascending (1, 2, 3), each reached by a forward branch. An if-chain in
   source order emits the bodies in the order they are tested. Retail tests 3
   with a PLAIN `beq` -- its delay slot holds the prologue's `sd $31`, the
   only instruction available before the first test -- and 2 and 1 with likely
   branches carrying the argument shuffle. */

/*rgp*/
/*rgp*/
/*rgp*/

s32 ObjRecLookup_1c3ef0(void *self, s32 kind, void *arg)
{
    switch (kind) {
    case 1:
        return ((s32)ObjRecTableGet_1c3fe0(self, arg));
    case 2:
        return ((s32)ObjRecTableGet_1c3fa0(self, arg));
    case 3:
        return ((s32)ObjRecTableGet_1c3f60(self, arg));
    }
    return 0;
}
