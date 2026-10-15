#include "types.h"

/* MAIN GameSceneDofSetOverridePreset_2f6ab0.  The +0x10 member is stored TWICE with the same
   value -- the `cvt.s.w` of 0x1388 is not folded, so the 5000 arrives
   through an integer local, and the duplicate store is in the source.  */

extern void *GetCurrentScene_1f5be0(void);
extern void GameSceneDofSetParams_1cf1b0(void *, void *);

typedef struct Cfg6ab0 {
    s32 m00;
    f32 m04;
    f32 m08;
    f32 m0C;
    f32 m10;
} Cfg6ab0;

void GameSceneDofSetOverridePreset_2f6ab0(void)
{
    Cfg6ab0 c;
    u8 *o;
    s32 n;

    o = GetCurrentScene_1f5be0();
    c.m00 = 1;
    c.m04 = 1.0f;
    c.m08 = 4000.0f;
    c.m0C = 4000.0f;
    n = 5000;
    c.m10 = (f32)n;
    c.m10 = (f32)n;
    GameSceneDofSetParams_1cf1b0(o, &c);
    *(s32 *)(o + 0x5968) = 1;
}
