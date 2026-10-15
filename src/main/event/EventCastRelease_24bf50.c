#include "types.h"

extern void EventCastRecordRelease_24dc90(void *, s32);

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

void EventCastRelease_24bf50(u8 *arg0, s32 arg1, s32 arg2)
{
    s32 i;
    s32 n;
    s32 want;
    s32 key;
    u8 *rec;

    if (arg2 <= -1) {
        if (begin(arg0) != 0) {
            return;
        }
        while ((rec = getnext(arg0, &key)) != NULL) {
            EventCastRecordRelease_24dc90(rec, arg1);
        }
        *(u8 **)(arg0 + 4) = NULL;
        *(s32 *)(arg0 + 8) = 0;
        return;
    }
    for (i = 0; i < arg2; i++) {
        n = *(s32 *)(arg0 + 0x324);
        if (n <= 0) {
            return;
        }
        *(s32 *)(arg0 + 0x324) = --n;
        want = (*(s32 **)(arg0 + 0x320))[n];
        if (begin(arg0) != 0) {
            rec = NULL;
        } else {
            while ((rec = getnext(arg0, &key)) != NULL) {
                if (want == key) {
                    break;
                }
            }
            *(u8 **)(arg0 + 4) = NULL;
            *(s32 *)(arg0 + 8) = 0;
        }
        if (rec != NULL) {
            EventCastRecordRelease_24dc90(rec, arg1);
        }
    }
}
