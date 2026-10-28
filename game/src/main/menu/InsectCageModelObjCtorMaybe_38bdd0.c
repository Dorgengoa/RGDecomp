/* rgp:protos */
#define RGP_SELF_InsectCageModelObjCtorMaybe_38bdd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T38BDD0 { u8 pad000[0x1C0]; void *f1C0; };

extern u8 D_00470F50[16];
/*rgp*/

struct T38BDD0 *InsectCageModelObjCtorMaybe_38bdd0(struct T38BDD0 *p, int rgp_a1, int rgp_a2, int rgp_a3)
{
    ModelObjExCtor_1c4920((u8 *)p + 0x10, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
    p->f1C0 = D_00470F50;
    return p;
}
