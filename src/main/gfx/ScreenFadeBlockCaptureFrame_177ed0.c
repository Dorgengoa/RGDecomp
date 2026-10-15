#include "types.h"

typedef struct {
    u8 pad0[0x50];
    s32 unk50;
} Obj00177ED0;

typedef struct {
    u8 pad0[0x2C];
    Obj00177ED0 *unk2C;
} ArgObj00177ED0;

typedef struct {
    s32 unk0[0x1C];
} Buf00177ED0;

void GsDownloadImage_140f20(s32, Buf00177ED0 *, s32);
void DrawEnvGetFrameTexDesc_144cc0(s32, Buf00177ED0 *);
void NameTableNodeCtor_15ae50(Buf00177ED0 *);
s32 GetDrawCtx_15de80();

void ScreenFadeBlockCaptureFrame_177ed0(ArgObj00177ED0 *arg0) {
    Buf00177ED0 sp30;
    s32 t;

    if (arg0->unk2C == NULL || arg0->unk2C->unk50 == 0) {
        return;
    }
    NameTableNodeCtor_15ae50(&sp30);
    t = GetDrawCtx_15de80();
    DrawEnvGetFrameTexDesc_144cc0(t, &sp30);
    GsDownloadImage_140f20(t, &sp30, arg0->unk2C->unk50);
}
