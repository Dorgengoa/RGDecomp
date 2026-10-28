/* rgp:protos */
#define RGP_SELF_TaskMoveBefore_27bf50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Item {
    s32 a;
    s32 b;
    s32 c;
    u16 d;
    u16 e;
} Item;

/*rgp*/
/*rgp*/
extern Item D_004D7FA0[];
extern s32 D_004DAE90[];

s32 TaskMoveBefore_27bf50(s32 id, s32 before)
{
    Item tmp __attribute__((aligned(16)));
    Item *p;
    Item *q;
    s32 i;
    s32 j;
    s32 k;
    s32 tv;

    p = ((Item *)TaskFind_27c2f0(id));
    if (p == 0) {
        return 0;
    }
    if (before != 0) {
        q = ((Item *)TaskFind_27c2f0(before));
    } else {
        q = &D_004D7FA0[TaskTableCount_27c2d0()];
    }
    if (q == 0) {
        return 0;
    }
    if (p == q || p + 1 == q) {
        return 1;
    }
    i = p - D_004D7FA0;
    j = q - D_004D7FA0;
    tmp = D_004D7FA0[i];
    tv = D_004DAE90[i];
    if (j < i) {
        for (; j < i; i--) {
            D_004D7FA0[i].a = D_004D7FA0[i - 1].a;
            D_004DAE90[i] = D_004DAE90[i - 1];
            D_004D7FA0[i].b = D_004D7FA0[i - 1].b;
            D_004D7FA0[i].c = D_004D7FA0[i - 1].c;
            D_004D7FA0[i].d = D_004D7FA0[i - 1].d;
            D_004D7FA0[i].e = D_004D7FA0[i - 1].e;
        }
        D_004D7FA0[j].a = tmp.a;
        D_004D7FA0[j].b = tmp.b;
        D_004D7FA0[j].c = tmp.c;
        D_004D7FA0[j].d = tmp.d;
        D_004D7FA0[j].e = tmp.e;
        D_004DAE90[j] = tv;
    } else {
        for (k = i + 1; k < j; k++) {
            D_004D7FA0[k - 1].a = D_004D7FA0[k].a;
            D_004DAE90[k - 1] = D_004DAE90[k];
            D_004D7FA0[k - 1].b = D_004D7FA0[k].b;
            D_004D7FA0[k - 1].c = D_004D7FA0[k].c;
            D_004D7FA0[k - 1].d = D_004D7FA0[k].d;
            D_004D7FA0[k - 1].e = D_004D7FA0[k].e;
        }
        D_004D7FA0[j - 1].a = tmp.a;
        D_004D7FA0[j - 1].b = tmp.b;
        D_004D7FA0[j - 1].c = tmp.c;
        D_004D7FA0[j - 1].d = tmp.d;
        D_004D7FA0[j - 1].e = tmp.e;
        D_004DAE90[j - 1] = tv;
    }
    return 1;
}
