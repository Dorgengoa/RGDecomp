/* rgp:protos */
#define RGP_SELF_FuncDataTableFindByName_1907c0 1
#define RGP_SELF_begin1907c0 1
#define RGP_SELF_end1907c0 1
#define RGP_SELF_next1907c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

typedef struct Node1907c0 {
    struct Node1907c0 *next;
    u8 pad4[0xC];
    void *obj;
} Node1907c0;

typedef struct {
    u8 pad0[0x4];
    Node1907c0 **tbl;
    Node1907c0 *cur;
} T1907c0_arg0;

static inline void begin1907c0(T1907c0_arg0 *t, s32 i)
{
    t->cur = NULL;
    if (t->tbl != NULL && i >= 0 && i < 11) {
        t->cur = t->tbl[i];
    }
}

static inline void *next1907c0(T1907c0_arg0 *t)
{
    Node1907c0 *n;

    n = t->cur;
    if (n == NULL) {
        return NULL;
    }
    t->cur = n->next;
    return n->obj;
}

static inline void end1907c0(T1907c0_arg0 *t)
{
    t->cur = NULL;
}

void *FuncDataTableFindByName_1907c0(T1907c0_arg0 *arg0, s32 arg1)
{
    void *result;
    void *v;
    s32 i;

    result = NULL;
    for (i = 1; i < 13; i++) {
        begin1907c0(arg0, i);
        while ((v = next1907c0(arg0)) != NULL) {
            if (Strcasecmp_1345b8(*(s32 *)((u8 *)v + 0x3C), arg1) == 0) {
                result = v;
                break;
            }
        }
        end1907c0(arg0);
        if (result != NULL) {
            break;
        }
    }
    return result;
}
