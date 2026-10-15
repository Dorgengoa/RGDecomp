#include "types.h"

struct Base {
    u8 pad[1];
};

struct Item {
    u8 pad0[0xC];
    s16 sC;
    u8 padE[0xC];
    u8 f1A;
};

struct Iter {
    u8 pad[8];
};

struct A88 {
    u8 pad0[0x88];
};

struct Slot : A88, Base {
    u8 pad89[0x98 - 0x89];
};

struct SlotTbl {
    u8 pad0[8];
    Slot *slots;
    Slot *Get(s32 idx);
};

struct Entry {
    s16 *key;
    u8 pad4[4];
    s16 idx;
    u8 padA[0x1C - 0xA];
};

struct Data {
    u8 pad0[0xC];
    Entry *entries;
    u8 pad10[0x74 - 0x10];
    SlotTbl *tbl;
};

struct Hdr {
    u8 pad0[4];
    s16 key;
};

struct Obj {
    u8 pad0[8];
    Data *data;
    u8 padC[4];
    void *p10;
    u8 pad14[4];
    Hdr *hdr;
};

extern "C" {
Item *IterNext_370040(Iter *);
void IterInit_370170(Iter *, Base *, Data *);
s32 PartyGetLocationGroupIdMaybe_3cb150(Hdr *);
s32 Bitset256Test_3cc650(void *, s32);
void StateFlagSet_3ccb70(void *, s32, bool, s32);
u8 StateFlagTest_3ccd70(void *, s32);
s32 SavePointAreaCompleteFlagIdMaybe_3ec9b0(Obj *, s32);
}

inline Slot *SlotTbl::Get(s32 idx)
{
    return (idx >= 0 && idx < 2) ? &slots[idx] : 0;
}

extern "C" bool SavePointAreaCompleteCheckMaybe_3ec7e0(Obj *self)
{
    s32 r;
    s16 key;
    s32 id;
    u8 busy;
    bool found;
    s32 i;
    Iter it;

    r = PartyGetLocationGroupIdMaybe_3cb150(self->hdr);
    if (r == 1 || r == 10) {
        return 0;
    }
    key = self->hdr->key;
    id = SavePointAreaCompleteFlagIdMaybe_3ec9b0(self, key);
    if (id < 0) {
        return 0;
    }
    busy = StateFlagTest_3ccd70(self->p10, id);
    found = false;
    for (i = 0; i < 2; i++) {
        Data *d = self->data;
        Entry *e = &d->entries[i];
        Slot *s;
        found = false;
        if (e == 0) continue;
        if (e->key == 0) continue;
        if (*e->key != key) continue;
        s = d->tbl->Get(e->idx);
        if (s == 0) continue;
        found = true;
        {
            Item *o;
            IterInit_370170(&it, s, d);
            while ((o = IterNext_370040(&it)) != 0) {
                if (!(o->f1A & 1) && !(Bitset256Test_3cc650(self->p10, o->sC) & 0xFF)) {
                    found = false;
                    break;
                }
            }
        }
        break;
    }
    if (found) {
        StateFlagSet_3ccb70(self->p10, id, found, 0);
    }
    {
        bool ret = false;
        if (!busy && found) {
            ret = true;
        }
        return ret;
    }
}
