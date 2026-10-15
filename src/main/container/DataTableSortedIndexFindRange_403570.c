#include "types.h"

typedef struct {
    s16 key;
    u8 pad2[6];
} Ent00403570;

typedef struct {
    u8 pad0[0x7C];
    s16 unk7C;
    u8 pad7E[0xA0 - 0x7E];
    s16 unkA0;
    Ent00403570 *unkA4;
} Obj00403570;

Ent00403570 *DataTableSortedIndexFindRange_403570(Obj00403570 *arg0, s32 arg1, s32 *arg2)
{
    s16 key;
    s32 lo;
    s32 hi;
    s32 mid;
    Ent00403570 *tbl;
    Ent00403570 *found;
    Ent00403570 *e;
    Ent00403570 *last;

    if (arg0->unkA4 == NULL || arg0->unkA0 <= 0) {
        return NULL;
    }
    key = arg1;
    *arg2 = 0;
    found = NULL;
    hi = arg0->unkA0 - 1;
    tbl = arg0->unkA4;
    lo = 0;
    if (tbl[0].key == key) {
        found = tbl;
    } else if (key < tbl[0].key) {
        return NULL;
    } else {
        lo++;
        if (hi < lo) {
            return NULL;
        }
    }
    if (found == NULL) {
        e = &tbl[hi];
        if (e->key == key) {
            found = e;
        } else if (e->key < key) {
            return NULL;
        } else {
            hi--;
            if (hi < lo) {
                return NULL;
            }
        }
    }
    if (found == NULL) {
        while (lo <= hi) {
            mid = lo + (hi - lo + 1) / 2;
            e = &tbl[mid];
            if (e->key == key) {
                found = e;
                break;
            }
            if (e->key < key) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
    }
    if (found != NULL) {
        while (found > tbl) {
            e = found - 1;
            if (e->key != key) {
                break;
            }
            found = e;
        }
    }
    if (found != NULL) {
        *arg2 = 1;
        last = &arg0->unkA4[arg0->unk7C] - 1;
        if (found < last) {
            for (e = found + 1; e <= last; e++) {
                if (e->key != key) {
                    break;
                }
                (*arg2)++;
            }
        }
    }
    return found;
}
