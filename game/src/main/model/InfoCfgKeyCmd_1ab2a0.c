/* rgp:protos */
#define RGP_SELF_InfoCfgKeyCmd_1ab2a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct Ent {
    u8 m00[0x24];
    f32 m24;
    f32 m28;
    f32 m2C;
};

/*rgp*/
/*rgp*/
/*rgp*/
extern void strcpy(void *, void *);

extern struct { struct Ent *v; s32 pad[3]; } D_0049D424;
extern struct { s32 v; s32 pad[3]; } D_0049D428;

s32 InfoCfgKeyCmd_1ab2a0(E8 *p0, s32 p1)
{
    struct Ent *base;
    struct Ent *e;
    char *s;

    if (p1 < 4) {
        return 0;
    }
    base = D_0049D424.v;
    if (base == 0) {
        return 0;
    }
    e = &base[D_0049D428.v];
    s = ((char *)SlotGetInt_15f720(p0++));
    if (s != 0) {
        strcpy(e, s);
    } else {
        e->m00[0] = 0;
    }
    e->m24 = (f32)VariantGetInt_15f780(p0++);
    e->m28 = (f32)VariantGetInt_15f780(p0++);
    e->m2C = VariantGetFloat_15f740(p0);
    D_0049D428.v = D_0049D428.v + 1;
    return 1;
}
