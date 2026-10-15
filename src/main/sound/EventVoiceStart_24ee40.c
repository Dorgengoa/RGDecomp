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

extern void FileMakeDevicePath_181980(char *, char *);
extern s32 StreamIsChanActive_1cd8c0(s32, s32, char *);
extern void StreamPlayChan_1cda20(s32, s32, f32);
extern s32 GetLoaderMgr_1f59d0(void);
extern void EventVoiceMakePath_24edb0(List *, s32, char *, s32);
extern s32 EventVoicePlay_24efd0(List *, s32, s32, s32);
extern void EventVoiceChanSetPlaying_24f120(List *, s32, s32, s32);
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
    char buf1[0x100];
    char buf2[0x100];
    s32 ret;
    s32 id;
    Data *d;

    ret = -1;
    if (Begin(l) == 0) {
        while ((d = Next(l, &id)) != NULL) {
            if (d->key == key) {
                EventVoiceMakePath_24edb0(l, key, buf1, 0x100);
                FileMakeDevicePath_181980(buf1, buf2);
                if (StreamIsChanActive_1cd8c0(GetLoaderMgr_1f59d0(), id, buf2) != 0) {
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
        StreamPlayChan_1cda20(GetLoaderMgr_1f59d0(), ret, fv);
        EventVoiceChanSetPlaying_24f120(l, ret, key, 0);
    }
    return ret;
}
