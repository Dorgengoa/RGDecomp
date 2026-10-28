/* rgp:protos */
#define RGP_SELF_CdDiscSelect_1c3090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0048155C;
extern s32 D_00481560;

s32 CdDiscSelect_1c3090(s32 arg0) {
    u8 sp[0x50] __attribute__((aligned(16)));
    s32 i;

    if (!(arg0 != CdDiscGetCurrent_1c3080())) {
        return 0;
    }
    D_00481560 = arg0;
    for (i = 0; i < 2; i++) {
        *(u8 *)(sp + i * 0x20) = 0;
        *(s32 *)(sp + i * 4 + 0x40) = 0;
    }
    CdDataSetNamesInit_1c31a0(sp);
    CdDatArchivesOpenOnLayer_182dc0(D_00481560, sp);
    if (D_0048155C != 2) {
        D_0048155C = D_00481560;
    }
    OverlayLocateFiles_1c3300();
    return 1;
    return 0;
}
