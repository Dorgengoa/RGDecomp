/* rgp:protos */
#define RGP_SELF_EffectArchiveLoadChr_2df690 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clone of EffectArchiveLoadImg_2defe0 (same normalized opcode stream) -- see that file's
   header for the residue note on the uninitialized unkC read (here it's the
   tail of nameBuf, a buffer bigger than what strcpy/strcat ever fill). This
   one suffixes with D_00461798 instead of D_00461768 and dispatches to
   EffectEntryLoadChr_2df7c0 instead of EffectEntryLoadImg_2df110. */

typedef struct Result002df690 {
    s16 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Result002df690;

extern char D_00461798[];
extern char D_00461770[];

/*rgp*/
/*rgp*/



void EffectArchiveLoadChr_2df690(Result002df690 *out, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5,
                   void *archive, char *name, char *desc, s32 quality)
{
    char nameBuf[0x38] __attribute__((aligned(16)));
    char descBuf[0x20] __attribute__((aligned(16)));
    s32 nameSize;
    s32 descSize;
    void *namePtr;
    void *descPtr;
    s32 unused;

    unused = *(volatile s32 *) &nameBuf[0x2C];
    if (archive != 0 && name != 0 && desc != 0) {
        goto success;
    }
    out->unk0 = 2;
    out->unk4 = -1;
    out->unk8 = 0;
    out->unkC = unused;
    return;

success:
    strcpy(nameBuf, name);
    strcat(nameBuf, D_00461798);
    strcpy(descBuf, desc);
    strcat(descBuf, D_00461770);
    namePtr = ArchiveGetFileByPath_1c2800(archive, nameBuf, (u32 *) &nameSize);
    descPtr = ArchiveGetFileByPath_1c2800(archive, descBuf, (u32 *) &descSize);
    EffectEntryLoadChr_2df7c0(out, a1, a2, a3, a4, a5, namePtr, nameSize, descPtr, (void *)((s64) descSize), (int)((s64) quality)
);
}
