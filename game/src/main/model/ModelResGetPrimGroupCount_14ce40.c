/* rgp:protos */
#define RGP_SELF_ModelResGetPrimGroupCount_14ce40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0014ce40 {
    u8 pad000[0x70];
    s32 val;         /* +0x70 */
} Sub_FUN_0014ce40;

typedef struct Obj_FUN_0014ce40 {
    Sub_FUN_0014ce40 *p;         /* +0x0 */
} Obj_FUN_0014ce40;

s32 ModelResGetPrimGroupCount_14ce40(Obj_FUN_0014ce40 *o)
{
    Sub_FUN_0014ce40 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
