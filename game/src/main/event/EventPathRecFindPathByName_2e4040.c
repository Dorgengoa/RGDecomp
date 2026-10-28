/* rgp:protos */
#define RGP_SELF_EventPathRecFindPathByName_2e4040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 EventPathRecFindPathByName_2e4040(void *arg0, s32 arg1) {
    s32 p;
    s32 i;

    p = *(s32 *)((u8 *)arg0 + 0x14);
    if (p == 0 || arg1 == 0) {
        return 0;
    }
    i = 0;
    while (i < *(s16 *)((u8 *)arg0 + 0x1A)) {
        if (((unsigned char)StrEqualNonNull_1ca6c0(arg1, EventPathGetName_2e4570(p))) != 0) {
            return p;
        }
        i += 1;
        p += 0x10;
    }
    return 0;
}
