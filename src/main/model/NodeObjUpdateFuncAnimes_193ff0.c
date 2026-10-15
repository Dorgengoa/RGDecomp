#include "types.h"

struct Obj1 { s32 m00; u8 pad004[0xC]; s32 m10; };
struct Obj0 { u8 pad000[0x138]; s32 m138; s32 m13C; };

extern s32 FuncDataRecIsActiveAt_192170(s32, s32);
extern s32 FuncAnimeUpdate_191650(s32 *, s32);

void NodeObjUpdateFuncAnimes_193ff0(struct Obj0 *p0, s32 p1, s32 p2)
{
    struct Obj1 *l0;
    s32 t2;
    s32 *q;

    if (p0->m138 != 0) {
        return;
    }
    l0 = (struct Obj1 *)p0->m13C;
    while (l0 != 0) {
        t2 = l0->m10;
        q = &l0->m10;
        if (t2 != 0) {
            if (FuncDataRecIsActiveAt_192170(t2, p1) != 0) {
                FuncAnimeUpdate_191650(q, p2);
            }
        }
        l0 = (struct Obj1 *)l0->m00;
    }
}
