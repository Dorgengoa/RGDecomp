#include "types.h"

struct Inner {
    u8 pad00[0x1C];
};

struct Rec {
    u8 pad00[0x10];
    Inner inner;
};

class Owner {
    u8 pad00[0xC];
public:
    virtual s32 slot08(Rec *rec);
};

extern "C" s32 EventRecGetKey_2e5730(void *);
extern "C" Rec *DListGetHead_42ea60(Owner *);
extern "C" s32 DListGetCountPow2_42ea70(Owner *);
extern "C" Rec *DListNodeAdvance_42eb00(Rec *, s32);
extern "C" s32 StrCmpNullSafe_42ca40(s32, s32);
extern "C" void *MemStackHeapAlloc_14db10(void *, s32, s32, s32);
extern "C" Rec *MemStackNew_14e130(s32, void *);
extern "C" void DListNodeInit_42ec10(Rec *);
extern "C" void EventPosRecCtor_2e3800(Inner *);
extern "C" void EventPosRecReset_2e3740(Inner *);
extern "C" s32 EventPosRecClone_2e35e0(Inner *, void *, void *, void *, void *, s32);
extern "C" void MemStackReturnToOwnerMaybe_14dad0(void *);
extern "C" void MemStackHeapFree_14dcb0(void *, void *);

extern "C" Inner *EventPosRecAddUnique_2ead10(void *a0, s32 a1, void *a2, void *a3, Owner *a4)
{
    s32 key;
    Rec *cur;
    Rec *found;
    s32 n;
    Rec *node;
    s32 cmp;
    Inner *res;
    Rec *rec;
    void *buf;
    Rec *result;

    if (a3 == 0 || a2 == 0 || a4 == 0) {
        return 0;
    }
    key = EventRecGetKey_2e5730(a2);
    if ((cur = DListGetHead_42ea60(a4)) == 0) {
        found = 0;
    } else {
        found = 0;
        n = DListGetCountPow2_42ea70(a4);
        while (n > 0) {
            n = n >> 1;
            node = DListNodeAdvance_42eb00(cur, n);
            if (node != 0) {
                cmp = StrCmpNullSafe_42ca40(key, EventRecGetKey_2e5730(&node->inner));
                if (cmp == 0) {
                    found = node;
                    break;
                }
                if (cmp > 0) {
                    cur = node;
                }
            }
        }
    }
    res = (found == 0) ? (Inner *)0 : &found->inner;
    if (res != 0) {
        return 0;
    }
    if (a2 == 0 || a3 == 0) {
        result = 0;
    } else {
        buf = MemStackHeapAlloc_14db10(a3, 2, 0, 0x40);
        if (buf == 0) {
            goto fail;
        }
        if ((rec = MemStackNew_14e130(0x30, a3)) != 0) {
            DListNodeInit_42ec10(rec);
            EventPosRecCtor_2e3800(&rec->inner);
            DListNodeInit_42ec10(rec);
            EventPosRecReset_2e3740(&rec->inner);
        }
        if (rec == 0) {
            goto fail;
        }
        DListNodeInit_42ec10(rec);
        EventPosRecReset_2e3740(&rec->inner);
        if (EventPosRecClone_2e35e0(&rec->inner, buf, a2, a3, a0, a1) == 0) {
            goto fail;
        }
        MemStackReturnToOwnerMaybe_14dad0(a3);
        if (a4->slot08(rec) == 0) {
            goto fail;
        }
        result = rec;
        goto done;
    fail:
        MemStackReturnToOwnerMaybe_14dad0(a3);
        MemStackHeapFree_14dcb0(a3, buf);
        result = 0;
    }
done:
    return (result != 0) ? &result->inner : (Inner *)0;
}
