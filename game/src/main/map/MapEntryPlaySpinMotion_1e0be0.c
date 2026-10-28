/* rgp:protos */
#define RGP_SELF_MapEntryPlaySpinMotion_1e0be0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0x20]; f32 x, y, z; u8 pad2[0x40 - 0x2C]; s32 flags; } O1e0be0;
typedef struct { u8 pad[0x790]; O1e0be0 *obj; } S1e0be0;

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045B448[16];
extern u8 D_0045B458[16];

void MapEntryPlaySpinMotion_1e0be0(S1e0be0 *arg0)
{
    O1e0be0 *o;

    o = arg0->obj;
    if (o == NULL) return;
    MapEntrySetPosRotY_1e0b40((int)arg0, o->x, o->y, o->z, 0.0f);
    o = arg0->obj;
    if (!(o->flags & 1)) return;
    if (SavePointIsActivated_426510(o) != 0) {
        ModelObjPlayMotionByName_1867a0(arg0, D_0045B448, 4);
    } else {
        ModelObjPlayMotionByName_1867a0(arg0, D_0045B458, 4);
    }
}
