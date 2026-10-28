/* rgp:protos */
#define RGP_SELF_EffTableCreateInstance_1a0df0 1
#define RGP_SELF_MotionEventEffectSpawn_1b0e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Key {
    __extension__ unsigned short lo : 16;
    unsigned short  : 0, hi : 16;
} __attribute__((aligned(2))) Key;

typedef struct Ent {
    u8 pad0[0xEC];
    s32 mEC;
    u8 mF0;
    u8 mF1;
} Ent;

typedef struct Info {
    u8 pad0[0x28];
    char *m28;
    char *m2C;
    u8 pad30[4];
    u8 m34;
    u8 m35;
} Info;

typedef struct Self {
    u8 pad0[0x538];
    s32 m538;
    u8 *m53C;
} Self;

/*rgp*/
extern void EffTableCreateInstance_1a0df0(Key *, u8 *, Key, s32);
extern Ent *HandleTableGetDeref_1a0ca0(u8 *, u32);
/*rgp*/
/*rgp*/
/*rgp*/

void MotionEventEffectSpawn_1b0e90(Key *ret, Self *self, Info *info)
{
    Key r __attribute__((aligned(16)));
    Key tmp __attribute__((aligned(16)));
    Key k __attribute__((aligned(16)));
    Key k2 __attribute__((aligned(16)));
    Key kk __attribute__((aligned(16)));
    Key t __attribute__((aligned(16)));
    char *name;
    u8 *mgr;
    s32 id;
    Ent *e;
    s32 v;

    *(u32 *)&r = 0;
    name = info->m28;
    if (name == 0 || name[0] == 0) {
        *(u32 *)ret = *(volatile u32 *)&r;
        return;
    }
    mgr = self->m53C;
    if (mgr == 0) {
        goto out;
    }
    id = self->m538;
    StrMapGetValue_1b13e0(&kk, mgr + 0xB0, name);
    EffTableCreateInstance_1a0df0(&tmp, mgr, kk, id);
    *(u32 *)&r = *(u32 *)&tmp;
    t.lo = ((Key *)&r)->lo;
    t.hi = ((Key *)&r)->hi;
    k = t;
    name = info->m2C;
    e = HandleTableGetDeref_1a0ca0(self->m53C, *(u32 *)&k);
    v = 0;
    if (name != 0 && name[0] != 0) {
        v = ((s32)ModelGetFrame_1511f0(self, ModelFindFrameIndexByName_151220(self, name)));
    }
    if (v == 0) {
        v = ModelGetRootFrame_1511a0(self);
    }
    if (e != 0 && v != 0) {
        e->mEC = v;
    }
    k2 = t;
    e = HandleTableGetDeref_1a0ca0(self->m53C, *(u32 *)&k2);
    if (e != 0) {
        e->mF0 = info->m34;
        e->mF1 = info->m35;
    }
out:
    *(u32 *)ret = *(volatile u32 *)&r;
}
