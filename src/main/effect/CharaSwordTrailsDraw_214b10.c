#include "types.h"

extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern s32 GetDrawCtx_15de80(void);
extern void SwordTrailDraw_2d7230(void *, s32);

typedef struct { s16 u0; u8 pad2[0x8E]; s32 u90; u8 pad94[0x20]; s32 uB4; } E214b10;
typedef struct { u8 pad[0x584]; E214b10 *list; s32 n; } T214b10;

void CharaSwordTrailsDraw_214b10(T214b10 *arg0) {
    E214b10 *e;
    s32 i;

    e = arg0->list;
    if (e != NULL) {
        for (i = 0; i < arg0->n; i++, e++) {
            if (e->u0 != 0 && *(s32 *)((u8 *)e + 0x90) >= 0 && (u8)(!(e->uB4 != 0)) >= 0) {
                DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), e->u90, 1.0f);
                SwordTrailDraw_2d7230(e, e->uB4);
            }
        }
    }
}
