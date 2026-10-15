#include "types.h"

/* arity read off the SETUP: $4 is overwritten by the %hi/%lo of
   D_004DCAB0 before any use, but $5 is kept in $16, so param 1 exists and
   is unused.  `ori $6,$0,0xC000` is the positive constant 0xC000. */

extern u8 D_004DCAB0[];
extern u8 D_004DCB10[];
extern u8 D_004DCC70[];
extern u8 D_004DCCC0[];
extern char D_004615B8[];
extern char D_004615C8[];

extern void MemStackClear_14dff0(void *);
extern void EventObjMgrReset_2ea280(void *);
extern void NavMgrReset_30da70(void *);
extern void UskMemoryInit_42e070(void *);
extern void MemStackAlign64_14d8e0(void *);
extern void *MemStackAllocAligned64_14da10(void *, s32);
extern void MemStackHeapInit_14dee0(void *, void *, s32);
extern u32 strlen(char *);
extern char *strcpy(char *, char *);
extern void MemStackHeapReinit_14de90(void *);
extern void EventObjMgrSetHeap_2ea1d0(void *, void *);
extern void UskMemorySetStackName_42e020(void *, char *);
extern void UskMemorySetBuffer_42df30(void *, void *, s32);
extern void NavMgrInit_30d360(void *, s32, void *);
extern void EventObjMgrInitLists_2ea1e0(void *);
extern void NavMgrFreeAllGraphs_30d9b0(void *);
extern void MonographDrawHoldSetFrames_2d1940(s32);

void EventObjDataInit_2d12d0(s32 unused, void *heap)
{
    MemStackClear_14dff0(D_004DCAB0);
    EventObjMgrReset_2ea280(D_004DCB10);
    NavMgrReset_30da70(D_004DCCC0);
    UskMemoryInit_42e070(D_004DCC70);
    if (heap != 0) {
        MemStackAlign64_14d8e0(heap);
        MemStackHeapInit_14dee0(D_004DCAB0, MemStackAllocAligned64_14da10(heap, 0x2800), 0x2800);
        if (strlen(D_004615B8) < 0x10U) {
            strcpy((char *)D_004DCAB0, D_004615B8);
        }
        MemStackHeapReinit_14de90(D_004DCAB0);
        MemStackAlign64_14d8e0(D_004DCAB0);
        EventObjMgrSetHeap_2ea1d0(D_004DCB10, D_004DCAB0);
        UskMemorySetStackName_42e020(D_004DCC70, D_004615C8);
        UskMemorySetBuffer_42df30(D_004DCC70, MemStackAllocAligned64_14da10(heap, 0xC00), 0xC000);
        NavMgrInit_30d360(D_004DCCC0, 4, D_004DCC70);
        EventObjMgrInitLists_2ea1e0(D_004DCB10);
        NavMgrFreeAllGraphs_30d9b0(D_004DCCC0);
        MonographDrawHoldSetFrames_2d1940(0);
    }
}
