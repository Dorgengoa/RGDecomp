/* rgp:protos */
#define RGP_SELF_EffectEntriesReleaseAllNodesByName_2de2e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_002de2e0 {
    u8 pad000[0xB4];
    s16 fB4;
} Obj_FUN_002de2e0;

/*rgp*/
/*rgp*/

void EffectEntriesReleaseAllNodesByName_2de2e0(int rgp_a0, int rgp_a1)
{
    Obj_FUN_002de2e0 *o;

    o = ((Obj_FUN_002de2e0 *)EffectFindByNameNoId_2dfed0((int)rgp_a0, (int)rgp_a1));
    if (o != 0) {
        if (o->fB4 != 0) {
            EffectEntryReleaseAllNodes_2da430(o);
        }
    }
}
