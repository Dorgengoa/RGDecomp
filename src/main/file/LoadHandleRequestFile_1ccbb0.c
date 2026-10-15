#include "types.h"

extern void LoadHandleReset_1ccc10(void *);
extern s32 GetLoaderMgr_1f59d0(void);
extern s32 LoaderRequestFile_1cd870(s32, s32, s32);

struct Obj0 {
    s16 m00;
};

s16 LoadHandleRequestFile_1ccbb0(struct Obj0 *p0, s32 p1)
{
    s32 r1;
    s32 r2;

    LoadHandleReset_1ccc10(p0);
    r1 = GetLoaderMgr_1f59d0();
    r2 = LoaderRequestFile_1cd870(r1, p1, 0);
    p0->m00 = r2;
    return r2;
}
