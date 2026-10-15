#include "types.h"
typedef struct { s32 a, b; } E8_244840;
struct O244840 { u8 pad000[0xA60]; s32 mA60; };
struct C244840 { u8 pad000[0x4]; struct O244840 *m04; };
extern struct C244840 * gEventContext;
extern s32 ScriptGetInt_2490f0(E8_244840 *);

s32 EvCmdEventPlayerSetFlags_244840(E8_244840 *p0, s32 p1)
{
    struct O244840 *o;
    s32 mask;
    s32 v;

    if (p1 != 2) {
        return 0;
    }
    o = gEventContext->m04;
    mask = ScriptGetInt_2490f0(p0++);
    v = ScriptGetInt_2490f0(p0);
    if (v != 0) {
        o->mA60 = o->mA60 | mask;
    } else {
        o->mA60 = o->mA60 & ~mask;
    }
    return 1;
}
