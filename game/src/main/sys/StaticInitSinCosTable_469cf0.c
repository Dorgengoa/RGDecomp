/* rgp:protos */
#define RGP_SELF_StaticInitSinCosTable_469cf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004816A0;
extern s32 D_004816AC;
extern s32 D_004816B0;
extern s32 D_004816BC;
extern f32 D_0047D1F4;
extern f32 D_0047D1F8;
extern f32 D_0047D1FC;
extern f32 D_0047D200;
extern f32 D_0047D204;
extern f32 D_0047D208;
extern f32 D_0047D20C;
extern f32 D_0047D210;
extern f32 D_0047D214;
extern f32 D_0047D218;
extern f32 D_0047D21C;
extern f32 D_0047D220;
extern f32 D_0047D224;
extern f32 D_0047D228;
extern f32 D_0047D22C;
extern f32 D_004B3190[29];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void StaticInitSinCosTable_469cf0(void)
{
    IosBaseInitCtor_102bd0(&D_004816AC);
    RegisterGlobalObject_100dc0(&D_004816AC, (void *)IosBaseInitDtor_102ee0, &D_004816A0);
    WIosBaseInitCtor_103110(&D_004816BC);
    RegisterGlobalObject_100dc0(&D_004816BC, (void *)WIosBaseInitDtor_103420, &D_004816B0);
    D_004B3190[0] = Sinf_128fd0(0.0f);
    D_004B3190[1] = Sinf_128fd0(D_0047D200);
    D_004B3190[2] = Sinf_128fd0(D_0047D204);
    D_004B3190[3] = Sinf_128fd0(D_0047D1F4);
    D_004B3190[4] = Sinf_128fd0(D_0047D208);
    D_004B3190[5] = Sinf_128fd0(D_0047D20C);
    D_004B3190[6] = Sinf_128fd0(D_0047D1FC);
    D_004B3190[7] = Sinf_128fd0(D_0047D210);
    D_004B3190[8] = Sinf_128fd0(D_0047D214);
    D_004B3190[9] = Sinf_128fd0(D_0047D1F8);
    D_004B3190[10] = Sinf_128fd0(D_0047D218);
    D_004B3190[11] = Sinf_128fd0(D_0047D21C);
    D_004B3190[12] = Sinf_128fd0(0.0f);
    D_004B3190[16] = Cosf_128d30(0.0f);
    D_004B3190[17] = Cosf_128d30(D_0047D220);
    D_004B3190[18] = Cosf_128d30(D_0047D224);
    D_004B3190[19] = Cosf_128d30(D_0047D1F4);
    D_004B3190[20] = Cosf_128d30(D_0047D208);
    D_004B3190[21] = Cosf_128d30(D_0047D20C);
    D_004B3190[22] = Cosf_128d30(D_0047D1FC);
    D_004B3190[23] = Cosf_128d30(D_0047D210);
    D_004B3190[24] = Cosf_128d30(D_0047D214);
    D_004B3190[25] = Cosf_128d30(D_0047D1F8);
    D_004B3190[26] = Cosf_128d30(D_0047D228);
    D_004B3190[27] = Cosf_128d30(D_0047D22C);
    D_004B3190[28] = Cosf_128d30(0.0f);
}
