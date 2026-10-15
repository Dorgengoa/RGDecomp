#include "types.h"

/* Same materialised-boolean guard as FileReqThreadShutdown_182a50. */

extern void sceGsSyncV(s32 mode);
extern s32 scePadGetState(s32 a, s32 b);
extern u32 PadUpdateConnection_184a50(void *p, s32 a, s32 b, s32 c);

void PadWaitReady_1849e0(u8 *p)
{
    sceGsSyncV(0);
    while ((s32)!(PadUpdateConnection_184a50(p + 4, *(s32 *)(p + 0xB4), *(s32 *)(p + 0xB8),
                               *(s32 *)(p + 0xBC)) > 0) != 0) {
        sceGsSyncV(0);
        if (scePadGetState(*(s32 *)(p + 0xB4), *(s32 *)(p + 0xB8)) == 0) {
            break;
        }
    }
}
