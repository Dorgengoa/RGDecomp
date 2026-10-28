/* rgp:protos */
#define RGP_SELF_ModelObjShadowFrameMapCtor_195450 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

typedef struct Obj_FUN_00195450 {
    s32 m00;         /* +0x0 */
    s32 m04;         /* +0x4 */
    s32 m08;         /* +0x8 */
    s32 m0C;         /* +0xC */
    s32 m10;         /* +0x10 */
} Obj_FUN_00195450;

Obj_FUN_00195450 * ModelObjShadowFrameMapCtor_195450(Obj_FUN_00195450 *o)
{
    o->m00 = 0;
    o->m08 = 0;
    o->m04 = 0;
    o->m10 = 0;
    o->m0C = 0;
    return o;
}
