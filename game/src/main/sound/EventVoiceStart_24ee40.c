/* rgp:protos */
#define RGP_SELF_Begin 1
#define RGP_SELF_End 1
#define RGP_SELF_EventVoiceStart_24ee40 1
#define RGP_SELF_Next 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    struct Node *next;
    u8 pad4[8];
    s32 id;
    u8 data[0x24];
} Node;

typedef struct {
    s32 pad0;
    s32 key;
} Data;

typedef struct {
    Node *head;
    Node *cur;
    s32 done;
} List;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, s32);

static inline s32 Begin(List *l)
{
    if (l->cur != NULL) {
        return -1;
    }
    l->cur = l->head;
    l->done = 0;
    return 0;
}

static inline Data *Next(List *l, s32 *id)
{
    Node *n = l->cur;
    Data *d;
    if (n == NULL) {
        return NULL;
    }
    *id = n->id;
    d = (Data *)n->data;
    l->cur = n->next;
    if (l->cur == NULL) {
        l->done = 1;
    }
    return d;
}

static inline void End(List *l)
{
    l->cur = NULL;
    l->done = 0;
}

s32 EventVoiceStart_24ee40(List *l, s32 key, s32 arg2, f32 fv)
{
    char buf1[0x100] __attribute__((aligned(16)));
    char buf2[0x100] __attribute__((aligned(16)));
    s32 ret;
    s32 id;
    Data *d;

    ret = -1;
    if (Begin(l) == 0) {
        while ((d = Next(l, &id)) != NULL) {
            if (d->key == key) {
                EventVoiceMakePath_24edb0(l, key, buf1);
                FileMakeDevicePath_181980(buf1, buf2);
                if (StreamIsChanActive_1cd8c0(((s32)GetLoaderMgr_1f59d0()), id, buf2) != 0) {
                    ret = id;
                } else {
                    memset(d, 0, 0x24);
                }
                break;
            }
        }
        End(l);
    }
    if (ret < 0) {
        ret = EventVoicePlay_24efd0(l, key, arg2, -1);
    }
    if (ret >= 0) {
        StreamPlayChan_1cda20(((s32)GetLoaderMgr_1f59d0()), ret, fv);
        EventVoiceChanSetPlaying_24f120(l, ret, key, 0, 0);
    }
    return ret;
}
