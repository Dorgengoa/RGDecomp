/* rgp:protos */
#define RGP_SELF_factory_FactoryMaterialGridRefresh_4f3730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F3730 -- forwarder that supplies the third
 * argument from the object.
 *
 * `j factory_FactoryMaterialGridBuild_4f3560` with `lh $6, 0x4($4)` in the delay slot: $4 and $5
 * pass straight through, and the callee's third parameter is `o->f4`.
 */

typedef struct Obj {
    u8   pad0[4];
    s16  f4;
} Obj;

/*rgp*/

s32 factory_FactoryMaterialGridRefresh_4f3730(Obj *o, s32 a)
{
    return factory_FactoryMaterialGridBuild_4f3560(o, a, o->f4);
}
