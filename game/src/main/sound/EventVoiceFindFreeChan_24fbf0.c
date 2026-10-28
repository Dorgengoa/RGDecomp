/* rgp:protos */
#define RGP_SELF_EventVoiceFindFreeChan_24fbf0 1
#define RGP_SELF_it_begin 1
#define RGP_SELF_it_end 1
#define RGP_SELF_it_next 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct N24f { struct N24f *next; u8 pad4[8]; s32 unkC; s32 unk10; } N24f;
typedef struct {
    N24f *unk0;
    N24f *unk4;
    s32 unk8;
} T24fbf0_arg0;
static inline s32 it_begin(T24fbf0_arg0 *it) {
    if (it->unk4 != NULL) {
        return -1;
    }
    it->unk4 = it->unk0;
    it->unk8 = 0;
    return 0;
}
static inline void *it_next(T24fbf0_arg0 *it, s32 *key) {
    N24f *n;
    N24f *nx;
    void *p;
    n = it->unk4;
    if (n == NULL) {
        return NULL;
    }
    *key = n->unkC;
    p = &n->unk10;
    nx = n->next;
    it->unk4 = nx;
    if (nx == NULL) {
        it->unk8 = 1;
    }
    return p;
}
static inline void it_end(T24fbf0_arg0 *it) {
    it->unk4 = NULL;
    it->unk8 = 0;
}

s32 EventVoiceFindFreeChan_24fbf0(T24fbf0_arg0 *arg0) {
    s32 *p;
    s32 r;
    s32 v;

    r = -1;
    if (it_begin(arg0) != 0) {
        return -1;
    }
    while ((p = it_next(arg0, &v)) != NULL) {
        if (*p == 0) {
            r = v;
            break;
        }
    }
    it_end(arg0);
    return r;
}
