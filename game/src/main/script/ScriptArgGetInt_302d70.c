/* rgp:protos */
#define RGP_SELF_ScriptArgGetInt_302d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 ScriptArgGetInt_302d70(u8 *p)
{
    s32 t;
    f32 f;

    if (*(s8 *)p == 0) {
        ((u8 *)&t)[0] = p[1];
        ((u8 *)&t)[1] = p[2];
        ((u8 *)&t)[2] = p[3];
        ((u8 *)&t)[3] = p[4];
        return t;
    }
    if (*(s8 *)p == 1) {
        ((u8 *)&f)[0] = p[1];
        ((u8 *)&f)[1] = p[2];
        ((u8 *)&f)[2] = p[3];
        ((u8 *)&f)[3] = p[4];
        return (s32)f;
    }
    return 0;
}
