/* rgp:protos */
#define RGP_SELF_EntryGridGetCell_323a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EntryGridGetCell_323a60(s32 *arg0, s32 arg1) {
    s32 a;
    s32 b;
    s32 prod;

    EntryGetGridSize_323bb0(arg0, &a, &b);
    prod = a * b;
    if (arg1 < 0 || arg1 >= prod) {
        return 0;
    }
    return *arg0 + arg1 * 3;
}
