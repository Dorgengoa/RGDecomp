#include "types.h"

/* ONE symbol, TWO entries: a `j` TAIL CALL that loads the three per-row
   scales into $f12/$f13/$f14, then a 4x4 build.  The 0.0f and 1.0f columns
   are INTEGER stores (`sw $0` and `lui 0x3F80` + `sw`). */

void FUN_002e5630_e1(f32 *in, f32 *out, f32 sx, f32 sy, f32 sz);

void EventVolumeGetMatrix_2e5630(f32 *in, f32 *out)
{
    FUN_002e5630_e1(in, out, in[13], in[14], in[15]);
}

void FUN_002e5630_e1(f32 *in, f32 *out, f32 sx, f32 sy, f32 sz)
{
    out[0]  = sx * in[1];
    out[1]  = sx * in[2];
    out[2]  = sx * in[3];
    out[3]  = 0.0f;
    out[4]  = sy * in[4];
    out[5]  = sy * in[5];
    out[6]  = sy * in[6];
    out[7]  = 0.0f;
    out[8]  = sz * in[7];
    out[9]  = sz * in[8];
    out[10] = sz * in[9];
    out[11] = 0.0f;
    out[12] = in[10];
    out[13] = in[11];
    out[14] = in[12];
    out[15] = 1.0f;
}
