#include "types.h"
#include "eekernel.h"

extern s32 D_00481504;
extern s32 D_00481508;
extern s32 D_0047E214;
extern s32 iPollSema(s32 sema_id);
extern s32 iSignalSema(s32 sema_id);

s32 SoundVblankIntrHandler_1bd6f0(void)
{
    if (D_00481504 == 0) {
        D_00481504 = 1;
        if (iPollSema(D_0047E214) < 0) {
            iSignalSema(D_0047E214);
        }
        D_00481504 = 0;
    }
    D_00481508++;
    ExitHandler();
    return 0;
}
