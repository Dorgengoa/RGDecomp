#include "types.h"
#pragma divbyzerocheck on

extern u32 CodeCipherRandNext_42efe0(void);
extern s32 Crc16Ccitt_42f000(s32, s32);
extern s32 D_0048031C;

s32 CodeCipherDecode_42edb0(u8 *buf, s32 len, s32 a2, s32 a3) {
    u8 *p;
    u8 *q;
    u8 c;
    s32 key;
    s32 i;

    D_0048031C = 0x014A76E0;
    p = (u8 *)(len + (s32)buf) - 2;
    c = *p;
    q = buf + CodeCipherRandNext_42efe0() % (u32)(len - 2);
    *p = *q;
    *q = c;
    key = *p;
    key |= buf[len - 1] << 8;
    D_0048031C = key + 0x05888F27;
    for (i = 0; i < len - 2; i++) {
        { u8 x = CodeCipherRandNext_42efe0() >> 24; buf[i] = x ^ buf[i]; }
    }
    key ^= Crc16Ccitt_42f000(a2, a3);
    return (key ^ 0x62D3) == Crc16Ccitt_42f000((s32)buf, len - 2);
}
