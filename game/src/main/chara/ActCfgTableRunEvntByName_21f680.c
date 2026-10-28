/* rgp:protos */
#define RGP_SELF_ActCfgTableRunEvntByName_21f680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Look the thing up, then act on it. The first argument is never touched
   before the lookup, so it rides through in $4; the third moves into $5 and
   the second is parked in $16 for the second call. */

/*rgp*/
/*rgp*/

void ActCfgTableRunEvntByName_21f680(void *self, void *arg, void *key)
{
    void *found;

    found = ActCfgTableFindEvntByName_222960(self, key);
    if (found != 0) {
        ScriptListRun_22f110(found, arg);
    }
}
