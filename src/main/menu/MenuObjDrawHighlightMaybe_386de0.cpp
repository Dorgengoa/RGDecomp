#include "types.h"


extern "C" {
f32 Sinf_128fd0(f32 arg0);
void DrawListAddTexLoad_1418c0(s32 arg0, s32 arg1, f32 arg2);
s32 GetDrawCtx_15de80(void);
void Character2DrawWithLightBlendMaybe_1ae540(void *arg0, void *arg1, f32 arg2);
s32 BitArrayTest_384320(void *arg0, s32 arg1);
}
extern f32 D_0047D344;
extern f32 D_0047D7C4;
extern u8 D_0047FCD0;
extern u8 D_0047FCE0;
extern u8 D_0047FCF0;

class Obj {
public:
    u8 pad0[0x1B0];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void SetAlpha(f32);
    virtual void v5();
    virtual void v6();
    virtual void Reset();
    u8 pad1B4[0x4DC - 0x1B4];
    s32 unk4DC;
    u8 pad4E0[0x985 - 0x4E0];
    s8 unk985;
    u8 unk986[2];
    f32 unk988;
};



static inline f32 Abs(f32 x) {
    if (x < 0.0f) {
        return -x;
    }
    return x;
}

extern "C" void MenuObjDrawHighlightMaybe_386de0(Obj *arg0)
{
    f32 t;

    if (arg0->unk985 != 0 && BitArrayTest_384320(arg0->unk986, 7) == 0) {
        DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), arg0->unk4DC, 1.0f);
        arg0->SetAlpha(1.0f);
        if (BitArrayTest_384320(arg0->unk986, 2) != 0) {
            t = Sinf_128fd0(arg0->unk988);
            Character2DrawWithLightBlendMaybe_1ae540(arg0, &D_0047FCD0, 0.5f + 0.5f * t);
        } else if (BitArrayTest_384320(arg0->unk986, 1) != 0) {
            t = Abs(Sinf_128fd0(arg0->unk988));
            Character2DrawWithLightBlendMaybe_1ae540(arg0, &D_0047FCE0, 0.5f + D_0047D7C4 * t);
        } else if (BitArrayTest_384320(arg0->unk986, 3) != 0) {
            t = Abs(Sinf_128fd0(arg0->unk988));
            Character2DrawWithLightBlendMaybe_1ae540(arg0, &D_0047FCF0, 0.5f + D_0047D344 * t);
        } else {
            arg0->Reset();
        }
    }
}
