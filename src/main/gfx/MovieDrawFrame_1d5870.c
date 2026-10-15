#include "types.h"

/* ---- mechanical m2c draft (lane u31) -------------------------------------
   Produced by build/u31/gendraft.py from m2c --valid-syntax.  This is a
   STARTING POINT, not a match: every M2C_* macro below marks something m2c
   could not type or could not translate.  Replace them as the unit is worked.
   -------------------------------------------------------------------- */
typedef unsigned __int128 u128;
typedef __int128 s128;
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK(x) (0)
#define M2C_SYNC() (0)
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

M2C_UNK GsPktSetTexFilter_13e3d0(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktSetTextured_13e400(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktSetZWriteMask_13e430(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktEnableZTest_13e460(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktSetAlphaTestFunc_13e4c0(s32, M2C_UNK, M2C_UNK);        /* extern */
M2C_UNK GsPktEnableAlphaTest_13e4d0(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktSetBlendMode_13e4f0(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktSetAlphaBlend_13e500(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktSetTexture_13ec00(s32, s16 *);                   /* extern */
M2C_UNK GsPktSetUVFixed_13ed90(s32, s32, s32);                /* extern */
M2C_UNK GsPktSetRGBAQ_13ee40(s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK GsPktSetXYZPixel_13f110(s32, s32, s32, M2C_UNK);       /* extern */
M2C_UNK GsPktClose_13f5b0(s32);                          /* extern */
M2C_UNK GsPktOpenPrim_13f730(s32, M2C_UNK);                 /* extern */
void DrawListAddTexLoad_1418c0(s32, s16, f32);            /* extern */
M2C_UNK DrawListEndPrim_141a20(s32);                          /* extern */
s32 DrawListBeginPrim_141b00(s32);                              /* extern */
s32 GetDrawCtx_15de80();                                 /* extern */
M2C_UNK ScreenFadeBlockDraw_177540(s8 *);                       /* extern */
extern s16 *D_004817A8;
extern u8 D_004B3210[0x400];
extern u8 D_004B3214[0x400];

typedef struct { u8 pad[0x17920]; u8 m17920[0x50]; s32 m17970; s32 m17974; } O001d5870;

void MovieDrawFrame_1d5870(O001d5870 *arg0) {
        s16 arg_h0;

    s32 temp_2_4;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_21;
    s32 temp_2_3;
    s32 var_17;
    s32 temp_17;
    s32 temp_16;
    s32 var_16;
    s32 var_22;

    if (D_004817A8 != NULL) {
        temp_2 = GetDrawCtx_15de80();
        DrawListAddTexLoad_1418c0(temp_2, *D_004817A8, 1.0f);
        temp_2_2 = DrawListBeginPrim_141b00(temp_2);
        GsPktSetAlphaBlend_13e500(temp_2_2, 1);
        GsPktSetBlendMode_13e4f0(temp_2_2, 1);
        GsPktEnableAlphaTest_13e4d0(temp_2_2, 1);
        GsPktSetAlphaTestFunc_13e4c0(temp_2_2, 1, 0);
        GsPktEnableZTest_13e460(temp_2_2, 0);
        GsPktSetZWriteMask_13e430(temp_2_2, 1);
        GsPktSetTexFilter_13e3d0(temp_2_2, 0);
        GsPktSetAlphaBlend_13e500(temp_2_2, 0);
        GsPktSetTextured_13e400(temp_2_2, 0);
        GsPktOpenPrim_13f730(temp_2_2, 6);
        GsPktSetRGBAQ_13ee40(temp_2_2, 0, 0, 0, 0x80);
        var_17 = 0;
        do {
            var_16 = 0;
loop_3:
            GsPktSetXYZPixel_13f110(temp_2_2, var_17, var_16, 0);
            GsPktSetXYZPixel_13f110(temp_2_2, var_17 + 0x20, var_16 + 0x20, 0);
            var_16 += 0x20;
            if (var_16 < 0x1C0) {
                goto loop_3;
            }
            var_17 += 0x20;
        } while (var_17 < 0x200);
        GsPktClose_13f5b0(temp_2_2);
        temp_17 = (*(s32 *)D_004B3210);
        temp_16 = (*(s32 *)D_004B3214);
        var_21 = (0x200 - temp_17) / 2;
        var_22 = (0x1C0 - temp_16) / 2;
        GsPktSetTexFilter_13e3d0(temp_2_2, 0);
        GsPktSetTextured_13e400(temp_2_2, 1);
        GsPktOpenPrim_13f730(temp_2_2, 6);
        GsPktSetTexture_13ec00(temp_2_2, D_004817A8);
        GsPktSetRGBAQ_13ee40(temp_2_2, 0x80, 0x80, 0x80, 0x80);
        GsPktSetUVFixed_13ed90(temp_2_2, 8, 8);
        GsPktSetXYZPixel_13f110(temp_2_2, var_21 + arg0->m17970, var_22 + arg0->m17974, 0);
        GsPktSetUVFixed_13ed90(temp_2_2, ((temp_17 - 1) * 0x10) + 8, ((temp_16 - 1) * 0x10) + 8);
        GsPktSetXYZPixel_13f110(temp_2_2, (arg0->m17970 + (var_21 + temp_17)) - 1, (arg0->m17974 + (var_22 + temp_16)) - 1, 0);
        GsPktClose_13f5b0(temp_2_2);
        DrawListEndPrim_141a20(temp_2);
        ScreenFadeBlockDraw_177540((s8 *)arg0->m17920);
    }
}
