/* rgp:protos */
#define RGP_SELF_EventCastSetEnabledMaybe_24aa40 1
#define RGP_SELF_begin 1
#define RGP_SELF_getnext 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline s32 begin(u8 *arg0)
{
    if (*(u8 **)(arg0 + 4) != NULL) {
        return -1;
    }
    *(u8 **)(arg0 + 4) = *(u8 **)(arg0 + 0);
    *(s32 *)(arg0 + 8) = 0;
    return 0;
}

static inline u8 *getnext(u8 *arg0, s32 *key)
{
    u8 *cur;
    u8 *rec;
    u8 *next;

    cur = *(u8 **)(arg0 + 4);
    if (cur == NULL) {
        rec = NULL;
    } else {
        *key = *(s32 *)(cur + 0xC);
        rec = cur + 0x10;
        next = *(u8 **)cur;
        *(u8 **)(arg0 + 4) = next;
        if (next == NULL) {
            *(s32 *)(arg0 + 8) = 1;
        }
    }
    return rec;
}

void EventCastSetEnabledMaybe_24aa40(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 st;
    u8 *cur;
    u8 *next;
    u8 *rec;
    s32 key;
    s32 r;
    s32 v;

    if (begin(arg0) != 0) {
        rec = NULL;
    } else {
        while ((rec = getnext(arg0, &key)) != NULL) {
            if (arg1 == key) {
                break;
            }
        }
        *(u8 **)(arg0 + 4) = NULL;
        *(s32 *)(arg0 + 8) = 0;
    }
    if (rec != NULL) {
        *(s32 *)(rec + 0x40) = arg2;
    }
    r = EventCastGetKind_24c0d0(arg0, arg1, (int)arg2);
    switch (r) {
    case 1:
    case 2:
    case 3:
    case 6:
    case 7:
        v = EventCastGetObjId_24c160(arg0, arg1, 0);
        if (arg2 != 0) {
            ObjRecSetFlag2_1c3e80(arg3, 1, v);
        } else {
            ObjRecClearFlag2_1c3e40(arg3, 1, v);
        }
        break;
    }
}
