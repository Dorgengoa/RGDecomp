#include "types.h"

typedef struct E8_241 {
    u8 b[8];
} E8_241;

typedef struct Msg241 {
    s32 m00;
    s32 m04;
    f32 m08;
    s32 m0C;
} Msg241;

typedef struct Ctx241 {
    u8    pad000[0x4];
    void *m4;
} Ctx241;

extern Ctx241 *gEventContext;
extern s32 ScriptGetInt_2490f0(E8_241 *p);
extern void Vec4VectorPushBack_249120(void *a, Msg241 *m);

s32 EvCmdCueStreamFadeIn_241310(E8_241 *p)
{
    Msg241 m;
    s32 r1;
    s32 r2;

    r1 = ScriptGetInt_2490f0(p++);
    r2 = ScriptGetInt_2490f0(p);
    m.m00 = 0x8;
    m.m04 = r1;
    m.m08 = 1.0f;
    m.m0C = (s32)(f32)r2;
    Vec4VectorPushBack_249120(gEventContext->m4, &m);
    return 1;
}
