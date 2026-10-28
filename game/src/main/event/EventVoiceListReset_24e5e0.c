/* rgp:protos */
#define RGP_SELF_EventVoiceListReset_24e5e0 1
#define RGP_SELF_begin 1
#define RGP_SELF_next 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, u32);

typedef struct L {
    u8 *head;
    u8 *cur;
    s32 done;
    s32 xc;
    u8 pad[0x34];
    s32 x44;
} L;

static inline s32 begin(L *l) {
    if (l->cur != NULL) {
        return -1;
    }
    l->cur = l->head;
    l->done = 0;
    return 0;
}
static inline void *next(L *l) {
    u8 *c = l->cur;
    void *r;
    if (c == NULL) {
        r = NULL;
    } else {
        r = c + 0x10;
        l->cur = *(u8 **)c;
        if (l->cur == NULL) {
            l->done = 1;
        }
    }
    return r;
}
int EventVoiceListReset_24e5e0(L *arg0) { int rgp_v0 = 0;
    void *e;
    s32 s;

    if (begin(arg0) == 0) {
        while ((e = next(arg0)) != NULL) {
            memset(e, 0, 0x24);
        }
        arg0->cur = NULL;
        arg0->done = 0;
    }
    s = ((s32)GetLoaderMgr_1f59d0());
    StreamStopChan_1cda60(s, 1);
    StreamStopChan_1cda60(s, 2);
    (rgp_v0 = MesWinClose_2774f0(arg0->xc));
    arg0->x44 = 0;
return rgp_v0; }
