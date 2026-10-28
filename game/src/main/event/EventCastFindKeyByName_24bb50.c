/* rgp:protos */
#define RGP_SELF_EventCastFindKeyByName_24bb50 1
#define RGP_SELF_iter_begin 1
#define RGP_SELF_iter_end 1
#define RGP_SELF_iter_next 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strcmp(const char *, const char *);

typedef struct Node0024bb50 {
    struct Node0024bb50 *next;
    u8 pad4[8];
    s32 key;
    s32 data;
} Node0024bb50;

typedef struct Iter0024bb50 {
    Node0024bb50 *head;
    Node0024bb50 *cur;
    s32 done;
} Iter0024bb50;

static inline s32 iter_begin(Iter0024bb50 *it)
{
    if (it->cur != NULL) {
        return -1;
    }
    it->cur = it->head;
    it->done = 0;
    return 0;
}

static inline s32 *iter_next(Iter0024bb50 *it, s32 *key)
{
    Node0024bb50 *n;
    Node0024bb50 *nx;
    s32 *d;

    n = it->cur;
    if (n == NULL) {
        return NULL;
    }
    *key = n->key;
    d = &n->data;
    nx = n->next;
    it->cur = nx;
    if (nx == NULL) {
        it->done = 1;
    }
    return d;
}

static inline void iter_end(Iter0024bb50 *it)
{
    it->cur = NULL;
    it->done = 0;
}

s32 EventCastFindKeyByName_24bb50(Iter0024bb50 *arg0, char *arg1) {
    s32 key;
    s32 *p;
    s32 found;

    key = -1;
    if (iter_begin(arg0) != 0) {
        return 0;
    }
    found = 0;
    while ((p = iter_next(arg0, &key)) != NULL) {
        if (*p != 0 && strcmp(arg1, (const char *)*p) == 0) {
            found = 1;
            break;
        }
    }
    iter_end(arg0);
    if (found != 0) {
        return key;
    }
    return -1;
}
