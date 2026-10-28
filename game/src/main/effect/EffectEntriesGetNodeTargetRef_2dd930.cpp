#include "types.h"

/* Same array-scan idiom as EffectEntriesSetId_2ddf00 / EffectEntriesSetAutoRelease_2de500 (0x30 entries, stride
   0xE0, match on unkE == arg1->unk8, then hand the match to EffectEntryFindNodeById_2da140).
   Difference here: only the FIRST match is processed, and its result feeds a
   virtual call (`lw t9 / lw t9 / jalr t9`) instead of a plain field write --
   the vtable pointer sits at +0x190 of the object EffectEntryFindNodeById_2da140 returns, and
   the used slot is +0x34, i.e. virtual index (0x34-8)/4 = 11 (see
   include/worldobj_cpp.h and include/camera_cpp.h for the same recipe: pad
   up to the vptr's real offset, then declare every slot up to the one used). */

typedef struct ElemFUN_002dd930 {
    u8 pad0[0xE];
    s16 unkE;
} ElemFUN_002dd930;

typedef struct Arg1FUN_002dd930 {
    u8 pad0[0x8];
    s32 unk8;
} Arg1FUN_002dd930;

class ObjFUN_002da140 {
    u8 pad000[0x190];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    s32 slot034() { return VCM0(s32, 0x34); }
};

extern "C" ObjFUN_002da140 *EffectEntryFindNodeById_2da140(ElemFUN_002dd930 *arg0, Arg1FUN_002dd930 *arg1);

extern "C" s32 EffectEntriesGetNodeTargetRef_2dd930(ElemFUN_002dd930 *arg0, Arg1FUN_002dd930 *arg1)
{
    s32 i;
    ElemFUN_002dd930 *elem;
    ObjFUN_002da140 *obj;

    for (i = 0; i < 0x30; i++) {
        elem = (ElemFUN_002dd930 *)((u8 *)arg0 + i * 0xE0);
        if (elem->unkE == arg1->unk8) {
            obj = EffectEntryFindNodeById_2da140(elem, arg1);
            if (obj != NULL) {
                return obj->slot034();
            }
            goto ret0;
        }
    }
ret0:
    return 0;
}
