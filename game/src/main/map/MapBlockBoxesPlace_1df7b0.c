/* rgp:protos */
#define RGP_SELF_MapBlockBoxesPlace_1df7b0 1
#include "port/game_protos.h"
#line 1
/* main s27m: CLOSED -- MapDataGetRotVec4_1e7720 takes (arg0, buf): retail never writes $a0. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MapBlockBoxesPlace_1df7b0(s32 arg0, s32 arg1, f32 fparg0)
{
    s32 var_20;
    s32 var_19_2;
    s32 var_19;
    s32 var_18;
    s32 temp_18;
    s32 temp_17;
    u8 sp80[0x10] __attribute__((aligned(16)));
    u8 sp70[0x10] __attribute__((aligned(16)));

    MapDataGetRotVec4_1e7720(arg0, sp80);
    MapDataGetPosVec4_1e7740(arg0, sp70);
    AreaBoxPlaceThunk_1e94a0(arg0 + 0x74, sp70, *(f32 *)(sp80 + 4));
    var_20 = MapBlockGetBoxArray1_1dfec0(arg0);
    if (var_20 != 0) {
        temp_18 = MapBlockGetBoxCount1_1dfeb0(arg0);
        var_19 = 0;
        while (var_19 < temp_18) {
            AreaBoxPlace_1e94a0(var_20, arg1, fparg0);
            var_19 += 1;
            var_20 += 0x4C;
        }
    }
    var_19_2 = MapBlockGetBoxArray2_1dfea0(arg0);
    if (var_19_2 != 0) {
        temp_17 = MapBlockGetBoxCount2_1dfe90(arg0);
        var_18 = 0;
        while (var_18 < temp_17) {
            AreaBoxPlace_1e94a0(var_19_2, arg1, fparg0);
            var_18 += 1;
            var_19_2 += 0x4C;
        }
    }
}
