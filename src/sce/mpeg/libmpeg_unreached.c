/* SPDX-License-Identifier: CC0-1.0 */
/* libmpeg entry points the game's own movie layer still names, bound so the
 * game links (docs/BINDINGS.md, docs/MOVIE.md "Override list").
 *
 * The port's movie service replaces the IPU/libmpeg decoder: MovieOpen,
 * MoviePlayerStart, MovieFrameQueueSendNext, MoviePlayerWaitTick and
 * MoviePlayerShutdown are overridden, so VideoDecCreate_1d5470,
 * VideoDecSetStream_1d5430, VideoDecDecodeBs_1d29e0 and MovieReadThread_1d4f50
 * are compiled but never run (no thread is created for them).  Those four are
 * the only callers of the functions below.  If one is reached anyway, it says
 * so once on stderr and returns the value that ends the caller's work:
 * MpegIsEnd -> 1 (end of stream), MpegDemuxPssRing -> 0 bytes consumed,
 * MpegGetPicture -> -1 (error), the setup calls -> 0 (no handle).
 * MpegStopDmaMaybe_111050 is not here: its only caller was MovieOpen_1d5cf0,
 * whose override drops the call. */
#include <stdint.h>
#include <stdio.h>

static void reached_once(int *seen, const char *name)
{
    if (!*seen) {
        *seen = 1;
        fprintf(stderr, "libmpeg: %s reached, but the movie service replaces libmpeg "
                        "(docs/MOVIE.md); ignored\n", name);
    }
}

#define reached(name) do { static int seen_; reached_once(&seen_, name); } while (0)

int32_t MpegCreate_1104a8(void *mp, int32_t work, int32_t work_size)
{
    (void)mp; (void)work; (void)work_size;
    reached("MpegCreate_1104a8");
    return 0;
}

int32_t MpegAddCallback_1112c0(void *mp, int32_t type, void *fn, int32_t data)
{
    (void)mp; (void)type; (void)fn; (void)data;
    reached("MpegAddCallback_1112c0");
    return 0;
}

int32_t MpegAddStrCallback_115740(int32_t mp, int32_t stream, int32_t id, int32_t fn, int32_t data)
{
    (void)mp; (void)stream; (void)id; (void)fn; (void)data;
    reached("MpegAddStrCallback_115740");
    return 0;
}

int32_t MpegDemuxPssRing_115340(void *mp, int32_t buf, int32_t size, void *ring, int32_t ring_size)
{
    (void)mp; (void)buf; (void)size; (void)ring; (void)ring_size;
    reached("MpegDemuxPssRing_115340");
    return 0;
}

int32_t MpegGetPicture_111148(void *mp, int32_t rgb32, int32_t mbcount)
{
    (void)mp; (void)rgb32; (void)mbcount;
    reached("MpegGetPicture_111148");
    return -1;
}

int32_t MpegReset_1111e8(void *mp)
{
    (void)mp;
    reached("MpegReset_1111e8");
    return 0;
}

int32_t MpegIsEnd_111268(void *mp)
{
    (void)mp;
    reached("MpegIsEnd_111268");
    return 1;
}
