#include "types.h"

/* Resolve an entry and return a pointer to its payload, optionally handing
   back the payload's size. The size pointer is allowed to be null, and the
   +0x40 offset is read on BOTH paths -- retail puts one copy in the null
   check's `beql` delay slot, which is what makes the two-branch shape come
   out as five words rather than six. */

typedef struct Entry00181dd0 {
    u8 pad00[0x40];
    s32 offset;        /* +0x40 */
    u32 size;          /* +0x44 */
} Entry00181dd0;

extern Entry00181dd0 *ArchiveFindEntryByName_181e20(void *archive, void *name);

void *ArchiveGetFileData_181dd0(void *archive, void *name, u32 *size)
{
    Entry00181dd0 *e;

    e = ArchiveFindEntryByName_181e20(archive, name);
    if (e == 0) {
        return 0;
    }
    if (size != 0) {
        *size = e->size;
    }
    return (u8 *)e + e->offset;
}
