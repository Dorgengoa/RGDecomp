/* rgp:protos */
#define RGP_SELF_EntryReset_323c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void EntryReset_323c20(s32 *arg0) {
    EntrySetGridSize_323bd0(arg0, 0, 0);
    EntrySetScale_323c10(arg0, 0.0f);
    EntrySetOrigin_323c00(arg0, 0.0f, 0.0f);
    EntrySetRange_323bf0(arg0, 0.0f, 0.0f);
    EntrySetPair20Related_323be0(arg0, 0, 0);
    *arg0 = 0;
    EntrySetBlockName_323960(arg0, 0);
    EntrySetName_323910(arg0, 0);
    EntrySetExploredOffset_323900(arg0, 0);
    EntrySetGroupId_3238e0(arg0, -1);
}
