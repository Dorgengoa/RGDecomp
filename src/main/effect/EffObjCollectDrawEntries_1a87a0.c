/* PARKED s17b: not attempted. Linked-list walk with s128 (VU quad) field
   copies, nested allocate+link-into-hash-bucket logic, several fields whose
   types m2c left as `?`. Higher risk/time than the lane budget allows for a
   single pass; needs a careful asm read of
   asm/matchings/main/EffObjCollectDrawEntries_1a87a0.s before a first C draft is worth writing. */
/* s49m: 39 bad (right length) */
#include "types.h"
#include "vec.h"

typedef struct Info {
    u8 d[0x40];
    Vec4 pos;
} Info;

typedef struct Entry {
    struct Entry *next;
    s32 m4;
    s32 m8;
    s32 mC;
    Info info;
    s32 m60;
    s32 m64;
} Entry;

typedef struct Hash {
    s32 n;
    s32 base;
    Entry **tab;
    s32 lo;
    s32 hi;
} Hash;

typedef struct Elem {
    u8 pad0[0x18];
    s32 m18;
    s32 m1C;
    s32 m20;
    u8 pad24[0x14];
    s32 m38;
    s32 m3C;
} Elem;

typedef struct Node {
    struct Node *next;
    Elem *e;
} Node;

typedef struct Ctx {
    u8 pad0[0x100];
    s32 n;
    s32 *tab;
} Ctx;

typedef struct Self {
    u8 pad0[0x3C];
    s32 m3C;
    u8 pad40[0x24];
    Node *m64;
    u8 m68;
} Self;

extern void XformPairMulColor_19a170(Ctx *, Vec4 *);
extern void XformInitIdentity_1a86a0(Info *);
extern void XformPairComposeOffsetNoScale_199f60(Ctx *, Info *, s32);
extern void XformPairComposeOffset_19a010(Ctx *, Info *, s32);
extern void *OperatorNew_100990(s32);
extern void CopyQword5_1a8670(Info *, Info *);

s32 EffObjCollectDrawEntries_1a87a0(Self *self, Hash *hash, Ctx *ctx, s32 a3)
{
    volatile struct {
        s32 x;
        s32 y;
    } pr;
    Vec4 pos;
    Info info;
    s32 count;
    Node *node;
    s32 i;
    s32 m3C;
    s32 *pv;
    Elem *e;
    s32 eA0;
    s32 key;
    s32 idx;
    Entry *ent;
    Entry **bucket;

    count = 0;
    node = self->m64;
    i = 0;
    XformPairMulColor_19a170(ctx, &pos);
    m3C = self->m3C;
    while (node != 0) {
        if (i >= ctx->n) {
            break;
        }
        pv = &ctx->tab[i];
        e = node->e;
        i++;
        eA0 = e->m3C;
        pr.y = e->m18;
        pr.x = e->m1C;
        XformInitIdentity_1a86a0(&info);
        *(u128 *)&info.pos = *(u128 *)&pos;
        if (ctx != 0 && e->m38 == 0) {
            if (self->m68 != 0) {
                XformPairComposeOffsetNoScale_199f60(ctx, &info, a3);
            } else {
                XformPairComposeOffset_19a010(ctx, &info, a3);
            }
        }
        key = e->m20;
        idx = key - hash->base;
        if (idx < 0 || idx >= hash->n) {
            ent = 0;
        } else {
            ent = OperatorNew_100990(0x70);
            if (ent != 0) {
                ent->m8 = 0;
                ent->mC = 0;
                CopyQword5_1a8670(&ent->info, &info);
                ent->m64 = 0;
                ent->m60 = 0;
                ent->m4 = 0;
                ent->next = 0;
            }
            if (ent == 0) {
                ent = 0;
            } else {
                bucket = &hash->tab[idx];
                ent->next = *bucket;
                *bucket = ent;
                if (key < hash->lo) {
                    hash->lo = key;
                }
                if (hash->hi < key) {
                    hash->hi = key;
                }
            }
        }
        if (ent != 0) {
            count++;
            ent->m4 = *pv;
            ent->m8 = pr.y;
            ent->mC = pr.x;
            ent->m60 = m3C;
            ent->m64 = eA0;
        }
        node = node->next;
    }
    return count;
}
