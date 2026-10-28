/* rgp:protos */
#define RGP_SELF_PadPortOpen_184ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* if/else with the error arm laid out LAST: both guards branch away to the
   shared -1 block, so it is an && with an else, not two early returns. */

extern s32 D_0047E03C;

/*rgp*/
extern s32 WaitSema(s32 id);
extern s32 SignalSema(s32 id);
extern s32 scePadPortOpen(s32 port, s32 slot, void *addr);
extern void sceGsSyncV(s32 mode);

void PadPortOpen_184ed0(u8 *p, s32 port, s32 slot, void *addr)
{
    s32 r;

    PadStateInit_184f90(p);
    *(s32 *)(p + 0xB4) = port;
    *(s32 *)(p + 0xB8) = slot;
    if (slot >= 0 && *(s32 *)(p + 0xB4) >= 0) {
        WaitSema(D_0047E03C);
        r = scePadPortOpen(*(s32 *)(p + 0xB4), *(s32 *)(p + 0xB8), addr);
        SignalSema(D_0047E03C);
        if (r == 1) {
            sceGsSyncV(0);
            sceGsSyncV(0);
        }
    } else {
        *(s32 *)(p + 0xB4) = -1;
        *(s32 *)(p + 0xB8) = -1;
    }
}
