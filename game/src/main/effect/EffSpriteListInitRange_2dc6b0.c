/* rgp:protos */
#define RGP_SELF_EffSpriteListInitRange_2dc6b0 1
#include "port/game_protos.h"
#line 1
#pragma opt_repositioncode on
#include "types.h"

typedef struct {
    s16 f0;
    s16 f2;
    s32 f4;
    s32 f8;
    s32 fC;
    u8 f10[16];
    s32 f20[15];
    s32 f5C;
    u8 f60[16];
    u8 f70[16];
    u8 f80[16];
    u8 f90[16];
    u8 fA0[16];
    u8 fB0[16];
} Entry;

typedef struct {
    u8 pad0[0x244];
    Entry *list;
    s16 cap;
    char name[0x22];
    s32 f26C;
} Obj;

/*rgp*/
/*rgp*/
void *memset(void *, s32, u32);
char *strcpy(char *, const char *);

void EffSpriteListInitRange_2dc6b0(Obj *o, char *name, s32 start, s32 n) {
    s32 end;
    s32 h;

    if (o->list == 0) {
        return;
    }
    end = start + n;
    if (o->cap < end) {
        return;
    }
    h = ((s32)NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), name, o->f26C));
    strcpy(o->name, name);
    for (; start < end; start++) {
        strcpy(o->name, name);
        o->list[start].f4 = h;
        o->list[start].f0 = 0;
        o->list[start].f2 = 0;
        o->list[start].f8 = 0;
        o->list[start].fC = 1;
        memset(o->list[start].f10, 0, 16);
        o->list[start].f20[0] = 0;
        o->list[start].f20[1] = 0;
        o->list[start].f20[2] = 0;
        o->list[start].f20[3] = 0;
        o->list[start].f20[4] = 0;
        o->list[start].f20[5] = 0;
        o->list[start].f20[6] = 0;
        o->list[start].f20[7] = 0;
        o->list[start].f20[8] = 0;
        o->list[start].f20[9] = 0;
        o->list[start].f20[10] = 0;
        o->list[start].f20[11] = 0;
        o->list[start].f20[12] = 0;
        o->list[start].f20[13] = 0;
        o->list[start].f20[14] = 0;
        memset(o->list[start].f60, 0, 16);
        memset(o->list[start].f70, 0, 16);
        memset(o->list[start].f80, 0, 16);
        memset(o->list[start].f90, 0, 16);
        memset(o->list[start].fA0, 0, 16);
        memset(o->list[start].fB0, 0, 16);
    }
}
