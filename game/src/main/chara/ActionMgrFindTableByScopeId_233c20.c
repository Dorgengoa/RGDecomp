/* rgp:protos */
#define RGP_SELF_ActionMgrFindTableByScopeId_233c20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Member of the 5-clone group headed by ActionMgrFindById_233b50 (204 B each).
   This member differs from the head in the container offset `o + K` and
   the key-extractor / comparator pair.  The reading is written up in
   ActionMgrFindById_233b50.c. */

typedef struct Cont233 {
    u8  pad000[0x10];
    s32 m20;                    /* the container sub-object */
} Cont233;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void *ActionMgrFindTableByScopeId_233c20(Cont233 *o, s32 key)
{
    void *found;
    void *base;
    s32   n;
    void *cur;
    s32   c;

    if ((base = DListGetHead_42ea60(&o->m20)) == 0) {
        found = 0;
    } else {
        found = 0;
        n = ((unsigned short)DListGetCountPow2_42ea70(&o->m20));
        while (n > 0) {
            n >>= 1;
            cur = DListNodeAdvance_42eb00(base, n);
            if (cur != 0) {
                c = IntCompare_42ca30(key, ((short)ActCfgTableGetScopeId_223d00((u8 *)cur + 0x10)));
                if (c == 0) {
                    found = cur;
                    break;
                }
                if (c > 0) {
                    base = cur;
                }
            }
        }
    }
    return found == 0 ? 0 : (u8 *)found + 0x10;
}
