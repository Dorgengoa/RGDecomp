#include "types.h"

/* Two lookups in series, each with its own `return 0`. The argument is an id,
   not a pointer -- `EvCmdEventPlayerCreate_261220.cpp` calls this as
   MesMgrGetSlotWin_266af0(6) -- and it is held in $16 because the first lookup's result
   takes $4 for the second. */

typedef struct Rec00266af0 {
    s32 unk0;
    s32 unk4;
} Rec00266af0;

extern void *GetMesMgr_277e90(s32 id);
extern Rec00266af0 *MesMgrGetSlot_277a20(void *found, s32 id);

s32 MesMgrGetSlotWin_266af0(s32 id)
{
    void *a;
    Rec00266af0 *b;

    a = GetMesMgr_277e90(id);
    if (a == 0) {
        return 0;
    }
    b = MesMgrGetSlot_277a20(a, id);
    if (b == 0) {
        return 0;
    }
    return b->unk4;
}
