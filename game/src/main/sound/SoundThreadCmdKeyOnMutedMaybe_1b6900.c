/* rgp:protos */
#define RGP_SELF_SoundThreadCmdKeyOnMutedMaybe_1b6900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_func_001B6900 {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
} Obj_func_001B6900;

/*rgp*/

s32 SoundThreadCmdKeyOnMutedMaybe_1b6900(Obj_func_001B6900 *o)
{
    SoundIopSendCmdG3S2_165f20(o->f00, 0x11, o->f04, o->f08, o->f0C, o->f10, o->f14, o->f18,
                 o->f1C);
    SoundIopSendCmdG3S2_165f20(o->f00, 0x42, o->f04, o->f10, o->f14, 0);
    return 0;
}
