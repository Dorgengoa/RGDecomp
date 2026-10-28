/* SPDX-License-Identifier: CC0-1.0 */
/* tests/protos: native implementations of fixture/providers/crt.h (the port
 * provider side; compiled as is, never staged). */
#include <string.h>
#include "fixture/providers/crt.h"

double dpmul(double a, double b) { return a * b; }
double fptodp(float a) { return (double)a; }
float dptofp(double a) { return (float)a; }
int DoubleCmp_13b948(double a, double b) { return a < b ? -1 : a > b ? 1 : 0; }

void MatFromQuat_13c440(void *dst, void *quat)
{
    ((float *)dst)[0] = ((float *)quat)[0];
}

int g_rate_id = -1, g_rate_slot = -1;
float g_rate = -1.0f;
void MotionListSetRateById_172110(void *m, int id, int slot, float rate)
{
    (void)m;
    g_rate_id = id;
    g_rate_slot = slot;
    g_rate = rate;
}

void *FixCopyVector_13c480(FixVec v0, FixVec v1)
{
    memcpy(v0, v1, 16);
    return v0;
}
