/* rgp:protos */
#define RGP_SELF_EvCmdCharaTrailSetup_2592d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0047E964;
extern char D_004BE590[];

struct Obj0 {
    u8 m00[8];
    u8 m08[8];
    u8 m10[8];
    u8 m18[8];
    u8 m20[8];
};

/* Six five-byte descriptor slots live at sp+0x30; the nine-word argument
   pack at sp+0x60 is declared FIRST so it lands at the HIGHER address. */
s32 EvCmdCharaTrailSetup_2592d0(struct Obj0 *p0, s32 p1)
{
    s32 v60[9] __attribute__((aligned(16)));
    u8 v30[0x30] __attribute__((aligned(16)));
    f32 f;

    if (p1 < 4) {
        return 0;
    }
    v60[0] = -1;
    v60[1] = 0;
    v60[2] = 0;
    v60[3] = 0;
    v60[4] = 0;
    v60[5] = 0;
    v60[6] = 0;
    v60[7] = 0;
    v60[8] = 0;
    v60[0] = ScriptGetInt_26a2a0(p0->m00);
    VariantSetInt_302e80(&v30[0], D_0047E964);
    VariantSetString_302e00(&v30[5], D_004BE590);
    VariantSetInt_302e80(&v30[10], ScriptGetInt_26a2a0(p0->m08));
    VariantSetString_302e00(&v30[15], ((const char *)ScriptGetCodeAddr_26a200(p0->m10)));
    VariantSetFloat_302e40(&v30[20], TaggedGetFloat_26a280(p0->m18));
    if (p1 >= 5) {
        f = TaggedGetFloat_26a280(p0->m20);
    } else {
        f = 1.0f;
    }
    VariantSetFloat_302e40(&v30[25], f);
    ScriptCmdCharaTrailSetupThunk_22be30(v60, &v30[0], 6);
    return 1;
}
