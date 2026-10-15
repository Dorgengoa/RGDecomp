#include "types.h"
/* normal 0x005052C0 -- clears the popup's three scroll counters. */
typedef struct Obj { u8 pad00[0x74]; s16 f74; s16 f76; s16 f78; } Obj;
extern void normal_BtlChgPageScrollReset_5052c0(Obj *p);
void normal_BtlChgPageScrollReset_5052c0(Obj *p)
{
    p->f74 = 0;
    p->f76 = 0;
    p->f78 = 0;
}
