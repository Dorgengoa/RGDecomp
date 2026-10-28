/* rgp:protos */
#define RGP_SELF_S16ArrayAlloc_1ce1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void S16ArrayAlloc_1ce1d0(void *arg0, s32 arg1, s32 arg2) {
    s32 t;

    S16ArrayReset_1ce240((void *)arg0);
    if (arg1 <= 0 || arg2 == 0) {
        return;
    }
    t = ((s32)MemStackNew_14e1b0(arg1 * 2, arg2));
    *(s32 *)((u8 *)arg0 + 0x0) = t;
    if (t != 0) {
        *(s16 *)((u8 *)arg0 + 0x4) = (s16)arg1;
    }
}
