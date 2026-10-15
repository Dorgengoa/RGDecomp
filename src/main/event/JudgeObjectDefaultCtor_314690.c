#include "types.h"

/* Constructor.  The 1.0f and the -1s are built with lui/addiu and stored as
   integers; bit patterns and float literals are interchangeable here.  The
   store that sits in a jal's delay slot PRECEDES that call in source order. */

extern u8 D_00471AA0[];
extern void ExecInfoInit_3a7940(void *p);
extern void JudgeObjectResetState_314730(void *p);

void *JudgeObjectDefaultCtor_314690(void *self)
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
    return self;
}
