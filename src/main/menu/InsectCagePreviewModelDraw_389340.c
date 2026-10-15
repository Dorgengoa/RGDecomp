#include "types.h"

extern void *D_004832F8;
extern f32 D_004832F0;
extern f32 D_004832F4;
extern void DrawModelPreview_28be80(void *, f32, f32);

void InsectCagePreviewModelDraw_389340(void)
{
    void *p;

    p = D_004832F8;
    if (p != 0) {
        DrawModelPreview_28be80(p, D_004832F0, D_004832F4);
    }
}
