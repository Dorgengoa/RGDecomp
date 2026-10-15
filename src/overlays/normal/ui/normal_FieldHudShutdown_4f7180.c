#include "types.h"
/* normal 0x004F7180 -- a reset: five stores through the parameter and one to a
 * gp pointer global, written in RETAIL'S EMISSION ORDER (0x378, 0x3A2, 0x3AE,
 * 0x3D4, 0x3AC), which is not ascending -- store order through ONE base is
 * source order, so it is read off the listing.
 * One of the 55 unnamed functions. */
typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x3A2 - 0x37A];
    s16 f3A2;
    u8  pad3A4[0x3AC - 0x3A4];
    s16 f3AC;
    u8  f3AE;
    u8  pad3AF[0x3D4 - 0x3AF];
    s32 f3D4;
} Obj;

extern void *D_00484414;

void normal_FieldHudShutdown_4f7180(Obj *p)
{
    p->f378 = 0;
    p->f3A2 = 0;
    p->f3AE = 0;
    p->f3D4 = -1;
    p->f3AC = 0;
    D_00484414 = 0;
}
