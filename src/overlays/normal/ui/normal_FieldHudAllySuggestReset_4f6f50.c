#include "types.h"
/* normal 0x004F6F50 -- a seven-store reset written in retail's EMISSION order
 * (0x3A2, 0x3AE, 0x3AC, 0x3A4, 0x3A6, 0x3A8, 0x3AA), which is not ascending.
 * Store order through ONE base is source order, so it is read off the listing.
 * One of the 55 unnamed functions. */
typedef struct Obj {
    u8  pad000[0x3A2];
    s16 f3A2;
    s16 f3A4;
    s16 f3A6;
    s16 f3A8;
    s16 f3AA;
    s16 f3AC;
    u8  f3AE;
} Obj;

void normal_FieldHudAllySuggestReset_4f6f50(Obj *p)
{
    p->f3A2 = 0;
    p->f3AE = 1;
    p->f3AC = 0;
    p->f3A4 = 0;
    p->f3A6 = 0;
    p->f3A8 = -1;
    p->f3AA = 0;
}
