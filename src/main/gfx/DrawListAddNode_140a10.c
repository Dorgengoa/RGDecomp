#include "types.h"

typedef struct { s32 a, b, c, d; } Quad00140a10;

typedef struct EntryT {
    s16 *f0;
    s32 f4;
    u8 pad8[0x24 - 0x8];
    struct EntryT *f24;
    u8 pad28[0x30 - 0x28];
} EntryT;

typedef struct Obj0014dad0 {
    u8 pad0[0x28];
    s32 unk28;
    s32 unk2C;
} Obj0014dad0;

typedef struct T00140a10 {
    u8 pad0[0x3BA4];
    Obj0014dad0 *f3BA4;
    u8 pad3BA8[0x3BB0 - 0x3BA8];
    s32 *f3BB0;
    s32 f3BB4;
    s32 *f3BB8;
    u8 pad3BBC[0x3BC8 - 0x3BBC];
    s32 *f3BC8;
    EntryT **f3BCC;
} T00140a10;

void DrawListAddNode_140a10(T00140a10 *arg0, EntryT *arg1, s32 arg2)
{
    s16 *ptr0;
    s32 id;
    s32 *tab;
    Obj0014dad0 *obj;
    EntryT *entry;
    s32 slot;

    ptr0 = arg1->f0;
    if (ptr0 != NULL) {
        id = *ptr0;
        if (id < arg0->f3BB4) {
            if (id < 0) {
                return;
            }
        } else {
            return;
        }
        tab = arg0->f3BB8;
        if (tab != NULL) {
            id = tab[id];
        }
        if (id < 0) {
            return;
        }
    } else {
        id = *arg0->f3BB0;
    }

    obj = arg0->f3BA4;
    slot = obj->unk2C;
    entry = (EntryT *)(obj->unk28 + slot * 0x10);
    obj->unk2C = slot + 3;
    *(__int128 *)((u8 *)entry + 0x00) = *(__int128 *)((u8 *)arg1 + 0x00);
    *(__int128 *)((u8 *)entry + 0x10) = *(__int128 *)((u8 *)arg1 + 0x10);
    *(__int128 *)((u8 *)entry + 0x20) = *(__int128 *)((u8 *)arg1 + 0x20);
    entry->f24 = arg0->f3BCC[arg2];
    arg0->f3BCC[arg2] = entry;
    entry->f4 = id;
    arg0->f3BC8[id] += 1;
}
