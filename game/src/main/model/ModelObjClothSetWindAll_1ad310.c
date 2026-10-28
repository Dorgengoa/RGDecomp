/* rgp:protos */
#define RGP_SELF_ModelObjClothSetWindAll_1ad310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0x170]; } E_001ad310;
typedef struct { u8 pad[0x204]; s32 f204; E_001ad310 *f208; } T_001ad310;

/*rgp*/

void ModelObjClothSetWindAll_1ad310(T_001ad310 *p, void *q, f32 v)
{
    s32 i;

    for (i = 0; i < p->f204; i++) {
        DynClothSetWind_169410(&p->f208[i], v, q);
    }
}
