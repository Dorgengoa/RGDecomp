#include "types.h"

extern u8 *D_004DB930[3];

typedef struct Elem002c6eb0 {
    u8 pad0[0x8];
} Elem002c6eb0;

void ScriptSlotStoreIntRef_2cc900(Elem002c6eb0 *elem, s32 value);

s32 AiCmdGetTargetParams_2c6eb0(Elem002c6eb0 *arg0)
{
    Elem002c6eb0 *self;

    self = arg0;
    ScriptSlotStoreIntRef_2cc900(self++, *(s16 *)(D_004DB930[0] + 0x13C));
    ScriptSlotStoreIntRef_2cc900(self++, *(s16 *)(D_004DB930[0] + 0x13E));
    ScriptSlotStoreIntRef_2cc900(self, *(s16 *)(D_004DB930[0] + 0x140));
    return 1;
}
