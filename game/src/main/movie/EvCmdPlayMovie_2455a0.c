/* rgp:protos */
#define RGP_SELF_EvCmdPlayMovie_2455a0 1
#define RGP_SELF_begin 1
#define RGP_SELF_getnext 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Arg { s32 a, b; } Arg;
typedef struct Ctx { s32 x0; u8 *x4; } Ctx;

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

extern u8 D_0045EAC8[];
extern Ctx *gEventContext;

static inline s32 begin(u8 *it)
{
    if (*(u8 **)(it + 4) != NULL) {
        return -1;
    }
    *(u8 **)(it + 4) = *(u8 **)(it + 0);
    *(s32 *)(it + 8) = 0;
    return 0;
}

static inline u8 *getnext(u8 *it, s32 *key)
{
    u8 *cur;
    u8 *rec;
    u8 *next;

    cur = *(u8 **)(it + 4);
    if (cur == NULL) {
        rec = NULL;
    } else {
        *key = *(s32 *)(cur + 0xC);
        rec = cur + 0x10;
        next = *(u8 **)cur;
        *(u8 **)(it + 4) = next;
        if (next == NULL) {
            *(s32 *)(it + 8) = 1;
        }
    }
    return rec;
}

s32 EvCmdPlayMovie_2455a0(Arg *arg0, s32 arg1)
{
    s32 r;
    s32 spAC;
    s32 want;
    s32 h;
    s32 key;
    u8 *obj;
    u8 *it;
    s32 a;
    s32 v;
    s32 id;
    s32 b;
    u8 *rec;
    s32 c;
    s32 flag;

    h = RecStackPush_1c4240(gEventContext->x0, D_0045EAC8);
    id = ScriptGetCodeAddr_249050(arg0++);
    GetLoaderMgr_1f59d0();
    spAC = GetCurrentScene_1f5be0();
    obj = gEventContext->x4;
    it = obj + 0x60;
    want = EventCastFindKeyByName_24bb50(it, id);
    if (begin(it) != 0) {
        rec = NULL;
    } else {
        while ((rec = getnext(it, &key)) != NULL) {
            if (want == key) {
                break;
            }
        }
        *(u8 **)(it + 4) = NULL;
        *(s32 *)(it + 8) = 0;
    }
    b = 1;
    a = -1;
    c = 1;
    if (arg1 >= 2) {
        a = ScriptGetInt_2490f0(arg0++);
    }
    if (arg1 >= 3) {
        b = ScriptGetInt_2490f0(arg0++);
    }
    if (arg1 >= 4) {
        c = ScriptGetInt_2490f0(arg0);
    }
    v = ((s32)RecStackGetSlot_1c4330(gEventContext->x0, h));
    flag = 1;
    if (*(s32 *)(obj + 0xA60) & 1) {
        flag = 0;
    }
    if (rec != NULL) {
        r = MoviePlayModal_267c60(*(s32 *)(rec + 0x4), v, b, a, c, flag);
    } else {
        r = MoviePlayModal_267c60(id, v, b, a, c, flag);
    }
    RecStackPop_1c4140(gEventContext->x0, h);
    if (r == 2) {
        *(s32 *)(obj + 0xA60) |= 4;
        EventPlayerAbort_2498b0(obj, spAC);
    }
    return 1;
}
