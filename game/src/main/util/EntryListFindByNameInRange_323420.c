/* rgp:protos */
#define RGP_SELF_EntryListFindByNameInRange_323420 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(s32, s32);

s32 EntryListFindByNameInRange_323420(s32 arg0, s32 arg1, f32 fparg0, f32 fparg1) {
    f32 sp5C;
    f32 sp58;
    s32 var_2;

    if (arg1 == 0) {
        return 0;
    }
    EntryListGetCurIndex_3238b0((void *)arg0);
    var_2 = EntryListSelectByIndex_323540(arg0, 0);
    while (var_2 != 0) {
        if (strcmp(var_2 + 0x54, arg1) == 0) {
            EntryGetRange_323af0(var_2, &sp5C, &sp58);
            if (((sp5C - fparg1) <= fparg0) && (fparg0 <= (sp58 + fparg1))) {
                return var_2;
            }
        }
        var_2 = EntryListSelectNext_323500(arg0);
    }
    return 0;
}
