/* rgp:protos */
#line 1
/* main s27m: CLOSED -- C++ virtual (vptr 0xC0, slot 16) + a memberwise copy of a
   {f32 x10 SEPARATE members, s32} struct ([[cpp-memberwise-struct-copy]]); f32[10] loops. */
#include "types.h"
#include "vec.h"

typedef struct {
    f32 f[10];
    s32 w;
} S_176C90;

typedef struct {
    f32 f0; f32 f1; f32 f2; f32 f3; f32 f4; f32 f5; f32 f6; f32 f7; f32 f8; f32 f9;
    s32 w;
} T_176C90;

class C_176C90 {
public:
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    T_176C90 * v16(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(T_176C90 *, (void *, int, int, int), 0x48, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" void CameraCopyParams_176c90(C_176C90 *arg0, C_176C90 *arg1, int rgp_a2, int rgp_a3) {
    T_176C90 *temp_16;

    temp_16 = arg0->v16((int)(long)(arg1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    *arg1->v16() = *temp_16;
    *(u128 *)((u8 *)arg1 + 0x120) = *(u128 *)((u8 *)arg0 + 0x120);
}
