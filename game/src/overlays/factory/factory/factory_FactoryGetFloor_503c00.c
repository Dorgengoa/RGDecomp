/* rgp:protos */
#define RGP_SELF_factory_FactoryGetFloor_503c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00503C00 -- one field read, returned from the delay
 * slot of the epilogue's `jr $31`. */

typedef struct Obj {
    u8   pad0[0x234];
    s32  f234;
} Obj;

s32 factory_FactoryGetFloor_503c00(Obj *o)
{
    return o->f234;
}
