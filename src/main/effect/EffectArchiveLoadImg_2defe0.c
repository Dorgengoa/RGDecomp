#include "types.h"

/* Build two ".ext"-suffixed lookup names from a name/desc pair, resolve each
   through the archive (ArchiveGetFileByPath_1c2800), and hand both results plus the
   caller's five leading args and a quality value to EffectEntryLoadImg_2df110. On a
   missing archive/name/desc, fill the caller's result struct with a fixed
   error code instead.

   ⚠ The error path's last field (unkC) is read from an uninitialized local
   -- retail never assigns it on this path either, so the load is hoisted by
   the compiler to right after the prologue (long before the field it stands
   in for would ever be computed). Reproduced here with a genuinely
   uninitialized local so the same dead read shows up. */

typedef struct Result002defe0 {
    s16 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Result002defe0;

extern char D_00461768[];
extern char D_00461770[];

extern void *ArchiveGetFileByPath_1c2800(void *archive, void *name, u32 *size);
extern void EffectEntryLoadImg_2df110(Result002defe0 *out, s32 a1, s32 a2, s32 a3, s32 a4,
                          s32 a5, void *namePtr, u32 nameSize, void *descPtr,
                          s64 descSize, s64 quality);

void EffectArchiveLoadImg_2defe0(Result002defe0 *out, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5,
                   void *archive, char *name, char *desc, s32 quality)
{
    char nameBuf[0x38];
    char descBuf[0x20];
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
    strcat(nameBuf, D_00461768);
    strcpy(descBuf, desc);
    strcat(descBuf, D_00461770);
    namePtr = ArchiveGetFileByPath_1c2800(archive, nameBuf, (u32 *) &nameSize);
    descPtr = ArchiveGetFileByPath_1c2800(archive, descBuf, (u32 *) &descSize);
    EffectEntryLoadImg_2df110(out, a1, a2, a3, a4, a5, namePtr, nameSize, descPtr,
                 (s64) descSize, (s64) quality);
}
