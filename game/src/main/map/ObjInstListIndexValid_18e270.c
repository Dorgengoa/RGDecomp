/* rgp:protos */
#define RGP_SELF_ObjInstListIndexValid_18e270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 ObjInstListIndexValid_18e270(void *a, s32 n)
{
    if (n < 0 || n >= 0x7) {
        return 0;
    }
    return 1;
}
