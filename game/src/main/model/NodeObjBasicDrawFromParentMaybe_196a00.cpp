/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
#undef NULL
#define NULL 0
extern "C" {
void ModelSetRootMatrix_1512e0(void *, int);

/* ---- mechanical m2c draft (lane u31) -------------------------------------
   Produced by build/u31/gendraft.py from m2c --valid-syntax.  This is a
   STARTING POINT, not a match: every M2C_* macro below marks something m2c
   could not type or could not translate.  Replace them as the unit is worked.
   -------------------------------------------------------------------- */
typedef rg_u128 u128;
typedef rg_s128 s128;
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

void ModelDetachRootFrames_151460(s8 *);                       /* extern */
void NodeCalcWorldMatrix_186130(s32, M2C_UNK *);                    /* extern */

class VC_0 {
public:
    u8 pad[0x68];
    VC_VPTR_MEMBER;
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x20); }
};
class VC_1 {
public:
    u8 pad[0x68];
    VC_VPTR_MEMBER;
    f32 f() { return VCM0(f32, 0xC); }
};
class VC_2 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x2C); }
};
s32 NodeObjBasicDrawFromParentMaybe_196a00(s8 *arg0) {
    s32 saved_reg_s1;
    s32 unin;  /* u31: m2c referenced but never declared */
    u8 sp40[0x40] __attribute__((aligned(16)));
    f32 var_f21;
    f32 temp_f20;
    s32 var_17;
    s8 *temp_2;
    s8 *temp_4;
    s8 *temp_4_2;

    var_17 = saved_reg_s1;
    if (M2C_FIELD(arg0, s16 *, 0x32) == 0) {
        return 0;
    }
    temp_2 = (s8 *)(M2C_FIELD(arg0, s8 **, 0x6C));
    if (temp_2 == NULL) {
        return 0;
    }
    if (temp_2 != NULL) {
        NodeCalcWorldMatrix_186130((s32)arg0, (M2C_UNK *)sp40);
        ModelSetRootMatrix_1512e0((void *)(M2C_FIELD(arg0, s8 **, 0x6C)), (s32) sp40);
    }
    if ((M2C_FIELD(arg0, s8 **, 0x6C) != NULL) && (((VC_0 *)(arg0))->f() != 0)) {
        temp_f20 = M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x6C), f32 *, 0x170);
        var_f21 = M2C_FIELD(arg0, f32 *, 0x64);
        if (M2C_FIELD(arg0, s32 *, 0x50) != 0) {
            var_f21 *= ((VC_1 *)(arg0))->f();
        }
        M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x6C), f32 *, 0x170) = var_f21;
        temp_4 = (s8 *)(M2C_FIELD(arg0, s8 **, 0x6C));
        var_17 = ((VC_2 *)(temp_4))->f();
        M2C_FIELD(M2C_FIELD(arg0, s8 **, 0x6C), f32 *, 0x170) = temp_f20;
    }
    temp_4_2 = (s8 *)(M2C_FIELD(arg0, s8 **, 0x6C));
    if (temp_4_2 != NULL) {
        M2C_FIELD(temp_4_2, s32 *, 0x100) = 0;
        ModelDetachRootFrames_151460(temp_4_2);
    }
    return var_17;
}

}
