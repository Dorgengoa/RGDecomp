/* rgp:protos */
#define RGP_SELF_SaveDirRenameJpToUs_373160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad0[0x80]; } Buf30;
typedef struct { u8 pad0[0x88]; } BufB0;
typedef struct { u8 pad0[0x4]; } Buf138;
#define Buf00373160 void

typedef struct {
    u8 pad0[0x4EC];
    s16 unk4EC;
} Obj00373160;

void sceMcSync_12d098(s32, Buf00373160 *, s32 *);       /* extern */
void sceMcChdir_12d588(s16, s32, Buf00373160 *, s32);    /* extern */
void sceMcRename_12db48(s16, s32, Buf00373160 *, Buf00373160 *); /* extern */
/*rgp*/                                /* extern */
/*rgp*/              /* extern */
/*rgp*/              /* extern */
extern u8 D_004638C8[0x400];
extern u8 D_004638D0[0x400];

s32 SaveDirRenameJpToUs_373160(Obj00373160 *arg0) {
    s32 sp13C;
    Buf138 sp138 __attribute__((aligned(16)));
    BufB0 spB0 __attribute__((aligned(16)));
    Buf30 sp30 __attribute__((aligned(16)));
    s32 var_17;
    s16 temp_16;

    temp_16 = arg0->unk4EC;
    sp13C = 0;
    sceMcSync_12d098(0, &sp138, &sp13C);
    var_17 = 0;
    do {
        SaveDirNameFormatUs_376330(var_17, &spB0);
        SaveDirNameFormatJp_3762e0(var_17, &sp30);
        sceMcChdir_12d588(temp_16, 1, (void *)D_004638C8, 0);
        sceMcSync_12d098(0, &sp138, &sp13C);
        if (sp13C == 0) {
            sceMcRename_12db48(temp_16, 1, &sp30, &spB0);
            sceMcSync_12d098(0, &sp138, &sp13C);
            ReturnZero_207fe0();
            sceMcChdir_12d588(temp_16, 1, &spB0, 0);
            sceMcSync_12d098(0, &sp138, &sp13C);
            if (sp13C == 0) {
                sceMcRename_12db48(temp_16, 1, &sp30, &spB0);
                sceMcSync_12d098(0, &sp138, &sp13C);
                ReturnZero_207fe0();
                sceMcChdir_12d588(temp_16, 1, (void *)D_004638D0, 0);
                sceMcSync_12d098(0, &sp138, &sp13C);
            }
        }
        var_17 += 1;
    } while (var_17 < 0x32);
    return 1;
}
