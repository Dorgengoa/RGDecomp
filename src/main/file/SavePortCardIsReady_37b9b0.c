#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E90F0[];

extern s32 McCardIsReady_376280(void *, s32);

s32 SavePortCardIsReady_37b9b0(s32 a4)
{
    return McCardIsReady_376280(D_004E90F0, a4);
}
