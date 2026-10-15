#include "types.h"

extern void CdDatArchivesOpenOnLayer_182dc0(s32 arg0, void *arg1);
extern s32 CdDiscGetCurrent_1c3080(void);
extern void CdDataSetNamesInit_1c31a0(void *arg0);
extern void OverlayLocateFiles_1c3300(void);
extern s32 D_0048155C;
extern s32 D_00481560;

s32 CdDiscSelect_1c3090(s32 arg0) {
    u8 sp[0x50];
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
