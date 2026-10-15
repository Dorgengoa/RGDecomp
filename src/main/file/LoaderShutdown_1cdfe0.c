#include "types.h"

typedef struct Obj_FUN_001cdfe0 Obj_FUN_001cdfe0;

extern void LoaderPurgeAll_1cd240(Obj_FUN_001cdfe0 *o);
extern void LoaderTick_1ccc30(Obj_FUN_001cdfe0 *o);
extern s32 LoaderCountQueued_1cd620(Obj_FUN_001cdfe0 *o);
extern void LoaderClear_1ce040(Obj_FUN_001cdfe0 *o);
extern void FileReqCancelAll_182510(void);

void LoaderShutdown_1cdfe0(Obj_FUN_001cdfe0 *o)
{
    LoaderPurgeAll_1cd240(o);
    while (LoaderCountQueued_1cd620(o) > 0) {
        LoaderTick_1ccc30(o);
    }
    LoaderClear_1ce040(o);
    FileReqCancelAll_182510();
}
