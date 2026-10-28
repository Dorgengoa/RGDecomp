/* rgp:protos */
#define RGP_SELF_LoaderIsIdle_1cd5b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 LoaderIsIdle_1cd5b0(void *arg0) {
    u8 *base = (u8 *)arg0;

    if (((short)S16ArrayGetCount_1ce1b0(base + 0x28)) > 0) {
        return 0;
    }
    if (((short)S16ArrayGetCount_1ce1b0(base + 0x20)) > 0) {
        return (s16)S16ArrayGetChecked_1ce170(base + 0x20, 0) == 0x3FFF;
    }
    return 1;
}
