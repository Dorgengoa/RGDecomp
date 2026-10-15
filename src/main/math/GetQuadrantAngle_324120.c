#include "types.h"

extern s32 AngleToQuadrant_323fd0(void);

f32 GetQuadrantAngle_324120(void)
{
    return 90.0f * (f32)AngleToQuadrant_323fd0();
}
