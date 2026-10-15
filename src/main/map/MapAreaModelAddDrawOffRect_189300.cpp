/* PARKED at triage (0 round trips): complex linked-list-of-unresolved-type
 * traversal (`var_4 = *var_4` chain with `?` element type) plus two
 * unresolved "?"-typed stack locals (sp90/spA0) passed to AabbContains_13e090 --
 * too much type ambiguity to compile confidently without a raw-asm read.
 * Deferred to preserve lane throughput. See asm/matchings/main/MapAreaModelAddDrawOffRect_189300.s. */
/* s49m: len 0x1A4 vs 0x1B0 ED 6 */
#include "types.h"

typedef unsigned __int128 u128;

extern "C" void *MemStackNew_14e230(s32 arg0, s32 arg1);
extern "C" s32 NodeObjGetWorldBounds_194420(void *obj, u8 *out);
extern "C" s32 AabbContains_13e090(u8 *a, u8 *b, void *c, void *d);
extern u8 D_00470538[0x40];

class Node {
public:
    u8 pad0[0x14];
    virtual void v08();
};

typedef struct Slot {
    u128 a;
    u128 b;
    s32 used;
    s32 arg;
    void **head;
} Slot;

typedef struct Ent {
    Slot slot;
} Ent;

typedef struct Mgr {
    u8 pad0[0x504];
    s32 nobj;
    void **objs;
    u8 pad50C[0x8C];
    s32 nent;
    u8 pad59C[4];
    Ent ents[1];
} Mgr;

extern "C" void MapAreaModelAddDrawOffRect_189300(Mgr *m, s32 tag, u128 *box, f32 *box2, s32 arg4)
{
    u8 bA0[0x10];
    u8 b90[0x10];
    Slot *slot;
    s32 i;
    s32 j;
    void *obj;
    u8 *p;
    void **n;
    void **t;
    s32 cnt;
    void **objs;

    slot = 0;
    for (i = 0; i < m->nent; i++) {
        if (m->ents[i].slot.used == 0) {
            slot = &m->ents[i].slot;
            break;
        }
    }
    ((f32 *)box)[3] = 1.0f;
    ((f32 *)box)[7] = 1.0f;
    box2[3] = 1.0f;
    box2[7] = 1.0f;
    if (slot == 0) {
        return;
    }
    slot->used = 1;
    slot->a = box[0];
    slot->b = box[1];
    slot->arg = arg4;
    cnt = m->nobj;
    objs = m->objs;
    for (j = 0; j < cnt; j++) {
        obj = objs[j];
        if (obj == 0) {
            continue;
        }
        if (NodeObjGetWorldBounds_194420(obj, b90) == 0) {
            continue;
        }
        if (AabbContains_13e090(b90, bA0, box2, box2 + 4) == 0) {
            continue;
        }
        p = (u8 *)MemStackNew_14e230(0x18, tag);
        if (p != 0) {
            *(void **)(p + 0x14) = D_00470538;
            ((Node *)p)->v08();
        }
        *(void **)(p + 0x10) = obj;
        if (slot->head == 0) {
            slot->head = (void **)p;
        } else {
            n = slot->head;
            while (n != 0) {
                t = (void **)*n;
                if (t == 0) {
                    break;
                }
                n = t;
            }
            *n = p;
            if (p != 0) {
                *(void **)(p + 0x4) = n;
            }
        }
    }
}
