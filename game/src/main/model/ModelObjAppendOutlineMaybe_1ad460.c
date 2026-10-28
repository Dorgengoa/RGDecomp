/* rgp:protos */
#define RGP_SELF_Last 1
#define RGP_SELF_ModelObjAppendOutlineMaybe_1ad460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    u8 pad0[0x50];
    s32 x50;
    u32 x54;
    s32 x58;
    s32 x5C;
} Ent;

typedef struct Node64 {
    struct Node64 *unk0;
    struct Node64 *unk4;
    u8 pad8[8];
    Ent e;
} Node64;

typedef struct Own {
    u8 pad0[0x120];
    u8 x120[0xE0];
    Node64 *head;
} Own;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline Node64 *Last(Node64 *p)
{
    Node64 *q;

    while (p != NULL) {
        q = p->unk0;
        if (q == NULL) {
            break;
        }
        p = q;
    }
    return p;
}

void ModelObjAppendOutlineMaybe_1ad460(Own *arg0, s32 arg1, Node64 *arg2) {
    Ent *e;
    Node64 *p;
    Node64 *q;
    u8 *w;

    if (arg2 == NULL) {
        return;
    }
    e = &arg2->e;
    if (e == NULL) {
        return;
    }
    p = arg0->head;
    w = arg0->x120;
    if (p == NULL) {
        e->x54 = 1;
        arg0->head = arg2;
        e->x5C = 1;
        e->x58 = -1;
        ModelMeshTagAll_1526d0(w, e->x54);
    } else {
        e->x54 = Last(p)->e.x54 + 1;
        p = Last(arg0->head);
        p->unk0 = arg2;
        if (arg2 != NULL) {
            arg2->unk4 = p;
        }
        ModelTagMeshesUnderFrameName_1516e0(arg0, w, arg1, e->x54);
        if (((s32)ModelGetFrame_1511f0(arg0, ModelFindFrameIndexByName_151220(arg0, arg1))) != 0) {
            e->x5C = 1;
            e->x58 = ModelFindFrameIndexByName_151220(arg0, arg1);
        } else {
            e->x5C = 0;
            e->x58 = -1;
        }
    }
    e->x50 = 1;
}
