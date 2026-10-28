/* rgp:protos */
#define RGP_SELF_ModelResGetWeightFormat_14cd10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0x20 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0014cd10 {
    u8 pad000[0x14];
    u8 val;         /* +0x14 */
} Sub_FUN_0014cd10;

typedef struct Obj_FUN_0014cd10 {
    Sub_FUN_0014cd10 *p;         /* +0x0 */
} Obj_FUN_0014cd10;

s32 ModelResGetWeightFormat_14cd10(Obj_FUN_0014cd10 *o)
{
    Sub_FUN_0014cd10 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0x20;
}
