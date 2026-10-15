#include "types.h"

extern void SplinePathAddPoint_256c10(void *, void *);

s32 EvSubNodeSplineAddPoint_253370(void *a, void *b)
{
    SplinePathAddPoint_256c10((u8 *)b + 0x140, (u8 *)a + 0x10);
    return 0;
}
