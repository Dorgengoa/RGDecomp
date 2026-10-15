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

M2C_UNK SoundStreamHandleResolve_1bfa50(M2C_UNK *, void *, s32 *);
s32 RingBufGetReadSpan_1c1f30(s32, M2C_UNK *, s32 *);
s32 RingBufGetWriteSpan_1c2010(s32, s32 *, s32 *);
extern s32 SoundStreamLockAcquire_1bfb40(M2C_UNK *);
extern void *GetSoundStreamTable_1bf7c0(void);
extern void SoundStreamLockDtor_1bfab0(M2C_UNK *, s32);
extern s32 D_004814F0[] __attribute__((section(".sdata")));
extern u8 D_004A25F0[0x4A0];
void SoundStreamSlotGetBufInfo_1bd100(s32 arg0, void *arg1) {
    M2C_UNK sp4C;
    s32 sp48;
    s32 sp44;
    M2C_UNK sp40;
    s32 sp3C;
    s32 temp_16;
    s32 temp_16_2;
    s32 temp_2;
    void *temp_5;
    void *var_16;

    if (arg0 < 0 || arg0 >= 4) {
        var_16 = NULL;
    } else {
        var_16 = D_004A25F0 + arg0 * 0x128;
    }
    if ((var_16 == NULL) || (D_004814F0[arg0] == 0)) {
        var_16 = NULL;
    }
    if (var_16 == NULL) {
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        M2C_FIELD(arg1, s32 *, 8) = 0;
        M2C_FIELD(arg1, s32 *, 4) = 0;
        M2C_FIELD(arg1, s32 *, 0) = 0;
        return;
    }
    temp_5 = (s8 *)(GetSoundStreamTable_1bf7c0());
    sp3C = M2C_FIELD(var_16, s32 *, 4);
    SoundStreamHandleResolve_1bfa50(&sp4C, temp_5, &sp3C);
    temp_16 = SoundStreamLockAcquire_1bfb40(&sp4C) + 4;
    temp_16_2 = RingBufGetWriteSpan_1c2010(temp_16, &sp44, &sp48);
    temp_2 = RingBufGetReadSpan_1c1f30(temp_16, &sp40, &sp48);
    M2C_FIELD(arg1, s32 *, 0) = sp48;
    M2C_FIELD(arg1, s32 *, 4) = sp44;
    M2C_FIELD(arg1, s32 *, 8) = temp_16_2;
    M2C_FIELD(arg1, s32 *, 0xC) = temp_2;
    SoundStreamLockDtor_1bfab0(&sp4C, -1);
}
