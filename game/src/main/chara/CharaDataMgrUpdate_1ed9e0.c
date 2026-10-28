/* rgp:protos */
#define RGP_SELF_CharaDataMgrUpdate_1ed9e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004B2570[];

int CharaDataMgrUpdate_1ed9e0(void *arg0)
{ int rgp_v0 = 0;
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
    if ((rgp_v0 = ReturnZero_207fe0()) != 0) {
        (rgp_v0 = PadIsTriggered_1839f0(D_004B2570, 0x100));
    }
return rgp_v0; }
