#include "types.h"
#pragma opt_propagation off
typedef struct Arena0014e230 {
    u8 pad00[0x20];
    s32 unk20;
    u8 pad24[0x4];
    u32 unk28;
    s32 unk2C;
    u8 pad30[0x4];
    s32 unk34;
} Arena0014e230;

static inline void *alloc_(Arena0014e230 *arena, s32 units, u32 base)
{
    s32 offset;
    s32 newOffset;

    if (arena->unk20 != 0) {
        return NULL;
    }
    if (units <= 0) {
        return NULL;
    }
    offset = arena->unk2C;
    newOffset = offset + units;
    if (arena->unk34 < newOffset) {
        return NULL;
    }
    arena->unk2C = newOffset;
    return (void *)(base + offset * 16);
}

void *MemStackNew_14e230(u32 size, Arena0014e230 *arena)
{
    s32 units;
    u32 base;
    s32 ok;
    void *r;

    if (size & 0xF) {
        units = (size >> 4) + 1;
    } else {
        units = size >> 4;
    }
    base = arena->unk28;
    ok = base != 0;
    if (ok) {
        r = alloc_(arena, units, base);
        goto out;
    }
    return NULL;
out:
    return r;
}
