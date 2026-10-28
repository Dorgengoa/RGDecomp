/* rgp:protos */
#define RGP_SELF_MapSceneCfgLightSetEnd_192b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* `bc1fl` past the body with `sw $0,%gp_rel(D_00481304)` in the delay slot
   is the branch-likely duplication of the JOIN block's first store -- the
   global is nulled on BOTH paths, so the assignment sits after the `if`. */

/*rgp*/
/*rgp*/

typedef struct Ctx {
    u8 pad000[0x70];
    f32 m70[4];
    u8 pad080[0x100];
    f32 m180[4];
    f32 m190;
    f32 m194;
    f32 m198;
    f32 m19C;
} Ctx;

extern Ctx *D_00481304;
extern f32 D_0047DB7C;

s32 MapSceneCfgLightSetEnd_192b40(void)
{
    f32 tmp[4] __attribute__((aligned(16)));

    if (D_00481304->m190 < 0.0f) {
        VecScale_13be00(tmp, D_00481304->m70, D_0047DB7C);
        VecAdd_13be20(&D_00481304->m190, D_00481304->m180, tmp);
        D_00481304->m19C = 128.0f;
    }
    D_00481304 = 0;
    return 1;
}
