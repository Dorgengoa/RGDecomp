/* rgp:protos */
#define RGP_SELF_FileCacheFindLoaderId_26a7f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strcmp(s32, void *);

extern s32 D_00482074;

struct Ent { s32 id; char name[128]; };
extern struct Ent D_004BE170[];

s32 FileCacheFindLoaderId_26a7f0(s32 p0)
{
    s32 l0;
    struct Ent *e;
    s32 r1;

    l0 = 0;
    while (l0 < D_00482074) {
        e = &D_004BE170[l0];
        r1 = strcmp(p0, e->name);
        if (r1 == 0) {
            return e->id;
        }
        l0 = (l0 + 1);
    }
    return -1;
}
