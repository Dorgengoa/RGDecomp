#include "types.h"

f32 ScriptArgGetFloat_302cf0(u8 *p)
{
    f32 f;
    s32 t;

    if (*(s8 *)p == 1) {
        ((u8 *)&f)[0] = p[1];
        ((u8 *)&f)[1] = p[2];
        ((u8 *)&f)[2] = p[3];
        ((u8 *)&f)[3] = p[4];
        return f;
    }
    if (*(s8 *)p == 0) {
        ((u8 *)&t)[0] = p[1];
        ((u8 *)&t)[1] = p[2];
        ((u8 *)&t)[2] = p[3];
        ((u8 *)&t)[3] = p[4];
        return (f32)t;
    }
    return 0.0f;
}
