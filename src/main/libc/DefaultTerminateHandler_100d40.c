#include "types.h"

#pragma tailcall off

extern void Abort_12de80(void);

void DefaultTerminateHandler_100d40(void)
{
    Abort_12de80();
}
