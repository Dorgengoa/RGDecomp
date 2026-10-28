/* main s27m: CLOSED as a C++ struct assignment ([[cpp-memberwise-struct-copy]]). */
#include "types.h"

typedef struct { s32 a; s32 b; } P_193F60;
typedef struct {
    P_193F60 p[6];
    s16 h0;
    s16 h1;
    s32 w0;
    s32 w1;
    s32 arr[9];
    f32 f0;
    f32 f1;
} S_193F60;

extern "C" void *NodeAssign_193f60(void *arg0, void *arg1) {
    *(S_193F60 *)arg0 = *(S_193F60 *)arg1;
    return arg0;
}
