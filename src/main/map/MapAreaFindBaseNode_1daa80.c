#include "types.h"

extern s32 MapAreaDataGetModel_1e8c00(s32);
extern s32 MapAreaGetBaseObjName_1dce80(void *);
extern s32 ObjListFindRecByName_1894d0(s32, s32);
extern s32 NodeObjFindChildByName_195040(s32, void *);

extern u8 D_0045B378[];

struct Obj0 { u8 pad000[0x8]; s32 m08; };

s32 MapAreaFindBaseNode_1daa80(struct Obj0 *p0)
{
    s32 t0;
    s32 r0;
    s32 r1;
    s32 r2;

    t0 = p0->m08;
    if (t0 == 0) {
        return 0;
    }
    r0 = MapAreaDataGetModel_1e8c00(t0);
    if (r0 == 0) {
        return 0;
    }
    r1 = MapAreaGetBaseObjName_1dce80(p0);
    r2 = ObjListFindRecByName_1894d0(r0, r1);
    if (r2 != 0) {
        return NodeObjFindChildByName_195040(r2, D_0045B378);
    }
    return 0;
}
