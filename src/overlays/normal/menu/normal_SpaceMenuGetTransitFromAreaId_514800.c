#include "types.h"
/* normal 0x0000514800 -- `bnel` past the -1 early return, then the s16 read at
 * 0x1A6 is the RETURN VALUE on the non-10 path (the compare leaves it in $2). */

typedef struct Act { u8 pad00[0x1A6]; s16 f1A6; } Act;
typedef struct Ent { u8 pad00[0x18]; Act *f18; } Ent;

extern Ent *func_1FEDE0(void);

s32 normal_SpaceMenuGetTransitFromAreaId_514800(void)
{
    Ent *e;
    s32  v;

    e = func_1FEDE0();
    if (e == NULL) {
        return -1;
    }
    v = e->f18->f1A6;
    if (v == 10) {
        v = 7;
    }
    return v;
}
