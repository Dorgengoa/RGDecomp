#include "types.h"
#pragma opt_propagation off

typedef unsigned __int128 u128;

typedef struct Item {
    u8 data[0x20];
} Item;

typedef struct Ent {
    u8 data[0x20];
    struct Ent *next;
    u8 pad24[0xC];
} Ent;

typedef struct { u128 q; } Q;
typedef union { u128 q; struct { f32 x, y, z, w; } f; } V4;

typedef struct M {
    u8 pad0[0x180];
    Q x180;
    u8 pad190[0x960 - 0x190];
    s32 count;
    Ent *ents;
    Ent *cur;
    u8 pad96C[0x984 - 0x96C];
    s8 mode;
    u8 pad985[0x990 - 0x985];
    u8 x990[4];
} M;

extern void PlacePointInit_3869f0(void *);
extern void Copy20Bytes_3869c0(Ent *, Item *);
extern s32 PlacePointCollectByKind_386430(void *, s32, Item *, s32);
extern f32 RandFloat_13c010(void);
extern void MenuObjParamsRollSpeed_387ea0(void *);

void MenuObjBuildRandomRoute_3871a0(M *m, void *src, s32 n)
{
    struct {
        Item a[256];
        u128 q;
    } w;
    s32 cnt;
    s32 i;
    s32 k;
    s32 r;
    Item *it;
    Ent *prev;
    Ent *first;
    f32 fk;
    Item *buf;
    s32 size;
    Ent *e;

    if (src == 0) {
        return;
    }
    cnt = n;
    if (m->count < n) {
        cnt = m->count;
    }
    w.q = m->x180.q;
    for (i = 0; i < m->count; i++) {
        e = &m->ents[i];
        PlacePointInit_3869f0(e);
        e->next = 0;
    }
    prev = 0;
    first = 0;
    size = 0x100;
    it = w.a;
    do {
        PlacePointInit_3869f0(it);
        it++;
    } while (it < &w.a[256]);
    buf = w.a;
    k = 0;
    if (m->mode == 0) {
        k += PlacePointCollectByKind_386430(src, 0, buf, 0x100);
    } else {
        r = PlacePointCollectByKind_386430(src, 1, buf, 0x100);
        k += r;
        k += PlacePointCollectByKind_386430(src, 2, &buf[r], size - r);
    }
    fk = (f32)k - 1.0f;
    for (i = 0; i < cnt; i++) {
        it = &w.a[(s32)(fk * RandFloat_13c010())];
        if (it == 0) {
            break;
        }
        Copy20Bytes_3869c0(&m->ents[i], it);
        if (prev != 0) {
            prev->next = &m->ents[i];
        }
        prev = &m->ents[i];
        if (first == 0) {
            first = prev;
        }
    }
    m->cur = m->ents;
    MenuObjParamsRollSpeed_387ea0(m->x990);
}
