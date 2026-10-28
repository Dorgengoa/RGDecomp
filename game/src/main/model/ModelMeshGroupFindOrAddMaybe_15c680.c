/* rgp:protos */
#define RGP_SELF_ModelMeshGroupFindOrAddMaybe_15c680 1
#define RGP_SELF_find 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct N {
    struct N *next;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
} N;

/*rgp*/

static inline N *find(u8 *self, s32 key)
{
    N *n;
    for (n = *(N **)(self + 0xF0); n != NULL; n = n->next) {
        if (n->xC == key) {
            return n;
        }
    }
    return NULL;
}

N *ModelMeshGroupFindOrAddMaybe_15c680(u8 *self, s32 key, s32 pri, s32 heap)
{
    N *n;
    N *cur;
    N *prev;
    N *head;

    n = find(self, key);
    if (n != NULL) {
        return n;
    }
    n = ((N *)MemStackNew_14e230(0x14, heap));
    if (n == NULL) {
        return NULL;
    }
    n->next = NULL;
    n->x4 = 0;
    n->xC = -1;
    n->x8 = 0;
    n->x10 = 0;
    n->xC = key;
    n->x8 = pri;
    head = *(N **)(self + 0xF0);
    cur = head;
    if (head == NULL) {
        *(N **)(self + 0xF0) = n;
        return n;
    }
    prev = NULL;
    for (; cur != NULL; cur = cur->next) {
        if (cur->x8 > n->x8) {
            break;
        }
        prev = cur;
    }
    if (prev == NULL) {
        n->next = head;
        *(N **)(self + 0xF0) = n;
    } else {
        n->next = prev->next;
        prev->next = n;
    }
    return n;
}
