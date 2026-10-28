/* main s27m: CLOSED as a C++ STRUCT ASSIGNMENT (memberwise: 16 s32, two {s32,s32}[4]
   arrays, 2 s32). The same struct copy in C is a 0x30-byte block-copy loop. */
#include "types.h"

typedef struct { s32 a; s32 b; } P1AFC10;
typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
    s32 w5;
    s32 w6;
    s32 w7;
    s32 w8;
    s32 w9;
    s32 wA;
    s32 wB;
    s32 wC;
    s32 wD;
    s32 wE;
    s32 wF;
    P1AFC10 p[4];
    P1AFC10 q[4];
    s32 x;
    s32 y;
} S1AFC10;

extern "C" u8 *ParamScriptReqCopy_1afc10(u8 *arg0, u8 *arg1) {
    *(S1AFC10 *)arg0 = *(S1AFC10 *)arg1;
    return arg0;
}
