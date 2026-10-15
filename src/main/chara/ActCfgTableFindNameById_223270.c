#include "types.h"

typedef struct Elem {
    s32 id;
    u8  pad04[0x4];
} Elem;

typedef struct Node {
    u8   pad00[0x12];
    s16  m12;
    u8   pad14[0xC];
    Elem *list;
    u8   pad_b[0x38];
    s16  count;
} Node;

extern s32 ActCfgTableGetScopeId_223d00(Node *o);
extern void *GetActionMgr_1fdb50(void);
extern Node *ActionMgrGetGlobalTable_234850(void *w);

Elem *ActCfgTableFindNameById_223270(Node *o, s32 key)
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
    o = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
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
    o = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
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
    o = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
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
    if (ActCfgTableGetScopeId_223d00(o) == 0x7FFF) {
        r = NULL;
        goto done;
    }
    o = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
    if (o == NULL) {
        r = NULL;
        goto done;
    }
    r = ActCfgTableFindNameById_223270(o, key);
done:
    return r;
}
