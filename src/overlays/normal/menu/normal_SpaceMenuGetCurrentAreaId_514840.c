#include "types.h"
/* normal 0x0000514840 -- `bnel` past the -1 early return, then the s16 read at
 * 0x4 is the RETURN VALUE on the non-10 path (the compare leaves it in $2). */

typedef struct Act { u8 pad00[0x4]; s16 f4; } Act;
typedef struct Ent { u8 pad00[0x18]; Act *f18; } Ent;

extern Ent *func_1FEDE0(void);

s32 normal_SpaceMenuGetCurrentAreaId_514840(void)
{
    Ent *e;
    s32  v;

    e = func_1FEDE0();
    if (e == NULL) {
        return -1;
    }
    v = e->f18->f4;
    if (v == 10) {
        v = 7;
    }
    return v;
}
