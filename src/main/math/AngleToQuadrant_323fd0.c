#include "types.h"
typedef struct { u8 pad[0xCC]; f32 xCC; } S323fd0;

s32 AngleToQuadrant_323fd0(S323fd0 *arg0)
{
    if (arg0->xCC > 360.0f) {
        while (arg0->xCC > 360.0f) {
            arg0->xCC = arg0->xCC - 360.0f;
        }
    }
    if ((-45.0f <= arg0->xCC) && (arg0->xCC < 45.0f)) {
        return 0;
    }
    if ((45.0f <= arg0->xCC) && (arg0->xCC < 135.0f)) {
        return 1;
    }
    if ((135.0f <= arg0->xCC) && (arg0->xCC < 225.0f)) {
        return 2;
    }
    if ((225.0f <= arg0->xCC) && (arg0->xCC < 315)) {
        return 3;
    }
    if ((315 <= arg0->xCC) && (arg0->xCC < 360.0f)) {
        return 0;
    }
    return 0;
}
