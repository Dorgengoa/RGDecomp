/* SPDX-License-Identifier: CC0-1.0 */
/* tests/protos fixture: a port provider header (like src/crt/crt.h).  Native
 * double soft-float helpers and two excluded-asm game functions with their
 * real (asm-derived) signatures.  Implemented in providers_impl.c. */
#include <stdint.h>
double dpmul(double a, double b);
double fptodp(float a);
float dptofp(double a);
int DoubleCmp_13b948(double a, double b);
void MatFromQuat_13c440(void *dst, void *quat);
void MotionListSetRateById_172110(void *m, int id, int slot, float rate);
/* Sony-style array typedef parameters decay to pointers (src/sce/vu0/sce_vu0.h) */
typedef float FixVec[4] __attribute__((aligned(16)));
void *FixCopyVector_13c480(FixVec v0, FixVec v1);
