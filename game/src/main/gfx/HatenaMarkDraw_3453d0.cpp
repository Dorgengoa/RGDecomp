/* rgp:protos */
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK 1/3: length-wrong (93w vs retail 91w, ours LONGER). Fixed a negative-size struct-padding bug (Obj4 field order was backwards). */
#include "types.h"
#pragma opt_propagation off
#undef NULL
#define NULL 0
extern "C" {

typedef struct VT1B0 {
    u8 pad[0x24];
    void (*unk24)(void *);
} VT1B0;

typedef struct Obj4 {
    u8 pad28[0x28];
    s32 unk28;
    u8 pad90[0x90 - 0x2C];
    f32 unk90;
    f32 unk94;
    f32 unk98;
} Obj4;

void VecAdd_13be20(f32 *, void *, void *);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
void FrameSetScale_14a2c0(Obj4 *, void *);
void FrameSetRot_14a390(void *, void *);
void FrameSetDirty_14a5e0(Obj4 *);
void ModelSetRot_151080(void *, void *);
s32 GetDrawCtx_15de80(void);

class VC_0 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    void f() { VCM0(void, 0x24); }
};
s32 HatenaMarkDraw_3453d0(u8 *arg0) {
            void * arg_h1;

    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(f32[3])) + (0x10)];
    u8 *temp_3;
    Obj4 *temp_4;
    Obj4 *temp_4_2;
    VT1B0 **temp_4_3;

    if (*(u8 *)(arg0 + 0xC) == 2) {
        return 2;
    }
    if (*(u8 *)(arg0 + 0xA0) != 0) {
        if (*(u8 **)(arg0 + 0) == NULL) {
            return 1;
        }
        DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), 0x282, 1.0f);
        if ((*(u8 *)(arg0 + 0xC) == 1) && ((*(u8 *)(arg0 + 0xA1) & 1) != 1)) {
            VecAdd_13be20((*(f32 (*)[3])(rgp_blk1 + 0x0)), arg0 + 0x20, arg0 + 0x30);
        } else {
            VecAdd_13be20((*(f32 (*)[3])(rgp_blk1 + 0x0)), arg0 + 0x10, arg0 + 0x30);
            (*(f32 (*)[3])(rgp_blk1 + 0x0))[1] += 5.0f;
        }
        ModelSetRot_151080(*(u8 **)(arg0 + 0), arg0 + 0x60);
        FrameSetScale_14a2c0(*(Obj4 **)(arg0 + 4), arg0 + 0x70);
        temp_4 = *(Obj4 **)(arg0 + 4);
        temp_4->unk90 = *(f32 *)(arg0 + 0x10);
        temp_4->unk94 = *(f32 *)(arg0 + 0x14);
        temp_4->unk98 = *(f32 *)(arg0 + 0x18);
        FrameSetDirty_14a5e0(temp_4);
        temp_3 = *(u8 **)(arg0 + 8);
        if (*(s8 *)(temp_3 + 0x28) != 0) {
            *(s32 *)(temp_3 + 4) = 0;
        }
        FrameSetScale_14a2c0(*(Obj4 **)(arg0 + 8), arg0 + 0x80);
        FrameSetRot_14a390(*(u8 **)(arg0 + 8), arg0 + 0x60);
        temp_4_2 = *(Obj4 **)(arg0 + 8);
        temp_4_2->unk90 = (*(f32 (*)[3])(rgp_blk1 + 0x0))[0];
        temp_4_2->unk94 = (*(f32 (*)[3])(rgp_blk1 + 0x0))[1];
        temp_4_2->unk98 = (*(f32 (*)[3])(rgp_blk1 + 0x0))[2];
        FrameSetDirty_14a5e0(temp_4_2);
        temp_4_3 = *(VT1B0 ***)(arg0 + 0);
        ((VC_0 *)(temp_4_3))->f();
        return 0;
    }
    return 0;
}

}
