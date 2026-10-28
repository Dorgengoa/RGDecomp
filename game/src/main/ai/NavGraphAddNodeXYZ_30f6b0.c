/* rgp:protos */
#define RGP_SELF_NavGraphAddNodeXYZ_30f6b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MEASURED (q12 sweep, 6 arms): the four gp-relative float constants are TWO
   8-BYTE PAIR COPIES, not four scalar assignments.  Four scalars, a 4-member
   struct and a named-tail-local are ONE object (sha1 355453a3) and all miss by
   two words -- the scheduler puts swc1 $f12 ahead of the last init store.
   $4 is never rewritten: `self` is passed straight through to the callee. */
typedef struct P2 { f32 a; f32 b; } P2;
extern P2 D_0047F1E0;
extern P2 D_0047F1E8;
/*rgp*/
unsigned int NavGraphAddNodeXYZ_30f6b0(void *self, f32 x, f32 y, f32 z, f32 t)
{
    f32 v[4] __attribute__((aligned(16)));
    *(P2 *)&v[0] = D_0047F1E0;
    *(P2 *)&v[2] = D_0047F1E8;
    v[0] = x; v[1] = y; v[2] = z;
    return NavGraphAddNode_30f570(self, v, t);
}
