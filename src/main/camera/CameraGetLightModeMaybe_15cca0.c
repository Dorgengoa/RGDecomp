#include "types.h"
typedef struct A15CCA0 { u8 pad000[0xC]; s32 m0C; } A15CCA0;
typedef struct B15CCA0 { u8 pad000[0xF20]; A15CCA0 *mF20; } B15CCA0;
extern B15CCA0 *D_004810A4;
s32 CameraGetLightModeMaybe_15cca0(void)
{
    B15CCA0  *b;
    A15CCA0  *a;

    b = D_004810A4;
    /* the TRUE arm is the one threaded into the `bnel` slot. */
    a = (b == 0) ? 0 : b->mF20;
    return a->m0C;
}
