/* rgp:protos */
#define RGP_SELF_normal_InsectEntryMenuGetResult_524ce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00524CE0 -- the same eight-byte float-pair copy as normal_BtlChgPageGetAbilityReq_5052d0
 * with the source in SMALL DATA.  A struct assignment, not two member
 * assignments; see that file.  Eight bytes is under mwcc's small-data
 * threshold so the pair keeps its `%gp_rel`.
 * One of the 55 unnamed functions. */
typedef struct Pair {
    f32 x;
    f32 y;
} Pair;

extern Pair D_004849D0;

void normal_InsectEntryMenuGetResult_524ce0(Pair *o)
{
    *o = D_004849D0;
}
