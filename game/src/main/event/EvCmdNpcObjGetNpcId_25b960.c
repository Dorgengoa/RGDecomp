/* rgp:protos */
#define RGP_SELF_EvCmdNpcObjGetNpcId_25b960 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARKED (round 1): length 0x5C vs retail 0x60. Struct field width/offset at
   0xC6 or the vtable-arg shape is likely off by a word. */
#include "types.h"

typedef struct Obj {
    u8  pad0[0xC6];
    s16 fC6;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdNpcObjGetNpcId_25b960(s64 *arg0)
{
    void *temp_16;
    Obj *temp_2;

    temp_16 = GetNpcObjTable_312860();
    temp_2 = ((Obj *)NpcObjFindById_2fb420(temp_16, ScriptGetInt_26a2a0((s32)arg0++)));
    if (temp_2 != NULL) {
        ScriptSetRefInt_26a1e0((s32)arg0, temp_2->fC6);
    }
    return 1;
}
