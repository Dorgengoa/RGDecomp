#include "types.h"

typedef struct Req {
    s32 h0;
    s32 h1;
    s32 pad[2];
    f32 col[4];
    f32 scale;
} Req;

f32 Sinf_128fd0(f32);
f32 fabsf(f32);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
s32 NameTableFindByName_159fb0(s32, void *, s32);
s32 GetDrawCtxNameTable_15de40(void);
s32 GetDrawCtx_15de80(void);
void BloomExtractBlurMaybe_179360(Req *);
void FrameAlphaClear_179b20(void);
void VecScalePoint_1cbc60(f32 *, f32 *, f32);
void TreasureBoxPoolDraw_338c00(s32 *, s32, f32, s32);
extern u8 D_004625E8[0x10];
extern u8 D_004625F8[0x10];
extern f32 D_0047D858;
extern f32 D_0047D870;
extern s32 D_00482C40;
extern s32 D_00482C4C;

void TaskDrawTBox_3387a0(void)
{
    Req r;
    f32 f;
    s32 h;

    if (D_00482C4C >= 0) {
        f = fabsf(Sinf_128fd0(D_0047D858 * (((f32)D_00482C4C / 90.0f) - 0.5f)));
        if (f < 0.0f) {
            f = 0.0f;
        }
        FrameAlphaClear_179b20();
        TreasureBoxPoolDraw_338c00(&D_00482C40, 1, D_0047D870, 0);
        h = GetDrawCtxNameTable_15de40();
        r.col[3] = 1.0f;
        r.col[2] = 1.0f;
        r.col[1] = 1.0f;
        r.col[0] = 1.0f;
        r.scale = 1.0f;
        r.h1 = 0;
        r.h0 = 0;
        r.h0 = NameTableFindByName_159fb0(h, D_004625E8, 0x325);
        r.h1 = NameTableFindByName_159fb0(h, D_004625F8, 0x325);
        r.col[0] = 1.0f;
        r.col[1] = 1.0f;
        r.col[2] = 1.0f;
        r.col[3] = 1.0f;
        VecScalePoint_1cbc60(r.col, r.col, f);
        r.scale = f;
        DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), 0x325, 1.0f);
        BloomExtractBlurMaybe_179360(&r);
    }
    TreasureBoxPoolDraw_338c00(&D_00482C40, 1, 1.0f, 1);
}
