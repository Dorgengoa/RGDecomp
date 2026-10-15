#include "types.h"

typedef struct Info {
    u8 pad0[0x2C];
    f32 unk2C;
    s32 unk30;
} Info;

typedef struct Node {
    struct Node *next;
    Info *info;
} Node;

typedef struct Elem {
    f32 x;
    u8 pad4[0x100 - 4];
    s32 n;
    s32 *tbl;
    u8 pad108[0x110 - 0x108];
} Elem;

typedef struct Obj {
    u8 pad0[0x44];
    Node *head;
} Obj;

typedef struct Obj2 {
    u8 pad0[0xC0];
    s32 count;
    Elem *elems;
} Obj2;

extern "C" {
s32 ParticleEmitterSpawnMaybe_1a8ad0(Info *, f32, s32, Elem *, s32);
void EffObjStepChannels_1a9b50(Info *, Elem *, f32);
}

static inline u8 h1(Info *n, Elem *e)
{
    f32 x = e->x;
    if (n->unk30 != 0) {
        return 0;
    }
    {
        s32 r = n->unk2C < x;
        return (u8)r;
    }
}

static inline s32 h2(Elem *e)
{
    s32 j;
    for (j = 0; j < e->n; j++) {
        if (e->tbl[j] != 0) {
            return true;
        }
    }
    return false;
}

extern "C" s32 EffInstNodeUpdateEmitters_19b430(Obj *arg0, f32 f, s32 arg1, Obj2 *arg2, s32 arg3)
{
    s32 sum;
    Node *node;
    s32 i;
    Elem *e;
    Info *info;

    sum = 0;
    i = 0;
    for (node = arg0->head; ((node != NULL) ^ 1) == 0 && i < arg2->count; node = node->next, i++) {
        e = &arg2->elems[i];
        info = node->info;
        if (!h1(info, e) || h2(e)) {
            e->x += f;
            EffObjStepChannels_1a9b50(info, e, f);
            sum += ParticleEmitterSpawnMaybe_1a8ad0(node->info, f, arg1, e, arg3);
        }
    }
    return sum;
}
