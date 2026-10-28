/* rgp:protos */
#define RGP_SELF_MapDataDraw_1e63b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[8];
    s32 unk8;
} Obj001E63B0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern char D_0045B4B0[32];

void MapDataDraw_1e63b0(Obj001E63B0 *arg0, s32 arg1) {
    s32 temp_2;

    if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980((int)arg0)) != 0 && arg0->unk8 != 0) {
        if (((unsigned char)MapDataHasSkyParts_1e7ab0(arg0)) != 0) {
            temp_2 = MapDataFindObjByName_1e71d0(arg0, D_0045B4B0);
            if (temp_2 != 0) {
                NodeSetTranslation_1866b0(temp_2, arg1);
            }
        }
        MapAreaDataDraw_1e8290(arg0->unk8, arg1);
    }
}
