/* rg-override: replaces game/src/main/file/CdDatArchivesInit_182e70.c sha256 59a25f8eb1a9bb673c019475c1e3211ef03d75071d438744abaf69decd22f5a2
 * why: native files (docs/NATIVE-FS.md, PLAN.md D9): no disc to wait for or query.  The
 *      dual-layer flag stays 1, as on the retail disc, so the game keeps choosing the
 *      disc-row file names (DATA0_* / DATA1_*) itself; layer1_start (stored, never used)
 *      is 0.  The archive opens are unchanged. */
/* rgp:protos */
#define RGP_SELF_CdDatArchivesInit_182e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
    /* rg-override: was CdDiskReadyNewMaybe_12a508(0) and
     * do sceCdReadDvdDualInfo_12acd0(&D_004811DC, &D_004811E4) while (sceCdGetError()) */
    D_004811DC = 1;
    D_004811E4 = 0;
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
