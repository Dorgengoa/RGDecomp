/* PARK 1/3: RIGHT LENGTH (115w), 18 bad. */
#include "types.h"

typedef struct Obj1808 {
    u8 pad1808[0x1808];
    s32 unk1808;
    s32 unk180C;
} Obj1808;

s32 DrawEnvGetHeight_1451d0(s32);
s32 DrawEnvGetWidth_1451e0(s32);
s32 MemStackAllocAligned64_14da10(s32, s32);
s32 NameTableAddEntry_159b70(s32, s32, void *, s32, s32, s32, s32, s32, s64, s64);
s32 GetDrawCtxNameTable_15de40(void);
s32 GetDrawCtx_15de80(void);
void ScreenFadeSetCaptureObj_1cf650(void *, s32, s32);
void GameSceneSoundSlot6InitBuf_1d06f0(void *, void *, s32, s32);
void GameSceneSoundSlot5InitBuf_1d0700(void *, void *, s32, s32);
void GameSceneSoundSlot4InitBuf_1d0710(void *, void *, s32, s32);
void GameSceneSoundSlot3InitBuf_1d0720(void *, void *, s32, s32);
void GameSceneSoundSlot2InitBuf_1d0730(void *, void *, s32, s32);
void GameSceneSoundSlot1InitBuf_1d0740(void *, void *, s32, s32);
void GameSceneSoundSlot0InitBuf_1d0750(void *, void *, s32, s32);
void GameSceneSoundNoteListAlloc_1d1480(void *, s32);
Obj1808 *GetCurrentScene_1f5be0(void);
s32 GetReadBuffHeap_2025e0(void);
s32 GetSceneWorkHeap_2025f0(void);
extern u8 D_0045C178[];
extern u8 D_0045C180[];
extern u8 D_0045C190[];
extern u8 D_0045C1A0[];
extern u8 D_0045C1B0[];
extern u8 D_0045C1B8[];
extern u8 D_0045C1C0[];
extern u8 D_0045C1C8[];
extern s32 D_00481B64;

void GameSceneBufsInitMaybe_202390(s32 arg0) {
    Obj1808 *temp_2;
    s32 temp_2_2;
    s32 temp_17;
    s32 temp_16_2;
    s32 temp_16;

    temp_16 = GetDrawCtx_15de80();
    temp_2 = GetCurrentScene_1f5be0();
    if (temp_2 != NULL) {
        temp_2->unk1808 = GetReadBuffHeap_2025e0();
        temp_2->unk180C = GetSceneWorkHeap_2025f0();
        if (arg0 != 0) {
            GameSceneSoundSlot0InitBuf_1d0750(temp_2, D_0045C178, MemStackAllocAligned64_14da10(arg0, 0x200), 0x200);
            GameSceneSoundSlot1InitBuf_1d0740(temp_2, D_0045C180, MemStackAllocAligned64_14da10(arg0, 0x200), 0x200);
            GameSceneSoundSlot2InitBuf_1d0730(temp_2, D_0045C190, MemStackAllocAligned64_14da10(arg0, 0x14), 0x14);
            GameSceneSoundSlot3InitBuf_1d0720(temp_2, D_0045C1A0, MemStackAllocAligned64_14da10(arg0, 0x14), 0x14);
            GameSceneSoundSlot4InitBuf_1d0710(temp_2, D_0045C1B0, MemStackAllocAligned64_14da10(arg0, 0x10), 0x10);
            GameSceneSoundSlot5InitBuf_1d0700(temp_2, D_0045C1B8, MemStackAllocAligned64_14da10(arg0, 0xE00), 0xE00);
            GameSceneSoundSlot6InitBuf_1d06f0(temp_2, D_0045C1C0, MemStackAllocAligned64_14da10(arg0, 0xC00), 0xC00);
            GameSceneSoundNoteListAlloc_1d1480(temp_2, arg0);
        }
        temp_17 = GetDrawCtxNameTable_15de40();
        temp_16_2 = DrawEnvGetWidth_1451e0(temp_16);
        temp_2_2 = NameTableAddEntry_159b70(temp_17, 0x322, D_0045C1C8, 0, temp_16_2, DrawEnvGetHeight_1451d0(temp_16), 0x20, 0, 0, 0);
        D_00481B64 = temp_2_2;
        ScreenFadeSetCaptureObj_1cf650(temp_2, temp_2_2, 0);
    }
}
