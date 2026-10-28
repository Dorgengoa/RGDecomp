/* rgp:protos */
#define RGP_SELF_MenuWeaponCombineIsFeedableMaybe_3627a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"


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


s32 MenuWeaponCombineIsFeedableMaybe_3627a0(s32 unused0, u8 *arg1) {
    s16 var_2;
    u8 *var_3;

    var_3 = (u8 *)(M2C_FIELD(arg1, u8 **, 0x10));
    var_2 = (s16)(M2C_FIELD(var_3, s16 *, 6));
    var_3 = (u8 *)((u8 *) M2C_FIELD(var_3, s16 *, 0));
    if (var_2 < 4) {
        var_2 = (s16)(0x4110);
        if (var_3 != (u8 *)0x4110) {
            var_2 = (s16)(0x3F03);
            if (var_3 != (u8 *)0x3F03) {
                var_2 = (s16)(0x3F0B);
                if (var_3 != (u8 *)0x3F0B) {
                    var_2 = (s16)(0x3F07);
                    if (var_3 != (u8 *)0x3F07) {
                        var_2 = (s16)(1);
                        goto gpt_return1;
                    }
                    goto block_7;
                }
            }
        }
    }
block_7:
    var_2 = (s16)(0);
    goto gpt_return0;

gpt_return0: return 0;
gpt_return1: return 1;
}
