#include "types.h"

typedef struct Ent2205e0 {
    u8 pad00[0x3E];
    s16 m3E;
} Ent2205e0;

typedef struct A2205e0 {
    s8 *m00;
    void *m04;
    u8 pad08[0x8];
    u8 *m10;
    u8 pad14[0x10];
    s16 m24;
    u8 pad26[0x4];
    s16 m2A;
    u8 pad2C[0x8];
} A2205e0;

typedef struct T2205e0 {
    u8 pad00[0x28];
    A2205e0 *m28;
    s16 m2C;
} T2205e0;

extern void *DListGetHead_42ea60(void *a);
extern s32 DListGetCountPow2_42ea70(void *a);
extern Ent2205e0 *DListNodeAdvance_42eb00(void *node, s32 cnt);
extern s32 IntCompare_42ca30(void *p2, s32 key);
extern s32 StrNotEqual_1f5300(const s8 *a, const s8 *b);
extern void ActTimeAcclAddInRange_227990(void *q, void *p1, f32 x, f32 y);
extern void ActCfgTableAddTimeAcclRefs_2202a0(void *p0, void *p1, void *m04, s32 m24, f32 x, f32 y);

void ActCfgTableAddNormalTimeAccl_2205e0(u8 *p0, void *p1, void *p2, const s8 *p3, f32 x, f32 y)
{
    Ent2205e0 *found;
    void *node;
    s32 cnt;
    Ent2205e0 *e;
    T2205e0 *t;
    A2205e0 *arr;
    A2205e0 *hit;
    s32 i;
    s32 c;
    u8 *q;
    const s8 *s;

    node = DListGetHead_42ea60(p0 + 0x7C);
    if (node == 0) {
        found = 0;
    } else {
        found = 0;
        cnt = DListGetCountPow2_42ea70(p0 + 0x7C);
        while (cnt > 0) {
            cnt = cnt >> 1;
            e = DListNodeAdvance_42eb00(node, cnt);
            if (e != 0) {
                c = IntCompare_42ca30(p2, e->m3E);
                if (c == 0) {
                    found = e;
                    break;
                }
                if (c > 0) {
                    node = e;
                }
            }
        }
    }
    if (found == 0) {
        t = 0;
    } else {
        t = (T2205e0 *)((u8 *)found + 0x10);
    }
    if (t == 0) {
        return;
    }
    if (p3 == 0) {
        hit = 0;
    } else {
        arr = t->m28;
        if (arr == 0) {
            hit = 0;
        } else {
            for (i = 0; i < t->m2C; i++, arr = (A2205e0 *)((u8 *)arr + 0x34)) {
                s = arr->m00;
                if (*p3 != *s) {
                    continue;
                }
                if (StrNotEqual_1f5300(s + 1, p3 + 1) == 0) {
                    hit = arr;
                    goto found_l;
                }
            }
            hit = 0;
        }
    }
found_l:
    if (hit != 0) {
        q = hit->m10;
        if (q != 0) {
            i = 0;
            while (i < hit->m2A) {
                ActTimeAcclAddInRange_227990(q, p1, x, y);
                i++;
                q += 0x10;
            }
        }
        ActCfgTableAddTimeAcclRefs_2202a0(p0, p1, hit->m04, hit->m24, x, y);
    }
}
