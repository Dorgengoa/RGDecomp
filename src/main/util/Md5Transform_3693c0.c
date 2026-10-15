#include "types.h"

typedef struct {
    u64 bits[2];
    u64 buf[4];
} MD5Ctx;

#define F1(x, y, z) ((z) ^ ((x) & ((y) ^ (z))))
#define F2(x, y, z) F1(z, x, y)
#define F3(x, y, z) ((x) ^ (y) ^ (z))
#define F4(x, y, z) ((y) ^ ((x) | ~(z)))

#define ROTATE_LEFT(v, n) (((v) << (n)) | (((v) & 0xFFFFFFFFU) >> (32 - (n))))

#define STEP(f, w, xx, yy, zz, data, s, t) w += f(xx, yy, zz) + (data) + (t); w = (xx) + ROTATE_LEFT(w, s);

void Md5Transform_3693c0(MD5Ctx *ctx, u8 *in)
{
    u64 a;
    u64 b;
    u64 c;
    u64 d;
    u64 x[16];

    x[0] = (u64)in[0] | ((u64)in[1] << 8) | ((u64)in[2] << 16) | ((u64)in[3] << 24);
    x[1] = (u64)in[4] | ((u64)in[5] << 8) | ((u64)in[6] << 16) | ((u64)in[7] << 24);
    x[2] = (u64)in[8] | ((u64)in[9] << 8) | ((u64)in[10] << 16) | ((u64)in[11] << 24);
    x[3] = (u64)in[12] | ((u64)in[13] << 8) | ((u64)in[14] << 16) | ((u64)in[15] << 24);
    x[4] = (u64)in[16] | ((u64)in[17] << 8) | ((u64)in[18] << 16) | ((u64)in[19] << 24);
    x[5] = (u64)in[20] | ((u64)in[21] << 8) | ((u64)in[22] << 16) | ((u64)in[23] << 24);
    x[6] = (u64)in[24] | ((u64)in[25] << 8) | ((u64)in[26] << 16) | ((u64)in[27] << 24);
    x[7] = (u64)in[28] | ((u64)in[29] << 8) | ((u64)in[30] << 16) | ((u64)in[31] << 24);
    x[8] = (u64)in[32] | ((u64)in[33] << 8) | ((u64)in[34] << 16) | ((u64)in[35] << 24);
    x[9] = (u64)in[36] | ((u64)in[37] << 8) | ((u64)in[38] << 16) | ((u64)in[39] << 24);
    x[10] = (u64)in[40] | ((u64)in[41] << 8) | ((u64)in[42] << 16) | ((u64)in[43] << 24);
    x[11] = (u64)in[44] | ((u64)in[45] << 8) | ((u64)in[46] << 16) | ((u64)in[47] << 24);
    x[12] = (u64)in[48] | ((u64)in[49] << 8) | ((u64)in[50] << 16) | ((u64)in[51] << 24);
    x[13] = (u64)in[52] | ((u64)in[53] << 8) | ((u64)in[54] << 16) | ((u64)in[55] << 24);
    x[14] = (u64)in[56] | ((u64)in[57] << 8) | ((u64)in[58] << 16) | ((u64)in[59] << 24);
    x[15] = (u64)in[60] | ((u64)in[61] << 8) | ((u64)in[62] << 16) | ((u64)in[63] << 24);

    a = ctx->buf[0];
    b = ctx->buf[1];
    c = ctx->buf[2];
    d = ctx->buf[3];

    STEP(F1, a, b, c, d, x[0], 7, 0xD76AA478U);
    STEP(F1, d, a, b, c, x[1], 12, 0xE8C7B756U);
    STEP(F1, c, d, a, b, x[2], 17, 0x242070DBU);
    STEP(F1, b, c, d, a, x[3], 22, 0xC1BDCEEEU);
    STEP(F1, a, b, c, d, x[4], 7, 0xF57C0FAFU);
    STEP(F1, d, a, b, c, x[5], 12, 0x4787C62AU);
    STEP(F1, c, d, a, b, x[6], 17, 0xA8304613U);
    STEP(F1, b, c, d, a, x[7], 22, 0xFD469501U);
    STEP(F1, a, b, c, d, x[8], 7, 0x698098D8U);
    STEP(F1, d, a, b, c, x[9], 12, 0x8B44F7AFU);
    STEP(F1, c, d, a, b, x[10], 17, 0xFFFF5BB1U);
    STEP(F1, b, c, d, a, x[11], 22, 0x895CD7BEU);
    STEP(F1, a, b, c, d, x[12], 7, 0x6B901122U);
    STEP(F1, d, a, b, c, x[13], 12, 0xFD987193U);
    STEP(F1, c, d, a, b, x[14], 17, 0xA679438EU);
    STEP(F1, b, c, d, a, x[15], 22, 0x49B40821U);
    STEP(F2, a, b, c, d, x[1], 5, 0xF61E2562U);
    STEP(F2, d, a, b, c, x[6], 9, 0xC040B340U);
    STEP(F2, c, d, a, b, x[11], 14, 0x265E5A51U);
    STEP(F2, b, c, d, a, x[0], 20, 0xE9B6C7AAU);
    STEP(F2, a, b, c, d, x[5], 5, 0xD62F105DU);
    STEP(F2, d, a, b, c, x[10], 9, 0x02441453U);
    STEP(F2, c, d, a, b, x[15], 14, 0xD8A1E681U);
    STEP(F2, b, c, d, a, x[4], 20, 0xE7D3FBC8U);
    STEP(F2, a, b, c, d, x[9], 5, 0x21E1CDE6U);
    STEP(F2, d, a, b, c, x[14], 9, 0xC33707D6U);
    STEP(F2, c, d, a, b, x[3], 14, 0xF4D50D87U);
    STEP(F2, b, c, d, a, x[8], 20, 0x455A14EDU);
    STEP(F2, a, b, c, d, x[13], 5, 0xA9E3E905U);
    STEP(F2, d, a, b, c, x[2], 9, 0xFCEFA3F8U);
    STEP(F2, c, d, a, b, x[7], 14, 0x676F02D9U);
    STEP(F2, b, c, d, a, x[12], 20, 0x8D2A4C8AU);
    STEP(F3, a, b, c, d, x[5], 4, 0xFFFA3942U);
    STEP(F3, d, a, b, c, x[8], 11, 0x8771F681U);
    STEP(F3, c, d, a, b, x[11], 16, 0x6D9D6122U);
    STEP(F3, b, c, d, a, x[14], 23, 0xFDE5380CU);
    STEP(F3, a, b, c, d, x[1], 4, 0xA4BEEA44U);
    STEP(F3, d, a, b, c, x[4], 11, 0x4BDECFA9U);
    STEP(F3, c, d, a, b, x[7], 16, 0xF6BB4B60U);
    STEP(F3, b, c, d, a, x[10], 23, 0xBEBFBC70U);
    STEP(F3, a, b, c, d, x[13], 4, 0x289B7EC6U);
    STEP(F3, d, a, b, c, x[0], 11, 0xEAA127FAU);
    STEP(F3, c, d, a, b, x[3], 16, 0xD4EF3085U);
    STEP(F3, b, c, d, a, x[6], 23, 0x04881D05U);
    STEP(F3, a, b, c, d, x[9], 4, 0xD9D4D039U);
    STEP(F3, d, a, b, c, x[12], 11, 0xE6DB99E5U);
    STEP(F3, c, d, a, b, x[15], 16, 0x1FA27CF8U);
    STEP(F3, b, c, d, a, x[2], 23, 0xC4AC5665U);
    STEP(F4, a, b, c, d, x[0], 6, 0xF4292244U);
    STEP(F4, d, a, b, c, x[7], 10, 0x432AFF97U);
    STEP(F4, c, d, a, b, x[14], 15, 0xAB9423A7U);
    STEP(F4, b, c, d, a, x[5], 21, 0xFC93A039U);
    STEP(F4, a, b, c, d, x[12], 6, 0x655B59C3U);
    STEP(F4, d, a, b, c, x[3], 10, 0x8F0CCC92U);
    STEP(F4, c, d, a, b, x[10], 15, 0xFFEFF47DU);
    STEP(F4, b, c, d, a, x[1], 21, 0x85845DD1U);
    STEP(F4, a, b, c, d, x[8], 6, 0x6FA87E4FU);
    STEP(F4, d, a, b, c, x[15], 10, 0xFE2CE6E0U);
    STEP(F4, c, d, a, b, x[6], 15, 0xA3014314U);
    STEP(F4, b, c, d, a, x[13], 21, 0x4E0811A1U);
    STEP(F4, a, b, c, d, x[4], 6, 0xF7537E82U);
    STEP(F4, d, a, b, c, x[11], 10, 0xBD3AF235U);
    STEP(F4, c, d, a, b, x[2], 15, 0x2AD7D2BBU);
    STEP(F4, b, c, d, a, x[9], 21, 0xEB86D391U);

    ctx->buf[0] += a;
    ctx->buf[1] += b;
    ctx->buf[2] += c;
    ctx->buf[3] += d;
}
