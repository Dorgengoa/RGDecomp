/* rgp:protos */
#define RGP_SELF_EventVoicePlay_24efd0 1
#define RGP_SELF_lbegin 1
#define RGP_SELF_lend 1
#define RGP_SELF_lnext 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node Node;
struct Node {
    Node *next;
    u8 pad4[0x8];
    s32 id;
    u8 data[4];
};
typedef struct List {
    Node *head;
    Node *cur;
    s32 end;
} List;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
static inline s32 lbegin(List *l)
{
    if (l->cur != NULL) {
        return -1;
    }
    l->cur = l->head;
    l->end = 0;
    return 0;
}
static inline void *lnext(List *l, s32 *id)
{
    Node *n = l->cur;
    void *d;
    if (n == NULL) {
        return NULL;
    }
    *id = n->id;
    d = n->data;
    l->cur = n->next;
    if (l->cur == NULL) {
        l->end = 1;
    }
    return d;
}
static inline void lend(List *l)
{
    l->cur = NULL;
    l->end = 0;
}

s32 EventVoicePlay_24efd0(List *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u8 sp170[0x100] __attribute__((aligned(16)));
    u8 sp70[0x100] __attribute__((aligned(16)));
    void *e;
    s32 id;

    EventVoiceMakePath_24edb0(arg0, arg1, sp170);
    FileMakeDevicePath_181980(sp170, sp70);
    if (arg3 < 0) {
        arg3 = EventVoicePickChan_24f270(arg0, 1);
        if (lbegin(arg0) != 0) {
            e = NULL;
        } else {
            while ((e = lnext(arg0, &id)) != NULL) {
                if (arg3 == id) {
                    break;
                }
            }
            lend(arg0);
        }
        EventVoiceChanStop_24e9e0(arg0, arg3, e, EventVoiceCountPlayingChans_24fae0(arg0));
    }
    if (arg3 >= 0) {
        StreamStartChan_1cda90(((s32)GetLoaderMgr_1f59d0()), arg3, sp70, arg2 != 0);
        EventVoiceChanSetRequested_24f1d0(arg0, arg3, arg1, 0, 0, 0);
    }
    return arg3;
}
