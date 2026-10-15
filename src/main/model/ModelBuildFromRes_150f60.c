#include "types.h"

extern s32 ModelBuildMeshes_152380(s32, s32, s32, s32);
extern s32 ModelBindFramesByName_150ad0(s32, s32, s32);

s32 ModelBuildFromRes_150f60(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4)
{
        s32 arg_h0;

    s32 r;

    if (a1 != 0) {
        arg_h0 = a1;
        r = ModelBuildMeshes_152380(arg_h0, a2, a3, a4);
    } else {
        r = 0;
    }
    if ((r == 0)) return r;
    if ((ModelBindFramesByName_150ad0(a0, a1, a2) != 0)) return r; else r = 0;
    return r;
}
