#include "types.h"

/* Same body as JudgeObjectDefaultCtor_314690 with four extra parameters written after the
   JudgeObjectResetState_314730 call.  $f12 is saved into $f20 across the calls => a float
   parameter that outlives them. */

extern u8 D_00471AA0[];
extern void ExecInfoInit_3a7940(void *p);
extern void JudgeObjectResetState_314730(void *p);

void *JudgeObjectCtor_3145a0(void *self, s16 a, s16 b, s32 c, f32 t)
{
    u8 *p;

    p = (u8 *)self;
    ExecInfoInit_3a7940(p + 0x10);
    *(s32 *)(p + 0x00) = 0;
    *(s32 *)(p + 0x04) = 0;
    *(s32 *)(p + 0x08) = 0;
    *(s32 *)(p + 0x0C) = 0x3F800000;
    ExecInfoInit_3a7940(p + 0x10);
    *(s32 *)(p + 0x7C) = 0;
    *(s32 *)(p + 0x80) = 0;
    *(s16 *)(p + 0x84) = -1;
    *(s16 *)(p + 0x86) = -1;
    *(s16 *)(p + 0x88) = -1;
    *(s16 *)(p + 0x8A) = -1;
    *(s16 *)(p + 0x8C) = 0;
    *(s16 *)(p + 0x8E) = 0;
    *(s32 *)(p + 0x90) = 0;
    *(s32 *)(p + 0x94) = 0;
    *(s32 *)(p + 0x98) = 0;
    *(s32 *)(p + 0x9C) = 0;
    *(s32 *)(p + 0xA0) = -1;
    *(s16 *)(p + 0xA4) = 0;
    *(s16 *)(p + 0xA6) = 0;
    *(u8 **)(p + 0xB0) = D_00471AA0;
    JudgeObjectResetState_314730(p);
    *(s16 *)(p + 0x8A) = a;
    *(s16 *)(p + 0x86) = b;
    *(s16 *)(p + 0x88) = -1;
    *(s32 *)(p + 0x7C) = c;
    *(f32 *)(p + 0xC4) = t;
    return self;
}
