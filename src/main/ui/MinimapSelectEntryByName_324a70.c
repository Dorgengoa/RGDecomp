#include "types.h"

typedef struct {
    u8 pad0[0x54];
    u8 str[1];
} Elem00323530;

typedef struct {
    u8 pad0[0x4];
    f32 unk4;
} Obj0Arg2;

typedef struct {
    u8 pad0[0x106];
    s16 unk106;
} Obj0Arg0;

extern s32 EntryListFindByNameInRange_323420(u8 *, s32, f32, f32 );
extern s32 EntryListSelectNext_323500(u8 *);
extern s32 EntryTableGetCurrent_323530(u8 *);
extern s32 EntryListSelectByIndex_323540(u8 *, s32);
extern s16 EntryListGetCurIndex_3238b0(u8 *);
extern void MinimapRequestEntry_32ab90(Obj0Arg0 *, s32);
extern s32 strcmp(const char *, const char *);

static inline void apply324a70(Obj0Arg0 *arg0, Obj0Arg2 *arg2)
{
    u8 *lst;
    s32 v;
    s32 r;

    if (arg2 == NULL) {
        return;
    }
    lst = (u8 *)((u32)arg0 + 0x12C);
    if (lst == NULL) {
        return;
    }
    if (arg0->unk106 >= 0) {
        v = EntryListSelectByIndex_323540(lst, arg0->unk106);
        r = EntryListFindByNameInRange_323420(lst, v + 0x54, arg2->unk4, 0.0f);
        if (r != 0) {
            v = r;
        }
    } else {
        v = EntryListFindByNameInRange_323420(lst, 0, arg2->unk4, 0.0f);
    }
    MinimapRequestEntry_32ab90(arg0, v);
}

void MinimapSelectEntryByName_324a70(Obj0Arg0 *arg0, char *name, Obj0Arg2 *arg2)
{
    u8 *lst;
    s32 e;

    if (name == NULL) {
        return;
    }
    lst = (u8 *)arg0 + 0x12C;
    if (lst == NULL) {
        return;
    }
    EntryListSelectByIndex_323540(lst, 0);
loop:
    e = EntryTableGetCurrent_323530(lst);
    if (e == 0) {
        MinimapRequestEntry_32ab90(arg0, EntryListSelectByIndex_323540(lst, 0));
        return;
    }
    if (strcmp((const char *)(e + 0x54), name) != 0) {
        goto next;
    }
    arg0->unk106 = EntryListGetCurIndex_3238b0(lst);
    apply324a70(arg0, arg2);
    return;
next:
    EntryListSelectNext_323500(lst);
    goto loop;
}
