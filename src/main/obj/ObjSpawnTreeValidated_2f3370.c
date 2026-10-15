#include "types.h"
typedef struct Ctx3370 { u8 pad00[0x1C]; void *m1C; } Ctx3370;
typedef struct Ent3370 { u8 pad00[0xC]; void *mC; } Ent3370;
extern Ctx3370 *GetGameData_1fede0(void);
extern Ent3370 *ObjSpawnTree_3bbe20(void *, void *);
extern u8 UnitAddMonCharaMaybe_2f3160(void *, void *);
extern void ObjFreeRecursive_3bb4f0(void *, void *, s32);

Ent3370 *ObjSpawnTreeValidated_2f3370(void *a)
{
    Ent3370 *r;
    Ctx3370 *c;
    void *e;

    c = GetGameData_1fede0();
    r = ObjSpawnTree_3bbe20(c->m1C, a);
    if (r == 0) {
        return 0;
    }
    e = r->mC;
    if (UnitAddMonCharaMaybe_2f3160(e, a) != 0) {
        return r;
    }
    ObjFreeRecursive_3bb4f0(c->m1C, e, 1);
    return 0;
}
