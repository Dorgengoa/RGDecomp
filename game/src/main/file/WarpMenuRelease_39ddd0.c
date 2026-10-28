/* rgp:protos */
#define RGP_SELF_WarpMenuRelease_39ddd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x1C];
    s32 unk1C;
    s32 unk20;
} Obj0039DDD0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void WarpMenuRelease_39ddd0(Obj0039DDD0 *arg0) {
    s32 temp_4;
    s32 temp_5;
    s32 var_16;

    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x330);
    temp_5 = arg0->unk20;
    if (temp_5 != 0) {
        temp_4 = arg0->unk1C;
        if (temp_4 != 0) {
            MemStackHeapFree_14dcb0(temp_4, temp_5);
        }
    }
    var_16 = 0;
    do {
        LoaderReleaseHandle_1ccb70((u8 *)arg0 + (var_16 * 0xC));
        var_16 += 1;
    } while (var_16 < 2);
    WarpMenuReset_39e020(arg0);
}
