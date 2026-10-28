/* rgp:protos */
#define RGP_SELF_MemStackHeapAlloc_14db10 1
#include "port/game_protos.h"
#line 1
/* PARKED at triage (0 round trips): another memory-allocator-shaped
 * function (same family as MemStackHeapAllocFrontAligned_14dde0) with m2c's `var_2->unk-4` negative-
 * offset syntax and multiple unresolved "?" pointer types on a doubly-linked
 * freelist. Would need the same careful raw-asm reconstruction that closed
 * MemStackHeapAllocFrontAligned_14dde0's *shape* (which still didn't match retail) -- not worth the
 * time budget here. Deferred. See asm/matchings/main/MemStackHeapAlloc_14db10.s. */
/* s49m: MATCH */
#pragma divbyzerocheck on
#include "types.h"

typedef struct Block {
    struct Block *next;
    struct Block *prev;
    s32 size;
    s32 size2;
} Block;

typedef struct Heap {
    u8 pad0[0x18];
    Block *first;
    u8 pad1C[0xC];
    u8 *last;
    u8 pad2C[8];
    s32 free;
    Block *cur;
} Heap;

u8 *MemStackHeapAlloc_14db10(Heap *heap, s32 mode, s32 x, s32 size)
{
    Block *b;
    Block *best;
    Block *bestPrev;
    u32 bestGap;
    s32 n;
    u32 units;
    u32 gap;
    Block *end;
    Block *next;
    u8 *data;
    u32 rem;
    u32 need;

    units = size / 16;
    need = x + units;
    heap->cur = 0;
    b = heap->first;
    if (b == 0) {
        return 0;
    }
    best = 0;
    bestPrev = 0;
    bestGap = 0;
    while ((next = b->next) != 0) {
        end = (Block *)((u8 *)b + b->size * 16);
        gap = ((u8 *)next - (u8 *)end) / 16;
        if (mode == 1 && gap > 1) {
            best = end;
            bestPrev = b;
            break;
        }
        if (mode == 2 && bestGap < gap) {
            best = end;
            bestPrev = b;
            bestGap = gap;
        }
        if (mode == 3 && need < gap) {
            best = end;
            bestPrev = b;
            break;
        }
        b = next;
    }
    if (best != 0) {
        heap->cur = best;
        best->next = bestPrev->next;
        bestPrev->next = heap->cur;
        heap->cur->prev = bestPrev;
        heap->cur->next->prev = heap->cur;
        data = (u8 *)heap->cur + 0x10;
        rem = ((u32)data >> 4) % units;
        if (rem != 0) {
            data += (units - rem) << 4;
        }
        n = (data - (u8 *)heap->cur) / 16;
        heap->cur->size2 = n;
        *(s32 *)(data - 4) = n;
        heap->cur->size = (data - (u8 *)heap->cur) / 16;
        heap->last = data;
        heap->free = ((u8 *)heap->cur->next - data) / 16;
        return data;
    }
    return 0;
}
