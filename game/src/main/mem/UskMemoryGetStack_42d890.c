/* rgp:protos */
#define RGP_SELF_UskMemoryGetStack_42d890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x14. */

typedef struct Obj_FUN_0042d890 {
    u8 pad000[0x14];
    u8 sub[1];         /* +0x14 */
} Obj_FUN_0042d890;

void *UskMemoryGetStack_42d890(Obj_FUN_0042d890 *o)
{
    return o->sub;
}
