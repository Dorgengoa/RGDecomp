#include "types.h"

/* Known-positive sibling shape of MapAreaDataDupResLogStubMaybe_1e9920 (byte-identical, in cunits). */

extern void SpaceMenuResRelease_2046c0(void);
extern void MenuSpaceStackRelease_206560(void);

void SpaceMenuClose_204690(void)
{
    SpaceMenuResRelease_2046c0();
    MenuSpaceStackRelease_206560();
}
