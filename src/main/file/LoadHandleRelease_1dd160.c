#include "types.h"

/* Known-positive sibling shape of AreaBoxInit_1e01f0 (byte-identical, in cunits). */

extern void LoaderReleaseHandle_1ccb70(void);
extern void LoadHandleResetThunk_1ccc10(s32);

void LoadHandleRelease_1dd160(s32 p0)
{
    LoaderReleaseHandle_1ccb70();
    LoadHandleResetThunk_1ccc10(p0);
}
