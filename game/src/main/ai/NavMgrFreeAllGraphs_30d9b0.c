/* rgp:protos */
#define RGP_SELF_NavMgrFreeAllGraphs_30d9b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Retail branches INTO the condition (`b .L0030D9E8`): that is a `while
   (expr)` with the test at the bottom.  A `for(;;) { cond; if (!p) break; }`
   rotates the test to the top and costs two words.
   MEASURED (q12 sweep, 7 arms): the two `self + 4` arguments must be spelled
   as a STRUCT MEMBER ADDRESS.  `(u8 *)self + 4` written twice is one word too
   long (mwcc CSEs it inside the loop), and mixing two spellings is worse
   still -- it hoists the address into a THIRD callee-saved register and costs
   the extra sq/lq pair as well (`(u8*)self+4` twice, a named result local and
   a named `q` local are ONE object, sha1 b7b530e8).
   Retail FALLS THROUGH into `p = 0` at BOTH tests, so both ternaries have the
   null as their else-... i.e. `== 0 ? 0 : value`. */

typedef struct Sub0030d9b0 {
    s32 x;
} Sub0030d9b0;

typedef struct Obj0030d9b0 {
    u8 pad00[4];
    Sub0030d9b0 sub;
    u8 pad08[4];
    void *m0C;
    s32 m10;
} Obj0030d9b0;

/*rgp*/
/*rgp*/
/*rgp*/

void NavMgrFreeAllGraphs_30d9b0(Obj0030d9b0 *self)
{
    void *p;

    while ((p = (self->m0C == 0)
                ? (void *)0
                : ((self->m10 == 0) ? (void *)0 : *(void **)self->m0C)) != 0) {
        NavGraphRelease_311170(p);
        NavMgrFreeGraph_30cbc0(&self->sub, NavMgrIndexOf_30cd50(&self->sub, p));
    }
}
