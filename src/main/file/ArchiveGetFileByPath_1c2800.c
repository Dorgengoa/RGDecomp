#include "types.h"

/* Resolve a name into a 0x100-byte local, then hand the local to the reader.
   The prototype comes from the caller already in the tree: EvCmdEventStartMaybe_248450
   declares ArchiveGetFileByPath_1c2800(archive, name, size). PathLocalize_1c28c0 returns a bool --
   retail masks its result with `andi 0xFF`, the recorded u8 idiom -- and the
   failure path is its own `return 0`. */

extern u8 PathLocalize_1c28c0(void *entry, void *name);
extern void *ArchiveGetFileData_181dd0(void *archive, void *entry, u32 *size);

void *ArchiveGetFileByPath_1c2800(void *archive, void *name, u32 *size)
{
    u8 entry[0x100];

    if (PathLocalize_1c28c0(entry, name) == 0) {
        return 0;
    }
    return ArchiveGetFileData_181dd0(archive, entry, size);
}
