/* rgp:protos */
#define RGP_SELF_EventVoiceTick_24f720 1
#define RGP_SELF_begin 1
#define RGP_SELF_begin2 1
#define RGP_SELF_end 1
#define RGP_SELF_next 1
#define RGP_SELF_next2 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 state;
    s32 x4;
    s32 cnt;
    s32 id;
    u8 x10[0x10];
} Item;

typedef struct Node {
    struct Node *next;
    s32 x4;
    s32 x8;
    s32 key;
    Item data;
} Node;

typedef struct {
    Node *head;
    Node *cur;
    s32 done;
} List;

typedef struct {
    u8 pad0[0xD8];
    s32 xD8[2];
    u8 padE0[8];
    s32 xE8[2];
} Item2;

typedef struct Node2 {
    struct Node2 *next;
    s32 x4;
    s32 x8;
    s32 key;
    Item2 data;
} Node2;

typedef struct {
    Node2 *head;
    Node2 *cur;
    s32 done;
} List2;

typedef struct {
    List list;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    u8 pad24[0x20];
    s32 x44;
} Self;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline s32 begin(List *l) {
    if (l->cur != 0) {
        return -1;
    }
    l->cur = l->head;
    l->done = 0;
    return 0;
}

static inline Item *next(List *l, s32 *key) {
    Node *n = l->cur;
    Node *nx;
    Item *it;
    if (n == 0) {
        return 0;
    }
    *key = n->key;
    it = &n->data;
    nx = n->next;
    l->cur = nx;
    if (nx == 0) {
        l->done = 1;
    }
    return it;
}

static inline void end(List *l) {
    l->cur = 0;
    l->done = 0;
}

static inline s32 begin2(List2 *l) {
    if (l->cur != 0) {
        return -1;
    }
    l->cur = l->head;
    l->done = 0;
    return 0;
}

static inline Item2 *next2(List2 *l, s32 *key) {
    Node2 *n = l->cur;
    Node2 *nx;
    Item2 *it;
    if (n == 0) {
        return 0;
    }
    *key = n->key;
    it = &n->data;
    nx = n->next;
    l->cur = nx;
    if (nx == 0) {
        l->done = 1;
    }
    return it;
}

void EventVoiceTick_24f720(Self *self) {
    s32 w;
    s32 x;
    Node *n;
    Item *it;
    s32 key;
    s32 r;
    s32 o;
    u8 *p;
    List2 *q;
    s32 id;
    s32 cnt;
    Node2 *n2;
    s32 j;
    Item2 *found;
    s32 k;
    s32 a;
    s32 b;


    w = GetCurrentScene_1f5be0();
    x = ((s32)GetLoaderMgr_1f59d0());
    EventVoiceCountFreeChans_24fb70(self);
    cnt = EventVoiceCountPlayingChans_24fae0(self);
    if (begin(&self->list) != 0) {
        return;
    }
    while ((it = next(&self->list, &key)) != 0) {
        if (it->state == 0) {
            continue;
        }
        if (it->state == 2) {
            r = StreamGetChanStatus_1cd930(x, key);
            if (r != -1 && r != 1) {
                cnt--;
                if (r == -2) {
                    EventVoiceStopSetWait_24e8c0(self, key, it, cnt);
                } else {
                    EventVoiceChanStop_24e9e0(self, key, it, cnt);
                }
            }
            if (r == 1) {
                self->x18 = -1;
            }
            r = StreamGetChanPeakLevel_1cd900(x, key);
            o = ((s32)ObjRecGetLiveObject_1c4a90(w, it->id));
            if (o != 0) {
                if (r > 1000) {
                    ModelObjTexAnimStartByName_1ac590(o, it->x10);
                } else {
                    ModelObjTexAnimResetByName_1ac510(o, it->x10);
                }
            }
            p = ((u8 *)GetCurEventPlayer_26b830());
            if (p != 0 && r > 1000) {
                q = (List2 *)(p + 0x60);
                id = EventCastFindKeyByObjId_24b1d0(q, it->id, 0, 0);
                if (begin2(q) != 0) {
                    found = 0;
                } else {
                    while ((found = next2(q, &k)) != 0) {
                        if (id == k) {
                            break;
                        }
                    }
                    q->cur = 0;
                    q->done = 0;
                }
                for (j = 0; j < 2; j++) {
                    if (found != 0 && found->xD8[j] != 0) {
                        found->xE8[j] = 2;
                    }
                }
            }
        }
        if (it->cnt >= 0) {
            it->cnt++;
        }
    }
    end(&self->list);
    if (self->x44 > 0) {
        key = EventVoiceFindFreeChan_24fbf0(self);
        if (key >= 0) {
            b = EventVoicePendingPop_24e6b0(self);
            if (b >= 0) {
                EventVoicePlay_24efd0(self, b, 0, key);
            }
        }
    }
    if (self->x20 == 0) {
        return;
    }
    if (self->xC != 0 && self->x10 >= 0) {
        if (MesWinGetState_276a80(self->xC) == 3 || MesWinGetState_276a80(self->xC) == 5) {
            if (--self->x10 <= -1) {
                MesWinClose_2774f0(self->xC);
                self->x1C = 1;
            }
        }
    }
    if (StateFlagTest_3ccd70(*(s32 *)(((u8 *)GetGameData_1fede0()) + 0x10), 0x7ED) == 0) {
        if (self->x18 > 0) {
            self->x18--;
            if (self->x18 == 0) {
                MesWinAdvance_2768f0(self->xC);
                self->x14++;
                MesWinOwnerCalcPageWait_24e860(self);
            }
        }
    }
}
