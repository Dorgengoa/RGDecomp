#include "types.h"

extern s32 EntryListGetCurIndex_3238b0(void *);
extern void EntryGetRange_323af0(void *, void *, void *);
extern void EntryListSelectByIndex_323540(void *, s32);
extern void *memcpy(void *, void *, s32);

void MinimapCrossfadeUpdate_32a950(void * arg0)
{
    u8 *base;
    s32 sp2C;
    s32 sp28;
    f32 temp_f1_3;

    base = (u8 *)arg0;
    if (*(void **)(base + 0x170) == NULL || *(void **)(base + 0x174) == NULL) {
        return;
    }
    {
        if (*(f32 *)(base + 0xE8)) {
            *(f32 *)(base + 0xE4) = (f32) (*(f32 *)(base + 0xE4) + *(f32 *)(base + 0xE8));
            if (!(*(f32 *)(base + 0xE8) <= 0.0f) && !(*(f32 *)(base + 0xE4) < 1.0f)) {
                *(f32 *)(base + 0xE4) = 1.0f;
                *(f32 *)(base + 0xE8) = 0.0f;
            }
            if ((*(f32 *)(base + 0xE8) < 0.0f) && (*(f32 *)(base + 0xE4) <= 0.0f)) {
                *(f32 *)(base + 0xE4) = 0.0f;
                *(f32 *)(base + 0xE8) = 0.0f;
            }
        }
        if (*(f32 *)(base + 0xE0)) {
            *(f32 *)(base + 0xDC) = (f32) (*(f32 *)(base + 0xDC) + *(f32 *)(base + 0xE0));
            if (!(*(f32 *)(base + 0xE0) <= 0.0f) && !(*(f32 *)(base + 0xDC) < 1.0f)) {
                *(f32 *)(base + 0xDC) = 1.0f;
                *(f32 *)(base + 0xE0) = 0.0f;
            }
            if ((*(f32 *)(base + 0xE0) < 0.0f) && (*(f32 *)(base + 0xDC) <= 0.0f)) {
                *(f32 *)(base + 0xDC) = 0.0f;
                *(f32 *)(base + 0xE0) = 0.0f;
            }
        }
        if ((*(f32 *)(base + 0xDC) <= 0.0f) && !(*(f32 *)(base + 0xE4) < 1.0f)) {
            *(void **)(base + 0x170) = *(void **)(base + 0x174);
            *(void **)(base + 0x174) = NULL;
            temp_f1_3 = *(f32 *)(base + 0xDC);
            *(f32 *)(base + 0xDC) = *(f32 *)(base + 0xE4);
            *(f32 *)(base + 0xE4) = temp_f1_3;
            if (EntryListGetCurIndex_3238b0(base + 0x12C) == -1) {
                EntryGetRange_323af0(*(void **)(base + 0x170), &sp2C, &sp28);
                EntryListSelectByIndex_323540(base + 0x12C, *(s32 *)(*(u8 **)(base + 0x170) + 0x2C));
            }
            memcpy(base, base + 0x10, 0x10);
            memcpy(base + 0x20, base, 0x10);
        }
    }
}
