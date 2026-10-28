/* rgp:protos */
#define RGP_SELF_ActCfgTableFireNormalTimeClsn_21f960 1
#define RGP_SELF_FindEntry 1
#define RGP_SELF_Search 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Pair {
    s32 a;
    s32 b;
} Pair;

typedef struct Entry {
    s8 *name;
    Pair *pairs;
    u8 pad08[4];
    u8 *list;
    u8 pad10[0x14];
    s16 pairCount;
    u8 pad26[2];
    s16 listCount;
    u8 pad2A[0xA];
} Entry;

typedef struct Sub {
    u8 pad00[0x28];
    Entry *entries;
    s16 entryCount;
} Sub;

typedef struct Info {
    u8 pad00[0x3E];
    s16 key;
} Info;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline Entry *FindEntry(Sub *sub, s8 *name)
{
    Entry *e;
    s32 i;
    if (sub == 0) return 0;
    if (name == 0) return 0;
    e = sub->entries;
    if (e == 0) return 0;
    for (i = 0; i < sub->entryCount; i++, e++) {
        if (*name == *e->name && StrNotEqual_1f5300(e->name + 1, name + 1) == 0) {
            return e;
        }
    }
    return 0;
}

static inline Info *Search(void *tree, s32 key)
{
    void *node = DListGetHead_42ea60(tree);
    Info *found;
    s32 half;
    Info *info;
    s32 c;
    if (node == 0) return 0;
    found = 0;
    half = ((unsigned short)DListGetCountPow2_42ea70(tree));
    while (half > 0) {
        half >>= 1;
        info = ((Info *)DListNodeAdvance_42eb00(node, half));
        if (info == 0) continue;
        c = IntCompare_42ca30(key, info->key);
        if (c == 0) {
            found = info;
            break;
        }
        if (c > 0) node = info;
    }
    return found;
}

void ActCfgTableFireNormalTimeClsn_21f960(u8 *obj, s32 arg1, s32 key, s8 *name, f32 x, f32 y)
{
    Info *found;
    Sub *sub;
    Entry *e;
    u8 *l;
    Pair *pr;
    s32 n;
    s32 j;
    s32 i;

    found = Search(obj + 0x7C, key);
    e = FindEntry(found == 0 ? 0 : (Sub *)((u8 *)found + 0x10), name);
    if (e != 0) {
        l = e->list;
        if (l != 0) {
            GetActionMgr_1fdb50();
            n = e->listCount;
            for (j = 0; j < n; j++, l += 0x20) {
                if (((unsigned char)ActTimeClsnInRange_228560(l, x, y)) != 0) {
                    ActTimeClsnFire_227ac0(l, arg1, obj, e->name);
                }
            }
        }
        n = e->pairCount;
        pr = e->pairs;
        if (pr != 0) {
            for (i = 0; i < n; i++, pr++) {
                ActCfgTableFireTimeClsn_21f840(obj, arg1, pr->a, pr->b, x, y);
            }
        }
    }
}
