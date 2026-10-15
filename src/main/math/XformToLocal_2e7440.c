#include "types.h"

extern void VecCopy_1cbe30(void *, f32 *);

void XformToLocal_2e7440(f32 *m, void *dst, f32 *c)
{
    f32 tmp[3] = {0};
    f32 out[4];

    tmp[0] = c[0] - c[3] * m[6];
    tmp[1] = c[1] - c[3] * m[7];
    tmp[2] = c[2] - c[3] * m[8];
    out[0] = (m[9] * tmp[0] + m[10] * tmp[1] + m[11] * tmp[2]) / m[0];
    out[1] = (m[12] * tmp[0] + m[13] * tmp[1] + m[14] * tmp[2]) / m[1];
    out[2] = (m[15] * tmp[0] + m[16] * tmp[1] + m[17] * tmp[2]) / m[2];
    out[3] = c[3];
    VecCopy_1cbe30(dst, out);
}
