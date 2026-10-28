/* rgp:protos */
#define RGP_SELF_normal_TransMenuGetWarpRequest_518620 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00518620 -- the same eight-byte float-pair copy as normal_BtlChgPageGetAbilityReq_5052d0
 * with the source in SMALL DATA.  A struct assignment, not two member
 * assignments; see that file.  Eight bytes is under mwcc's small-data
 * threshold so the pair keeps its `%gp_rel`.
 * One of the 55 unnamed functions. */
typedef struct Pair {
    f32 x;
    f32 y;
} Pair;

extern Pair D_00484738;

void normal_TransMenuGetWarpRequest_518620(Pair *o)
{
    *o = D_00484738;
}
