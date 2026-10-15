#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
#pragma opt_propagation off

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

M2C_UNK GsPktSetOriginMode_13e2f0(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktSetTexFilter_13e3d0(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktSetUseUV_13e3e0(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktSetTextured_13e400(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktSetZWriteMask_13e430(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktEnableZTest_13e460(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktEnableAlphaTest_13e4d0(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktSetAlphaBlend_13e500(s32, M2C_UNK);                 /* extern */
M2C_UNK GsPktSetTexture_13ec00(s32, M2C_UNK *);               /* extern */
M2C_UNK GsPktSetUVFixed_13ed90(s32, s32, s32);                /* extern */
M2C_UNK GsPktSetRGBAQ_13ee40(s32, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK GsPktSetXYZPixel_13f110(s32, s32, s32, M2C_UNK);       /* extern */
M2C_UNK GsPktClose_13f5b0(s32);                          /* extern */
M2C_UNK GsPktOpenPrim_13f730(s32, M2C_UNK);                 /* extern */
M2C_UNK DrawListEndPrim_141a20(s32);                          /* extern */
s32 DrawListBeginPrim_141b00(s32);                              /* extern */
M2C_UNK DrawEnvGetFrameTexDesc_144cc0(s32, M2C_UNK *);               /* extern */
s32 DrawEnvGetHeight_1451d0(s32);                              /* extern */
s32 DrawEnvGetWidth_1451e0(s32);                              /* extern */
M2C_UNK NameTableNodeCtor_15ae50(M2C_UNK *);                    /* extern */
s32 GetDrawCtx_15de80();                                 /* extern */
s32 LetterboxIsEnabled_277fe0();                                 /* extern */

void LetterboxDraw_277ff0(s8 *arg0) {
    s32 temp_20;
    s32 temp_16;
    s32 temp_17;
    s32 temp_19;
    M2C_UNK sp70[25];
    s32 temp_2;
    s32 c;

    if ((LetterboxIsEnabled_277fe0() != 0) && !(M2C_FIELD(arg0, f32 *, 0xC) <= 0.0f)) {
        temp_20 = GetDrawCtx_15de80();
        temp_19 = (s32) ((f32) M2C_FIELD(arg0, s32 *, 0x18) * M2C_FIELD(arg0, f32 *, 0xC));
        NameTableNodeCtor_15ae50(sp70);
        if (temp_19 != 0) {
            DrawEnvGetFrameTexDesc_144cc0(temp_20, sp70);
        }
        temp_17 = DrawEnvGetWidth_1451e0(temp_20);
        temp_16 = DrawEnvGetHeight_1451d0(temp_20);
        temp_2 = DrawListBeginPrim_141b00(temp_20);
        GsPktSetOriginMode_13e2f0(temp_2, 0);
        GsPktSetTextured_13e400(temp_2, 0);
        GsPktSetZWriteMask_13e430(temp_2, 1);
        GsPktSetAlphaBlend_13e500(temp_2, 0);
        GsPktEnableAlphaTest_13e4d0(temp_2, 0);
        GsPktEnableZTest_13e460(temp_2, 0);
        if (temp_19 != 0) {
            GsPktSetTexFilter_13e3d0(temp_2, 0);
            GsPktSetTextured_13e400(temp_2, 1);
            GsPktSetUseUV_13e3e0(temp_2, 1);
            GsPktOpenPrim_13f730(temp_2, 6);
            GsPktSetTexture_13ec00(temp_2, sp70);
            c = 0x80;
            GsPktSetRGBAQ_13ee40(temp_2, c, c, c, c);
            c = 8;
            GsPktSetUVFixed_13ed90(temp_2, c, c);
            GsPktSetXYZPixel_13f110(temp_2, 0, temp_19, 0);
            GsPktSetUVFixed_13ed90(temp_2, ((temp_17 - 1) * 0x10) + 8, ((temp_16 - 1) * 0x10) + 8);
            GsPktSetXYZPixel_13f110(temp_2, temp_17 - 1, temp_16 - 1 + temp_19, 0);
            GsPktClose_13f5b0(temp_2);
        }
        GsPktSetTextured_13e400(temp_2, 0);
        GsPktSetTexFilter_13e3d0(temp_2, 0);
        GsPktOpenPrim_13f730(temp_2, 6);
        GsPktSetRGBAQ_13ee40(temp_2, 0, 0, 0, 0x80);
        GsPktSetXYZPixel_13f110(temp_2, 0, 0, 0);
        GsPktSetXYZPixel_13f110(temp_2, temp_17 - 1, temp_19 + (s32) (M2C_FIELD(arg0, f32 *, 0xC) * M2C_FIELD(arg0, f32 *, 0)), 0);
        GsPktSetXYZPixel_13f110(temp_2, 0, temp_19 + (temp_16 - (s32) (M2C_FIELD(arg0, f32 *, 0xC) * M2C_FIELD(arg0, f32 *, 4))), 0);
        GsPktSetXYZPixel_13f110(temp_2, temp_17 - 1, temp_16 - 1, 0);
        GsPktClose_13f5b0(temp_2);
        DrawListEndPrim_141a20(temp_20);
    }
}
