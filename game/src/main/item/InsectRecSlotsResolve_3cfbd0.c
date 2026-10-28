/* rgp:protos */
#define RGP_SELF_InsectRecSlotsResolve_3cfbd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s16 pad0; s16 ids[5]; s32 ptrs[5]; } Tbl3CF;
typedef struct { u8 pad[0x18]; Tbl3CF *tbl; } Obj3CF;
typedef struct { u8 pad[0x18]; s32 x18; } DObj3CF;
/*rgp*/
/*rgp*/
extern DObj3CF *D_004838E8;

s32 InsectRecSlotsResolve_3cfbd0(Obj3CF *arg0) {
    s32 i;
    s32 r;
    s32 t;

    if (D_004838E8 == NULL) {
        return 0;
    }
    i = 0;
    do {
        r = 0;
        t = ((s32)InvFindByUniqueId_3c85d0(D_004838E8->x18, arg0->tbl->ids[i], 7, 0));
        if (t != 0) {
            r = ((s32)InvObjCastToInsect_3d3d10(t, 0, 0, 0));
        }
        if (r != 0) {
            arg0->tbl->ptrs[i] = r;
        } else {
            arg0->tbl->ids[i] = -1;
            arg0->tbl->ptrs[i] = 0;
        }
        i++;
    } while (i < 5);
    return 1;
}
