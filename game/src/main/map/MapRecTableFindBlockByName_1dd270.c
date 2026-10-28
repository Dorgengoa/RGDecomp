/* rgp:protos */
#define RGP_SELF_MapRecTableFindBlockByName_1dd270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct P1dd270 { u8 pad0[0x3A]; s16 f3A; u8 pad3C[8]; u8 *f44; };

/*rgp*/
/*rgp*/

u8 *MapRecTableFindBlockByName_1dd270(struct P1dd270 *p0, s8 *name)
{
    u8 *e;
    s32 i;
    s8 c;

    if (name == 0) {
        return 0;
    }
    e = p0->f44;
    if (e == 0) {
        return 0;
    }
    for (i = 0; i < p0->f3A; i++, e += 0xCC) {
        if (((s8 *)MapDataGetName_1e7bf0(e)) == 0) {
            continue;
        }
        c = *name;
        if (c != *((s8 *)MapDataGetName_1e7bf0(e))) {
            continue;
        }
        if (StrNotEqual_1f5300(((s8 *)MapDataGetName_1e7bf0(e)) + 1, name + 1) != 0) {
            continue;
        }
        return e;
    }
    return 0;
}
