#include "types.h"
#pragma opt_common_subs off

extern void SoundSetEntryVolumeScaled_1b9820(s32, s32, s32, f32);
extern s32 SoundIdGetIndex_1bbf20(s32);

typedef struct { s32 id; s32 pad4; volatile s16 unk8; s16 padA; f32 scale; s32 pad10; } E1b4ab0;
typedef struct { s32 n; E1b4ab0 *e; f32 f; } T1b4ab0;

void SoundNoteListSetVolumeScale_1b4ab0(T1b4ab0 *arg0, f32 f) {
    s32 i;
    E1b4ab0 *e;
    s32 r;
    f32 s;
    f32 t;
    s32 id;

    arg0->f = f;
    if (arg0->e != NULL) {
        for (i = 0; i < arg0->n; i++) {
            e = &arg0->e[i];
            id = e->id;
            if (id < 0) continue;
            r = SoundIdGetIndex_1bbf20(id);
            t = e->scale;
            if (t >= 0.0f) {
                s = t * arg0->f;
            } else {
                s = arg0->f;
            }
            SoundSetEntryVolumeScaled_1b9820(e->id, r, e->unk8, s);
        }
    }
}
