/* rgp:protos */
#define RGP_SELF_SaveMenuIconCellLookupMaybe_37b3d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E { s8 id; s8 a; s8 b; } E;
extern E D_00463A40[];

s8 SaveMenuIconCellLookupMaybe_37b3d0(s16 *arg0)
{
    s32 i;
    E *tbl;

    if (arg0 == NULL) {
        return -1;
    }
    if (arg0[0] == -1) {
        return -1;
    }
    for (i = 0; D_00463A40[i].id >= 0; i++) {
        if (arg0[4] == D_00463A40[i].a && arg0[5] == D_00463A40[i].b) {
            return ((s8 *)D_00463A40)[i * 3];
        }
    }
    return -1;
}
