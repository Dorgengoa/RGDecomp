#include "types.h"
/* normal 0x005060F0 -- pushes the popup's current scroll row into the previous
 * slot and takes a new one. */
typedef struct Obj { u8 pad00[0x74]; s16 f74; s16 f76; } Obj;
extern s32 normal_BtlChgPageSetScrollPos_5060f0(Obj *p, s16 v);
s32 normal_BtlChgPageSetScrollPos_5060f0(Obj *p, s16 v)
{
    p->f74 = p->f76;
    p->f76 = v;
    return 1;
}
