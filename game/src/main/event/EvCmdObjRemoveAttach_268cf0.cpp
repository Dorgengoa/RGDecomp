/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {
s32 ScriptGetInt_26a2a0(void *);
s32 ObjRecGetLiveObject_1c4a90(void *, int);

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

extern s8 *D_00481F78;

class VC_0 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    M2C_UNK f(s32 x0) { return VCM(M2C_UNK, (void *, s32), 0x54, x0); }
};
class VC_1 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    M2C_UNK f(s32 x0) { return VCM(M2C_UNK, (void *, s32), 0x54, x0); }
};
s32 EvCmdObjRemoveAttach_268cf0(s64 *arg0, s32 arg1) {
    s8 *temp_2;
    s32 var_16;
    s32 var_17;
    s32 temp_16;

    var_17 = -1;
    temp_16 = ScriptGetInt_26a2a0((void *)((s32)arg0++));
    if (arg1 >= 2) {
        var_17 = ScriptGetInt_26a2a0((void *)((s32)arg0));
    }
    temp_2 = (s8 *)(ObjRecGetLiveObject_1c4a90((void *)(D_00481F78), temp_16));
    if (temp_2 == NULL) {
        return 0;
    }
    if (var_17 > 0) {
        ((VC_1 *)(temp_2))->f(var_17);
    } else {
        var_16 = 1;
        do {
            ((VC_0 *)(temp_2))->f(var_17);
            var_16 += 1;
        } while (var_16 < 8);
    }
    return 1;
}

}
