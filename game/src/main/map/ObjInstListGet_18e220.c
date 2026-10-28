/* rgp:protos */
#define RGP_SELF_ObjInstListGet_18e220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

u8 *ObjInstListGet_18e220(u8 *p, s32 i)
{
    if (ObjInstListIndexValid_18e270(p, (int)i) != 0) {
        return p + i * 12 + 0x4B0;
    }
    return 0;
}
