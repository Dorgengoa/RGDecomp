/* protos fixture (lane tentacle, docs/PROTOS.md "Code macros are not return types"):
   a code macro line without `;` before a call must not make the call a declaration
   (FrameUpdateWorld_149680's `XS` / `ScaleMul();`). */
#include "types.h"

#define SPLIT401000(p) if (p) { p = (s32 *)(s32)(u32)p; }
#define XS SPLIT401000(q)

static inline void Step_401000(void)
{
}

void StmtMacro_401000(s32 *q)
{
    XS
    Step_401000();
    XS
}
