/* rgp:protos */
#define RGP_SELF_DrawWireCylinder_1cc600 1
#include "port/game_protos.h"
#line 1
/* PARKED at triage (0 round trips): ten unresolved "?"-typed stack locals
 * (sp80..sp110) passed by address to ProjectToScreen_15d340/MatMulPointXyz_1cb780/GsPktSetXYZVecI_13eeb0
 * with unknown sizes -- high risk of wrong stack layout without a raw-asm
 * trace. Deferred to preserve lane throughput. See asm/matchings/main/DrawWireCylinder_1cc600.s. */
/* s49m: MATCH */
#include "types.h"
#include "vec.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_004B3190[];
extern f32 D_004B31D0[];

void DrawWireCylinder_1cc600(void *g, void *m, s32 c)
{
    Vec4 p[4] __attribute__((aligned(16)));
    s32 s[6][4] __attribute__((aligned(16)));
    s32 i;
    f32 *px;
    f32 *pz;

    GsPktOpenPrim_13f730(g, 1);
    GsPktSetRGBAQVec_13edd0(g, c);
    for (i = 0; i < 12; i++) {
        MatMulPointXyz_1cb780(&p[0], m, D_004B3190[i], 1.0f, D_004B31D0[i]);
        MatMulPointXyz_1cb780(&p[1], m, D_004B3190[i + 1], 1.0f, D_004B31D0[i + 1]);
        MatMulPointXyz_1cb780(&p[2], m, D_004B3190[i], -1.0f, D_004B31D0[i]);
        MatMulPointXyz_1cb780(&p[3], m, D_004B3190[i + 1], -1.0f, D_004B31D0[i + 1]);
        if (ProjectToScreen_15d340(s[4], &p[0]) & ProjectToScreen_15d340(s[5], &p[1])) {
            GsPktSetXYZVecI_13eeb0(g, s[4]);
            GsPktSetXYZVecI_13eeb0(g, s[5]);
        }
        if (ProjectToScreen_15d340(s[2], &p[2]) & ProjectToScreen_15d340(s[3], &p[3])) {
            GsPktSetXYZVecI_13eeb0(g, s[2]);
            GsPktSetXYZVecI_13eeb0(g, s[3]);
        }
        if (ProjectToScreen_15d340(s[0], &p[0]) & ProjectToScreen_15d340(s[1], &p[2])) {
            GsPktSetXYZVecI_13eeb0(g, s[0]);
            GsPktSetXYZVecI_13eeb0(g, s[1]);
        }
    }
    GsPktClose_13f5b0(g);
}
