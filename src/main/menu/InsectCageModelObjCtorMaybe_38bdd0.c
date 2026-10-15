#include "types.h"

struct T38BDD0 { u8 pad000[0x1C0]; void *f1C0; };

extern u8 D_00470F50[16];
extern void ModelObjExCtor_1c4920(void *);

struct T38BDD0 *InsectCageModelObjCtorMaybe_38bdd0(struct T38BDD0 *p)
{
    ModelObjExCtor_1c4920((u8 *)p + 0x10);
    p->f1C0 = D_00470F50;
    return p;
}
