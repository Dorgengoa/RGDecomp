#include "types.h"

typedef struct {
    u8 padC0[0xC0];
    s32 unkC0;
    u8 *unkC4;
    u16 unkC8;
    s16 unkCA;
} S001df030;

extern void MapObjRelease_1e0a90(void *a);
extern s32 MapDataUnload_1e6690(void);
extern void MapDataIsGenericTransporter_1e7a80(S001df030 *a);

s32 MapBlockRelease_1df030(S001df030 *arg0) {
    s32 v;
    s32 i;

    v = MapDataUnload_1e6690() & 0xFF;
    if (v != 0) {
        MapDataIsGenericTransporter_1e7a80(arg0);
        if (arg0->unkC4 != 0) {
            for (i = 0; i < arg0->unkCA; i++) {
                MapObjRelease_1e0a90(arg0->unkC4 + (i * 0x18));
            }
        }
        arg0->unkC0 = 0;
        arg0->unkC4 = 0;
        arg0->unkC8 = 0;
        arg0->unkCA = 0;
    }
    return v;
}
