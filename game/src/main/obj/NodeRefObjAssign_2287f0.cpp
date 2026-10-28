/* main s27m: CLOSED as the IMPLICIT operator= of a DERIVED struct: the base class has an
   INLINE operator= that calls JudgeObjectAssignBase_2289d0 (the base copy), the tail is memberwise;
   the three V4s sit at 0x150 via a MEMBER aligned(16) -- an aligned TYPE copies
   them as lq/sq instead of four lwc1 + four swc1. */
#include "types.h"

typedef struct { s16 a; s16 b; } P16_2287F0;
typedef struct { s8 a; s8 b; } P8_2287F0;
typedef struct { s32 a; s32 b; } P32_2287F0;
typedef struct { f32 x; f32 y; f32 z; f32 w; } V4_2287F0;

extern "C" void *JudgeObjectAssignBase_2289d0(void *, void *);

struct B_2287F0 {
    u8 pad[0xB4];
    B_2287F0 &operator=(const B_2287F0 &o) { JudgeObjectAssignBase_2289d0(this, (void *)&o); return *this; }
};

struct D_2287F0 : B_2287F0 {
    s16 h0;
    s16 h1;
    s16 h2;
    s16 h3;
    s16 h4;
    u16 h5;
    s16 h6;
    f32 f0;
    f32 f1;
    f32 f2;
    P16_2287F0 p[20];
    P8_2287F0 q[20];
    V4_2287F0 v0 __attribute__((aligned(16)));
    V4_2287F0 v1;
    V4_2287F0 v2;
    P32_2287F0 r[0xA0];
    s16 s;
    s16 t;
    P32_2287F0 u[0x18];
    P32_2287F0 w[0x28];
    s16 x;
    s16 y;
};


extern "C" void *NodeRefObjAssign_2287f0(void *arg0, void *arg1)
{
    *(D_2287F0 *)arg0 = *(D_2287F0 *)arg1;
    return arg0;
}
