/* rgp:protos */
#define RGP_SELF_DataTableCmdFormatText_4226b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* lane N4 family: DataTableCmdFormatText_4226b0 / DataTableCmdFormatText_4233b0 (168 B each).
   Substitutions: the 0x800/0x3E7 limit and the 0x9C/0xA0 vs 0xA4/0xA8 pair. */

typedef struct {
    u8 pad00[0x6C];
    u8 f6C[0x2C];
    char *f98;
    s32 f9C;
    s32 fA0;
} Obj;

extern Obj *D_004830F8;

/*rgp*/
/*rgp*/
extern s32 strlen(char *);
extern void Sprintf_1343b8(char *, char *, s32);
/*rgp*/

s32 DataTableCmdFormatText_4226b0(void *a0)
{
    char sp30[0x200] __attribute__((aligned(16)));
    s32 n;
    Obj *o;
    char *str;

    o = D_004830F8;
    str = ((char *)DataTableStoreString_368ab0(o, ((char *)SlotGetInt_15f720(a0))));
    if ((o->f98 = str) != 0) {
        if (strlen(str) > 0x1F0) {
            o->f98[0x1EF] = 0;
        }
        Sprintf_1343b8(sp30, o->f98, 0x800);
        n = strlen(sp30) + 1;
        o->f9C = ArenaStrDup_3701d0(&o->f6C, sp30, -1, 1, 1);
        o->fA0 = n;
    } else {
        o->f9C = 0;
        o->fA0 = 0;
    }
    return 1;
}
