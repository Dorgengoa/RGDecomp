/* rgp:protos */
#define RGP_SELF_ModelObjTexAnimBuildNameIndexMaybe_1abcd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Node {
    u8 pad0[8];
    char name[0x5C];
    struct Node *next;
} Node;

typedef struct {
    u8 pad0[8];
    Node *first;
} List;

typedef struct {
    Node *node;
    char name[0x20];
} Ent;

typedef struct {
    s32 f0;
    u8 pad4[8];
    s32 count;
    Ent *ents;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char *strcpy(char *dst, const char *src);
extern s32 D_0049D3B0[];
/*rgp*/

void ModelObjTexAnimBuildNameIndexMaybe_1abcd0(Obj *arg0, s32 arg1, s32 arg2)
{
    List *l;
    Node *p;
    s32 n;
    s32 i;
    s32 h;

    h = GetDrawCtxNameTable_15de40();
    if (arg0->f0 != 0 && D_0049D3B0[0] != 0) {
        l = ((List *)TableGetEntryOrDefault_159f60(h, arg1));
        if (l != NULL) {
            n = 0;
            for (p = l->first; p != NULL; p = p->next) {
                n++;
            }
            arg0->ents = ConstructNewArray_100710(MemStackNew_14e0b0(n * sizeof(Ent) + 0x10, arg2), ModelObjTexAnimNameIndexEntryCtorMaybe_1abe00, 0, sizeof(Ent), n);
            if (arg0->ents != NULL) {
                p = l->first;
                arg0->count = n;
                for (i = 0; i < n && p != NULL; i++) {
                    arg0->ents[i].node = p;
                    strcpy(arg0->ents[i].name, p->name);
                    p = p->next;
                }
            }
        }
    }
}
