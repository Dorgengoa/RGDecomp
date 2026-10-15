#include "types.h"

s32 CdDiskReadyNewMaybe_12a508(s32);                                  /* extern */
s32 sceCdGetError_12aa98();                                 /* extern */
s32 sceCdReadDvdDualInfo_12acd0(s32 *, s32 *);                           /* extern */
s32 CdDatArchiveOpen_183110(u8 *, s8 *, s32);                     /* extern */
extern s8 D_00459770[0x10];
extern s8 D_00459778[0x10];
extern s32 D_004811B8;
extern s32 D_004811CC;
extern s32 D_004811DC;
extern s32 D_004811E4;
extern u8 D_00495FB0[0xC];
extern u8 D_00495FBC[0xC];

void CdDatArchivesInit_182e70(s8 *arg0) {
    s32 i;

    D_004811B8 = 0;
    CdDiskReadyNewMaybe_12a508(0);
    do {
        sceCdReadDvdDualInfo_12acd0(&D_004811DC, &D_004811E4);
    } while (sceCdGetError_12aa98() != 0);
    if (arg0 == 0) {
        CdDatArchiveOpen_183110(D_00495FB0, D_00459770, 0);
        CdDatArchiveOpen_183110(D_00495FBC, D_00459778, 0);
        D_004811CC = 2;
    } else {
        D_004811CC = 0;
        for (i = 0; i < 2; i++) {
            if (arg0[i * 32] != 0) {
                CdDatArchiveOpen_183110(D_00495FB0 + i * 12, arg0 + i * 32, *(s32 *)(arg0 + i * 4 + 0x40));
                D_004811CC += 1;
            }
        }
    }
}
