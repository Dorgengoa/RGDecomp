/* rgp:protos */
#define RGP_SELF_EventCastAttachToFrame_24acd0 1
#define RGP_SELF_listBegin 1
#define RGP_SELF_listEnd 1
#define RGP_SELF_listNext 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

typedef struct Node {
    struct Node *next;
    u8 pad04[8];
    s32 key;
    u8 data[4];
} Node;

typedef struct List {
    Node *head;
    Node *cur;
    s32 done;
} List;

typedef struct Def {
    u8 pad00[8];
    s32 type;
    u8 pad0C[0x10];
    s32 x1C;
} Def;

typedef struct Ob {
    u8 pad00[4];
    void *x04;
    u8 pad08[0x20];
    u8 x28;
} Ob;


/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
s32 strcmp(const char *, const char *);
extern char D_0045EB68[];
extern f32 D_0047E7C0;
extern f32 D_0047E7C4;
extern f32 D_0047E7C8;
extern f32 D_0047E7CC;
extern f32 D_0047E7D0;
extern f32 D_0047E7D4;
extern f32 D_0047E7D8;
extern f32 D_0047E7DC;

static inline s32 listBegin(List *l) {
    if (l->cur != 0) {
        return -1;
    }
    l->cur = l->head;
    l->done = 0;
    return 0;
}

static inline void *listNext(List *l, s32 *key) {
    Node *n;
    Node *nx;
    void *d;
    n = l->cur;
    if (n == 0) {
        return 0;
    }
    *key = n->key;
    d = n->data;
    nx = n->next;
    l->cur = nx;
    if (nx == 0) {
        l->done = 1;
    }
    return d;
}

static inline void listEnd(List *l) {
    l->cur = 0;
    l->done = 0;
}

/*rgp*/

void EventCastAttachToFrame_24acd0(List *l, s32 id1, s32 id2, char *name) {
    Def *d[2];
    Ob *ob[2];
    void *mdl[2];
    volatile Vec vB0 __attribute__((aligned(16)));
    Vec vA0 __attribute__((aligned(16)));
    volatile Vec v90 __attribute__((aligned(16)));
    Vec v80 __attribute__((aligned(16)));
    void *g;
    s32 i;
    u8 *p;
    u32 n;
    Def *r;


    g = GetCurrentScene_1f5be0();
    if (listBegin(l) != 0) {
        r = 0;
    } else {
    s32 k1;
        while ((r = listNext(l, &k1)) != 0) {
            if (id1 == k1) {
                break;
            }
        }
        listEnd(l);
    }
    d[0] = r;
    if (r == 0) {
        return;
    }
    if (listBegin(l) != 0) {
        r = 0;
    } else {
    s32 k2;
        while ((r = listNext(l, &k2)) != 0) {
            if (id2 == k2) {
                break;
            }
        }
        listEnd(l);
    }
    d[1] = r;
    if (r == 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        ob[i] = 0;
        switch ((*(Def **)((u32)&d[i]))->type) {
        case 1:
        case 2:
        case 3:
        case 6:
        case 7:
            if ((mdl[(u32)i] = ObjRecGetLiveObject_1c4a90(g, (*(Def **)((u32)&d[i]))->x1C)) != 0) {
                ob[i] = ((Ob *)ModelGetFrame_1511f0(mdl[(u32)i], 0));
            }
            break;
        }
    }
    if (ob[0] == 0) {
        return;
    }
    if (ob[1] == 0) {
        return;
    }
    if (strcmp(name, D_0045EB68) != 0) {
        if ((ob[1] = ((Ob *)FrameFindByName_149ed0(ob[1], name))) == 0) {
            return;
        }
    }
    vB0.x = D_0047E7D0;
    vB0.y = D_0047E7D4;
    vB0.z = D_0047E7D8;
    vB0.w = D_0047E7DC;
    vB0.x = 0.0f;
    vB0.y = 0.0f;
    vB0.z = 0.0f;
    ModelSetPos_151110(mdl[0], (Vec *)&vB0);
    p = (u8 *)&vA0;
    n = 16;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    vA0.x = 0.0f;
    vA0.y = 0.0f;
    vA0.z = 0.0f;
    ModelSetRot_151080(mdl[0], &vA0);
    v90.x = D_0047E7C0;
    v90.y = D_0047E7C4;
    v90.z = D_0047E7C8;
    v90.w = D_0047E7CC;
    v90.x = 0.0f;
    v90.y = 0.0f;
    v90.z = 0.0f;
    FrameSetPos_14a450(ob[0], (Vec *)&v90);
    p = (u8 *)&v80;
    n = 16;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    v80.x = 0.0f;
    v80.y = 0.0f;
    v80.z = 0.0f;
    FrameSetRot_14a390(ob[0], &v80);
    ob[0]->x28 = 1;
    ob[0]->x04 = ob[1];
    FrameSetDirty_14a5e0(ob[0]);
}
