#include "types.h"
typedef struct { u8 pad[0xB0]; u8 *vp; } Obj;
extern u8 D_00471D00[];
extern u8 D_00471AA0[];
extern void OperatorDelete_100840(void *p);
void *NodeRefObjDtor_2166a0(Obj *obj, s16 n)
{
    if (obj != 0) {
        obj->vp = D_00471D00;
        if (obj != 0) {
            obj->vp = D_00471AA0;
        }
        if (n > 0) {
            OperatorDelete_100840(obj);
        }
    }
    return obj;
}
/* MEASURED (this unit): two stores to the SAME *(T *)((u8 *)p + K) address
   make mwcc CSE the address into `addiu $3,$16,0xB0` (one word long).  A
   struct MEMBER store keeps the offset folded into both `sw`s.
   INERT here: member type u8* vs s32, and `s16 n` vs `s32 n` + `(s16)n`
   (all three struct arms produced object sha1 83c0af55). */
