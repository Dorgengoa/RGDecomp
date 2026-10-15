#include "types.h"

/* lane N4 family: DataTableCmdFormatText_4233b0 / DataTableCmdFormatText_4233b0 (168 B each).
   Substitutions: the 0x3E7/0x3E7 limit and the 0x9C/0xA0 vs 0xA4/0xA8 pair. */

typedef struct {
    u8 pad00[0x6C];
    u8 f6C[0x2C];
    char *f98;
    u8 pad9C[8];
    s32 fA4;
    s32 fA8;
} Obj;

extern Obj *D_004830F8;

extern char *SlotGetInt_15f720(void *);
extern char *DataTableStoreString_368ab0(Obj *, char *);
extern s32 strlen(char *);
extern void Sprintf_1343b8(char *, char *, s32);
extern s32 ArenaStrDup_3701d0(void *, char *, s32, s32, s32);

s32 DataTableCmdFormatText_4233b0(void *a0)
{
    char sp30[0x200];
    s32 n;
    Obj *o;
    char *str;

    o = D_004830F8;
    str = DataTableStoreString_368ab0(o, SlotGetInt_15f720(a0));
    if ((o->f98 = str) != 0) {
        if (strlen(str) > 0x1F0) {
            o->f98[0x1EF] = 0;
        }
        Sprintf_1343b8(sp30, o->f98, 0x3E7);
        n = strlen(sp30) + 1;
        o->fA4 = ArenaStrDup_3701d0(&o->f6C, sp30, -1, 1, 1);
        o->fA8 = n;
    } else {
        o->fA4 = 0;
        o->fA8 = 0;
    }
    return 1;
}
