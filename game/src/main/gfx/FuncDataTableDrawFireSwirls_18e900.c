/* rgp:protos */
#define RGP_SELF_FuncDataTableDrawFireSwirls_18e900 1
#define RGP_SELF_next 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct Obj {
    u8 pad00[0x48];
    s32 x48;
    u8 pad4c[0x28];
    s32 x74;
} Obj;

typedef struct Node {
    struct Node *next;
    u8 pad04[0xC];
    Obj *obj;
} Node;

typedef struct Head {
    u8 pad00[0x8];
    Node *a;
    u8 pad0c[0x1C];
    Node *b;
} Head;

typedef struct List {
    u32 pad00;
    Head *head;
    Node *cur;
} List;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline Obj *next(List *l) {
    Node *n;
    n = l->cur;
    if (n == 0) {
        return 0;
    }
    l->cur = n->next;
    return n->obj;
}

void FuncDataTableDrawFireSwirls_18e900(void *mtx, List *list, s32 unused, void *tgt) {
    Vec4 v1 __attribute__((aligned(16)));
    Vec4 pos1 __attribute__((aligned(16)));
    Vec4 sz1 __attribute__((aligned(16)));
    Vec4 v2 __attribute__((aligned(16)));
    Vec4 pos2 __attribute__((aligned(16)));
    Vec4 sz2 __attribute__((aligned(16)));
    Obj *obj;
    f32 d;

    if (tgt != 0) {
        list->cur = 0;
        if (list->head != 0) {
            list->cur = list->head->a;
        }
        while ((obj = next(list)) != 0) {
            if (obj->x48 == 0) {
                continue;
            }
            if (obj->x74 == 0) {
                continue;
            }
            NodeGetTranslation_186650(obj, &pos1);
            NodeGetScale_186560(obj, &sz1);
            *(u128 *)&v1 = *(u128 *)&pos1;
            v1.w = 1.0f;
            MtxMulVec4_13c900(&v1, mtx, &v1);
            v1.y = v1.y + 10.0f * sz1.y;
            d = CameraDistToEye_15cdc0(&v1);
            if (!(d < 20.0f) && d <= 400.0f) {
                ParticleSwirlDraw_17d7b0(tgt, &v1, &sz1);
            }
        }
        list->cur = 0;
        list->cur = 0;
        if (list->head != 0) {
            list->cur = list->head->b;
        }
        while ((obj = next(list)) != 0) {
            if (obj->x48 == 0) {
                continue;
            }
            NodeGetTranslation_186650(obj, &pos2);
            NodeGetScale_186560(obj, &sz2);
            *(u128 *)&v2 = *(u128 *)&pos2;
            v2.w = 1.0f;
            MtxMulVec4_13c900(&v2, mtx, &v2);
            v2.y = v2.y + 10.0f * sz2.y;
            d = CameraDistToEye_15cdc0(&v2);
            if (!(d < 20.0f) && d <= 400.0f) {
                ParticleSwirlDraw_17d7b0(tgt, &v2, &sz2);
            }
        }
        list->cur = 0;
    }
}
