/* MATCH (s41m). Stale pre-match note follows -- PARK s16d: 3 round trips. Started 111 words/5 bad; fixed a wrong-global
   bug (2nd MemStackClear_14dff0 call used D_004BB890 instead of D_004BB8F0,
   matching m2c's original draft -- one of two similarly-named globals a
   few hundred bytes apart) which dropped it to 4 bad. The remaining 4 bad
   words are all in the final `D_00481B5C = D_00481B58 + 0xFFF1F000;`
   register choice: retail loads D_00481B58 into $v1 and the 32-bit
   constant into $at (lui/ori), mine loads the global into $a0 and the
   constant into $v1 -- same computation, different colouring. Neither
   swapping operand order nor introducing a named temp for the load
   changed it. */
#include "types.h"

extern void DepthProbeSlotsReset_13fcb0(s32);
extern void DrawEnvSetVsyncInterval_144140(s32, s32, s32);
extern void MemStackInit_14d810(void *, s32, s32);
extern void MemStackReset_14d830(void *);
extern s32 MemStackAllocQw_14d950(void *, s32);
extern s32 MemStackAllocAligned64_14da10(void *, s32);
extern void MemStackHeapReinit_14de90(void *);
extern void MemStackHeapInit_14dee0(void *, s32, s32);
extern void MemStackClear_14dff0(void *);
extern s32 DrawBufPairInitMaybe_15dc50(void *, s32, void *, s32, s32);
extern s32 GetDrawCtx_15de80(void);
extern void *GetMainStack_1c6dc0(void);
extern void ReadBuffHeapInit_202290(void *);
extern void DrawCtxNameTableSetupMaybe_202560(s32);
extern s32 GetSystemMemStack_202600(void);
extern s8 *strcpy(s8 *, s8 *);
extern u32 strlen(s8 *);
extern s8 D_0045C150[];
extern s8 D_0045C158[];
extern u8 *D_00481B58;
extern u8 *D_00481B5C;
extern s32 D_00481B60;
extern s32 D_00481B64;
extern u8 D_004BB830[];
extern u8 D_004BB890[];
extern u8 D_004BB8F0[];

void SystemHeapsInit_2020d0(void)
{
    void *t2;
    s32 t16;

    t2 = GetMainStack_1c6dc0();
    MemStackReset_14d830(t2);
    MemStackClear_14dff0(D_004BB830);
    MemStackClear_14dff0(D_004BB8F0);
    D_00481B58 = 0;
    D_00481B5C = 0;
    D_00481B60 = 0;
    D_00481B64 = 0;
    t16 = GetDrawCtx_15de80();
    DrawBufPairInitMaybe_15dc50(t2, 0x2134, t2, 0, 0xF03C);
    MemStackHeapInit_14dee0((u8 *)t16 + 0xD0, MemStackAllocQw_14d950(t2, 0x3A98), 0x3A98);
    DrawEnvSetVsyncInterval_144140(t16, 2, 0);
    DepthProbeSlotsReset_13fcb0(t16);
    MemStackClear_14dff0(D_004BB830);
    MemStackInit_14d810(D_004BB830, MemStackAllocAligned64_14da10(t2, 0x2A700), 0x2A700);
    if (strlen(D_0045C150) < 0x10U) {
        strcpy((s8 *)D_004BB830, D_0045C150);
    }
    MemStackReset_14d830(D_004BB830);
    MemStackAllocQw_14d950(D_004BB830, 0x800);
    DrawCtxNameTableSetupMaybe_202560(GetSystemMemStack_202600());
    MemStackClear_14dff0(D_004BB890);
    MemStackHeapInit_14dee0(D_004BB890, MemStackAllocAligned64_14da10(t2, 0x2300), 0x2300);
    if (strlen(D_0045C158) < 0x10U) {
        strcpy((s8 *)D_004BB890, D_0045C158);
    }
    MemStackHeapReinit_14de90(D_004BB890);
    ReadBuffHeapInit_202290(t2);
    D_00481B5C = D_00481B58 - 0xE1000;
}
