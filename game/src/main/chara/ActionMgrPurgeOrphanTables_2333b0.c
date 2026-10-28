/* rgp:protos */
#define RGP_SELF_ActionMgrPurgeOrphanTables_2333b0 1
#define RGP_SELF_Detach1 1
#define RGP_SELF_Detach2 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x10];
    u8 data[0x10];
} Node;

typedef struct {
    u8 pad0[0x10];
} List;

typedef struct {
    List l0;
    List l10;
    List l20;
    u8 pad30[4];
    s32 x34;
    u8 pad38[4];
    s32 x3C;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline void Detach1(Obj *o, Node *n)
{
    s32 s;

    s = o->x3C;
    if (n != NULL) {
        if (s != 0) {
            MemStackHeapFree_14dcb0(s, ActCfgTableGetHeapBlock_223d10(n->data));
        }
        DListRemove_42e4e0(&o->l10, n);
    }
}

static inline void Detach2(Obj *o, Node *n)
{
    s32 s;

    s = o->x3C;
    if (n != NULL) {
        if (s != 0) {
            MemStackHeapFree_14dcb0(s, CharaRefGetBlock_3121d0(n->data));
        }
        DListRemove_42e4e0(&o->l0, n);
    }
}

void ActionMgrPurgeOrphanTables_2333b0(Obj *o)
{
    Node *n;
    Node *next;
    u8 *e;
    Node *c;
    Node *n2;
    Node *next2;

    next = ((Node *)DListGetHead_42ea60(&o->l10));
    while ((n = next) != NULL) {
        next = ((Node *)DListGetNext_42eb30(next));
        e = n->data;
        if (((short)ActCfgTableGetScopeId_223d00(e)) == 0x7FFF) {
            continue;
        }
        for (c = ((Node *)DListGetHead_42ea60(&o->l20)); c != NULL; c = ((Node *)DListGetNext_42eb30(c))) {
            if (((short)CharaGetActScopeId_214a70(c->data)) == ((short)ActCfgTableGetScopeId_223d00(e))) {
                break;
            }
        }
        if (c == NULL && n != NULL) {
            if (((short)ActCfgTableGetScopeId_223d00(n->data)) == 0x7FFF) {
                o->x34 = 0;
            }
            ActCfgTableFreeActions_223f20(n->data, o->x3C);
            Detach1(o, n);
        }
    }
    next2 = ((Node *)DListGetHead_42ea60(&o->l0));
    while ((n2 = next2) != NULL) {
        next2 = ((Node *)DListGetNext_42eb30(next2));
        e = n2->data;
        if (((short)CharaRefGetId_3121c0(e)) == 0x7FFF) {
            continue;
        }
        for (c = ((Node *)DListGetHead_42ea60(&o->l20)); c != NULL; c = ((Node *)DListGetNext_42eb30(c))) {
            if (((short)CharaGetActScopeId_214a70(c->data)) == ((short)CharaRefGetId_3121c0(e))) {
                break;
            }
        }
        if (c == NULL && n2 != NULL) {
            Detach2(o, n2);
        }
    }
}
