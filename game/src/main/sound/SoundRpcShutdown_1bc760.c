/* rgp:protos */
#define RGP_SELF_SoundRpcShutdown_1bc760 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/*rgp*/
extern void DisableIntc_117080(s32 arg0);
extern void RemoveIntcHandler(s32 arg0, s32 arg1);
extern s32 PollSema(s32 arg0);
extern void SignalSema(s32 arg0);
extern void DeleteSema(s32 arg0);
/*rgp*/
/*rgp*/

extern s32 D_0047E210;
extern s32 D_0047E214;
extern s32 D_0047E218;
extern s32 D_0047E21C;
extern s32 D_004814D8 __attribute__((section(".sdata")));
extern volatile s32 D_00481500;
extern volatile s32 D_00481504;

s32 SoundRpcShutdown_1bc760(void) {
    SoundRpcCall_1bc5e0(0x8400, 0);
    SoundRpcCall_1bc5e0(0x10, 0);
    DisableIntc_117080(3);
    if (D_0047E210 >= 0) {
        RemoveIntcHandler(3, D_0047E210);
    }
    if (D_0047E21C >= 0) {
        D_00481500 = 1;
        if (D_00481504 == 0) {
            D_00481504 = 1;
            if (PollSema(D_0047E214) < 0) {
                SignalSema(D_0047E214);
            }
            D_00481504 = 0;
        }
    }
    if (D_0047E214 >= 0) {
        DeleteSema(D_0047E214);
    }
    if (D_0047E218 >= 0) {
        DeleteSema(D_0047E218);
    }
    D_0047E21C = -1;
    D_0047E214 = -1;
    if (D_004814D8 != 0) {
        IopHeapFreeLocked_1c2290(D_004814D8);
    }
    SoundStreamSysShutdownMaybe_1bf780();
    return 1;
}
