#include "types.h"

extern void CharaDataRecUpdate_1ee2a0(void *arg0);
extern s32 ReturnZero_207fe0(void);
extern void PadIsTriggered_1839f0(void *arg0, s32 arg1);
extern u8 D_004B2570[];

void CharaDataMgrUpdate_1ed9e0(void *arg0)
{
    s32 i;
    void *elem;
    u8 ok;

    for (i = 0; i < 0x20; i++) {
        elem = (u8 *)arg0 + i * 0x74;
        ok = *(s16 *)((u8 *)elem + 0x62) >= 0;
        if (ok) {
            CharaDataRecUpdate_1ee2a0(elem);
        }
    }
    if (ReturnZero_207fe0() != 0) {
        PadIsTriggered_1839f0(D_004B2570, 0x100);
    }
}
