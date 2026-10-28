/* rgp:protos */
#define RGP_SELF_MapFindAreaBlockBoxAtPos_1e3ac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void MapFindAreaBlockBoxAtPos_1e3ac0(s32 a, s32 *b, s32 c, s32 *d, s32 e, f32 v)
{
    s32 t;

    MapFindSmallestBlockAtPos_1e3b50(a, &t, c, e, v);
    if (b != 0) {
        *b = t;
    }
    if (d == 0) return;
    if (t != 0) {
        *d = MapAreaFindSmallestBoxAt_1db350(t, e, v);
    } else {
        *d = 0;
    }
}
