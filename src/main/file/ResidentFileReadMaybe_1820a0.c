#include "types.h"

typedef struct {
    s32 data;
    s32 size;
    s32 ref;
    s32 pad;
    s8 name[0x30];
} Ent;

s32 Strcasecmp_1345b8(s8 *, s8 *);
s32 FileReadByPath_181f80(s8 *, s32, s32 *, s32, s32);
s32 memcpy(s32, s32, u32);
s32 strncmp(s8 *, void *, s32);
extern u8 D_00459738[];
extern s32 D_00481208;
extern Ent D_0049A500[];

static inline Ent *find(s8 *name)
{
    Ent *e;
    s32 i;

    if (D_00481208 == 0) {
        return NULL;
    }
    for (i = 0, e = D_0049A500; i < 0x30; i++, e++) {
        if (e->data != 0 && Strcasecmp_1345b8(e->name, name) == 0) {
            return e;
        }
    }
    return NULL;
}

s32 ResidentFileReadMaybe_1820a0(s8 *arg0, s32 arg1, s32 *arg2)
{
    s8 *p;
    Ent *e;
    s32 i;

    p = arg0;
    while (*p != 0) {
        if (strncmp(p, D_00459738, 2) == 0) {
            for (;;) {
            }
        }
        p++;
    }
    if (arg2 != NULL) {
        *arg2 = 0;
    }
    e = find(arg0);
    if (e != NULL) {
        memcpy(arg1, e->data, e->size);
        e->ref--;
        if (arg2 != NULL) {
            *arg2 = e->size;
        }
        return 1;
    }
    return FileReadByPath_181f80(arg0, arg1, arg2, 0, -1);
}
