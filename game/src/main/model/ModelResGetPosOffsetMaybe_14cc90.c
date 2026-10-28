/* rgp:protos */
#define RGP_SELF_ModelResGetPosOffsetMaybe_14cc90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/* Copy one 16-byte row out of the sub-object, if there is one.
   Proven at CameraGetEyePos_13fce0. */

typedef struct Sub_FUN_0014cc90 {
    u8 pad000[0x30];
    u128 row;          /* +0x30 */
} Sub_FUN_0014cc90;

typedef struct Obj_FUN_0014cc90 {
    Sub_FUN_0014cc90 *p;   /* +0x0 */
} Obj_FUN_0014cc90;

void ModelResGetPosOffsetMaybe_14cc90(Obj_FUN_0014cc90 *o, u128 *out)
{
    Sub_FUN_0014cc90 *p;

    p = o->p;
    if (p != 0) {
        *out = p->row;
    }
}
