/* rgp:protos */
#define RGP_SELF_ActCfgTableFindMoveById_223080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem {
    s32 id;
    u8  pad04[0xC];
} Elem;

typedef struct Node {
    u8   pad00[0x12];
    s16  m12;
    u8   pad14[0x10];
    Elem *list;
    u8   pad_b[0x36];
    s16  count;
} Node;

/*rgp*/
/*rgp*/
/*rgp*/

Elem *ActCfgTableFindMoveById_223080(Node *o, s32 key)
{
    Elem *e;
    s32 i;
    s32 n;
    Elem *r;

    e = o->list;
    if (e != NULL) {
        n = o->count;
        i = 0;
        while (i < n) {
            if (key == e->id) {
                return e;
            }
            i++;
            e++;
        }
    }
    if (o->m12 == 0x7FFF) {
        return NULL;
    }
    o = ((Node *)ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50()));
    if (o == NULL) {
        return NULL;
    }
    e = o->list;
    if (e != NULL) {
        n = o->count;
        i = 0;
        while (i < n) {
            if (key == e->id) {
                r = e;
                goto done;
            }
            i++;
            e++;
        }
    }
    if (o->m12 == 0x7FFF) {
        r = NULL;
        goto done;
    }
    o = ((Node *)ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50()));
    if (o == NULL) {
        r = NULL;
        goto done;
    }
    e = o->list;
    if (e != NULL) {
        n = o->count;
        i = 0;
        while (i < n) {
            if (key == e->id) {
                r = e;
                goto done;
            }
            i++;
            e++;
        }
    }
    if (o->m12 == 0x7FFF) {
        r = NULL;
        goto done;
    }
    o = ((Node *)ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50()));
    if (o == NULL) {
        r = NULL;
        goto done;
    }
    e = o->list;
    if (e != NULL) {
        n = o->count;
        i = 0;
        while (i < n) {
            if (key == e->id) {
                r = e;
                goto done;
            }
            i++;
            e++;
        }
    }
    if (((short)ActCfgTableGetScopeId_223d00(o)) == 0x7FFF) {
        r = NULL;
        goto done;
    }
    o = ((Node *)ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50()));
    if (o == NULL) {
        r = NULL;
        goto done;
    }
    r = ActCfgTableFindMoveById_223080(o, key);
done:
    return r;
}
