#include "types.h"

typedef struct Ent {
    u8    pad000[0x8];
    char *name;
} Ent;

typedef struct Pool {
    u8  pad000[0x7C];
    s16 count;
} Pool;

extern s32   DataTableHashName_368a10(Pool *o, const char *s);
extern Ent **DataTableHashBucketFind_368550(Pool *o, s32 h, s32 *n);
extern s32   strcmp(const char *a, const char *b);

Ent *TableFindByNameHashed_429540(Pool *o, const char *name)
{
    Ent **list;
    Ent  *e;
    s32   n;
    s32   t;
    s32   h;
    Ent **q;

    if (name == 0) return 0;
    if (o->count <= 0) return 0;
    h = DataTableHashName_368a10(o, name);
    n = 0;
    q = DataTableHashBucketFind_368550(o, (u16)h, &n);
    list = q;
    if (q == 0) return 0;
    goto test;
body:
    if (strcmp(e->name, name) == 0) return e;
    list++;
    n--;
test:
    e = *list;
    t = !(e != 0);
    if (t != 0) goto done;
    if (n > 0) goto body;
done:
    return 0;
}
