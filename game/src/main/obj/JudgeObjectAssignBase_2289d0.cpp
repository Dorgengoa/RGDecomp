/* main s27m: CLOSED as a C++ STRUCT ASSIGNMENT -- a nested {f32 x4} (loaded as a batch),
   s32[27] (the loop), then scalars. */
#include "types.h"

typedef struct { f32 x; f32 y; f32 z; f32 w; } V2289D0;
typedef struct {
    V2289D0 v;
    s32 arr[27];
    s32 a;
    s32 b;
    s16 h0;
    s16 h1;
    s16 h2;
    s16 h3;
    s16 h4;
    s16 h5;
    s32 c;
    f32 f0;
    f32 f1;
    f32 f2;
    s32 d;
    s16 h6;
    s16 h7;
} S2289D0;

extern "C" void *JudgeObjectAssignBase_2289d0(void *arg0, void *arg1)
{
    *(S2289D0 *)arg0 = *(S2289D0 *)arg1;
    return arg0;
}
