/* rgp:protos */
#define RGP_SELF_SoundEnvPresetTableInitMaybe_207be0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s16 D_00481C90;
extern u8 D_004BCC90[0x100];
extern u8 D_004BCC9C[0x10];
extern u8 D_004BCC9E[0x10];
extern u8 D_004BCCA0[0x10];
extern u8 D_004BCCA2[0x10];
extern u8 D_004BCCA4[0x10];
extern u8 D_004BCCA6[0x10];
extern u8 D_004BCCA8[0x10];
extern u8 D_004BCCAA[0x10];
extern u8 D_004BCCAC[0x10];
extern u8 D_004BCCAE[0x10];
extern u8 D_004BCCB0[0x10];
extern u8 D_004BCCB2[0x10];
extern u8 D_004BCCB4[0x10];
extern u8 D_004BCCB6[0x10];
extern u8 D_004BCCB8[0x10];
extern u8 D_004BCCBA[0x10];
extern u8 D_004BCCBC[0x10];
extern u8 D_004BCCBE[0x10];
extern u8 D_004BCCC0[0x10];
extern u8 D_004BCCC2[0x10];
extern u8 D_004BCCC4[0x10];
extern u8 D_004BCCC6[0x10];
extern u8 D_004BCCC8[0x10];
extern u8 D_004BCCCA[0x10];
extern u8 D_004BCCCC[0x10];
extern u8 D_004BCCCE[0x10];
extern u8 D_004BCCD0[0x10];
extern u8 D_004BCD0E[0x10];
extern u8 D_004BCD10[0x10];
extern u8 D_004BCD12[0x10];

void SoundEnvPresetTableInitMaybe_207be0(void)
{
    s32 temp_3;
    s32 var_7;
    u8 *temp_5;

    SoundBankRelease_1bb6e0(7);
    SoundBankRelease_1bb6e0(5);
    D_00481C90 = -1;
    SoundSetEffectEnable_1bb6c0(0);
    var_7 = 0;
    do {
        temp_3 = var_7 * 6;
        var_7 += 1;
        temp_5 = D_004BCC90 + temp_3;
        *(s16 *)(temp_5 + 0x0) = 0x232D;
        *(s16 *)(temp_5 + 0x2) = 0x232D;
        *(s16 *)(temp_5 + 0x4) = 0x232D;
    } while (var_7 < 0x16);
    *(s16 *)D_004BCC9C = 0x2346;
    *(s16 *)D_004BCC9E = 0x2350;
    *(s16 *)D_004BCCA0 = 0x235A;
    *(s16 *)D_004BCCA2 = 0x2348;
    *(s16 *)D_004BCCA4 = 0x2352;
    *(s16 *)D_004BCCA6 = 0x235C;
    *(s16 *)D_004BCCA8 = 0x2347;
    *(s16 *)D_004BCCAA = 0x2351;
    *(s16 *)D_004BCCAC = 0x235B;
    *(s16 *)D_004BCCAE = 0x2349;
    *(s16 *)D_004BCCB0 = 0x2353;
    *(s16 *)D_004BCCB2 = 0x235D;
    *(s16 *)D_004BCCB4 = 0x234A;
    *(s16 *)D_004BCCB6 = 0x2354;
    *(s16 *)D_004BCCB8 = 0x235E;
    *(s16 *)D_004BCCC0 = 0x2361;
    *(s16 *)D_004BCCC2 = 0x2361;
    *(s16 *)D_004BCCC4 = 0x2361;
    *(s16 *)D_004BCCC6 = 0x2362;
    *(s16 *)D_004BCCC8 = 0x2362;
    *(s16 *)D_004BCCCA = 0x2362;
    *(s16 *)D_004BCCBA = 0x234B;
    *(s16 *)D_004BCCBC = 0x2355;
    *(s16 *)D_004BCCBE = 0x235F;
    *(s16 *)D_004BCCCC = 0x234C;
    *(s16 *)D_004BCCCE = 0x2356;
    *(s16 *)D_004BCCD0 = 0x2360;
    *(s16 *)D_004BCD0E = 0x234D;
    *(s16 *)D_004BCD10 = 0x2357;
    *(s16 *)D_004BCD12 = 0x2363;
}
