/* rgp:protos */
#define RGP_SELF_CharaNormalTableFindAndLoad_233a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A {
    u8  pad000[0x10];
    u8  m10;
    u8  pad011[0x2B];
    s32 m3C;
} A;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaNormalTableFindAndLoad_233a20(A *a, void *key, void *c)
{
    u8 *best;
    u8 *lo;
    s32 k;
    u8 *cur;
    s32 cc;
    u8 *p;

    if ((lo = ((u8 *)DListGetHead_42ea60(&a->m10))) != 0) {
        goto search;
    }
    best = 0;
    goto done;
search:
    best = 0;
    k = ((unsigned short)DListGetCountPow2_42ea70(&a->m10));
    while (k > 0) {
        k >>= 1;
        cur = ((u8 *)DListNodeAdvance_42eb00(lo, k));
        if (cur == 0) {
            continue;
        }
        cc = IntCompare_42ca30(key, ActCfgTableGetScopeId_223d00(cur + 0x10));
        if (cc == 0) {
            best = cur;
            goto done;
        }
        if (cc > 0) {
            lo = cur;
        }
    }
done:
    p = best == 0 ? 0 : best + 0x10;
    if (p == 0) {
        return 0;
    }
    return CharaNormalTableCreate_224270(p, c, a->m3C);
}
