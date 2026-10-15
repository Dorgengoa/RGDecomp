#include "types.h"
/* normal 0x00514750 -- call then return the parameter, held in $16. */

extern void normal_SpaceMenuObjInit_5146b0(void *p);

void *normal_SpaceMenuObjCtor_514750(void *p)
{
    normal_SpaceMenuObjInit_5146b0(p);
    return p;
}
