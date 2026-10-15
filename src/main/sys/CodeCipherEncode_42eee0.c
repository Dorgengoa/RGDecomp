#include "types.h"

/* PARK (3 rounds): 0xF8 vs retail 0x100 -- 8 bytes short even with crc1/crc2
   split into locals (was 12 short inline). Encode counterpart of
   CodeCipherDecode_42edb0 (decode, src/s15j): CRC-16 (Crc16Ccitt_42f000) plus a keystream
   (CodeCipherRandNext_42efe0, matched def in src/p23b) plus a byte swap. Reconstructed
   from the raw listing; arg2/arg3 typed to match Crc16Ccitt_42f000. */

#pragma divbyzerocheck on
#pragma opt_propagation off

extern s32 Crc16Ccitt_42f000(u8 *data, u32 len);
extern u32 CodeCipherRandNext_42efe0(void);
extern s32 D_0048031C;

void CodeCipherEncode_42eee0(u8 *arg0, s32 arg1, u8 *arg2, u32 arg3)
{
    u32 temp_3;
    s32 crc1;
    s32 crc2;
    u8 *var_4;
    s32 var_16;
    u8 var_17;
    u8 *p;
    u8 *buf_pos;
    u8 k;

    crc1 = Crc16Ccitt_42f000(arg0, arg1 - 2);
    crc2 = Crc16Ccitt_42f000(arg2, arg3);
    temp_3 = (crc1 ^ 0x62D3) ^ crc2;
    (arg1 + arg0)[-2] = (u8)temp_3;
    (arg1 + arg0)[-1] = (u8)(temp_3 >> 8);
    D_0048031C = temp_3 + 0x05888F27;
    for (var_16 = 0; var_16 < arg1 - 2; var_16++) {
        k = CodeCipherRandNext_42efe0() >> 0x18;
        arg0[var_16] = k ^ arg0[var_16];
    }
    D_0048031C = 0x014A76E0;
    var_4 = (u8 *)(arg1 + (s32)arg0);
    p = var_4 - 2;
    var_17 = *p;
    buf_pos = arg0 + CodeCipherRandNext_42efe0() % (arg1 - 2U);
    *p = *buf_pos;
    *buf_pos = var_17;
}
