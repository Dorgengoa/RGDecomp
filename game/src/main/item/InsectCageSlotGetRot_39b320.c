/* rgp:protos */
#define RGP_SELF_InsectCageSlotGetRot_39b320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/* Copy one 16-byte row out of the sub-object, if there is one.
   Proven at CameraGetEyePos_13fce0. */

typedef struct Sub_FUN_0039b320 {
    u8 pad000[0x190];
    u128 row;          /* +0x190 */
} Sub_FUN_0039b320;

typedef struct Obj_FUN_0039b320 {
    u8 pad000[0x18];
    Sub_FUN_0039b320 *p;   /* +0x18 */
} Obj_FUN_0039b320;

void InsectCageSlotGetRot_39b320(Obj_FUN_0039b320 *o, u128 *out)
{
    Sub_FUN_0039b320 *p;

    p = o->p;
    if (p != 0) {
        *out = p->row;
    }
}
