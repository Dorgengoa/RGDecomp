#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E7E60[];

extern s32 TargetMngDraw2_31edb0(void *);

s32 TaskDrawTargetMng2_313580(void)
{
    return TargetMngDraw2_31edb0(D_004E7E60);
}
