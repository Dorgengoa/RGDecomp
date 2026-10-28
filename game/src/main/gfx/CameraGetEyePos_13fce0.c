/* rgp:protos */
#define RGP_SELF_CameraGetEyePos_13fce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/* Copy one 16-byte row out of the sub-object, if there is one. */

typedef struct Sub_FUN_0013fce0 {
    u8 pad000[0x170];
    u128 row;          /* +0x170 */
} Sub_FUN_0013fce0;

typedef struct Obj_FUN_0013fce0 {
    u8 pad000[0xF20];
    Sub_FUN_0013fce0 *p;   /* +0xF20 */
} Obj_FUN_0013fce0;

void CameraGetEyePos_13fce0(Obj_FUN_0013fce0 *o, u128 *out)
{
    Sub_FUN_0013fce0 *p;

    p = o->p;
    if (p != 0) {
        *out = p->row;
    }
}
