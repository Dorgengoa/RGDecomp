#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E7E60[];

extern s32 TargetMngDraw1_31edf0(void *);

s32 TaskDrawTargetMng1_313590(void)
{
    return TargetMngDraw1_31edf0(D_004E7E60);
}
