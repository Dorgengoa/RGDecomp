/* SPDX-License-Identifier: CC0-1.0 */
/* The exe / window icon, made from the player's own data/ (docs/ICON.md).
 *
 * The public build carries no game art (docs/RELEASE.md leak gate), so the icon is never
 * compiled in: it is cut from a texture of the extracted disc at run time (window /
 * taskbar), by Setup.exe after the fill (the exe file icon of the player's rg-game.exe), and
 * by `rg-icon embed` for maintainer / play-test copies.  One implementation for all three,
 * so the window icon and the exe file icon are the same pixels.
 *
 *   source   RG_ICON_DEFAULT = RG_ICON_LOGO (L_mark02 of menu\l_mark02_en.img); RG_ICON_JASTER: b_m_face of menu\rc\menu_static_img2_en.pac (the
 *            battle-menu portrait, PSMT8 256x128, cell 6..50 x 0..48, own alpha);
 *            RG_ICON_SHIP: the ship of chara\dc3title.img (CT24 512x448, 4:3 display);
 *            galaxy (memory-card icon texture), logo, birthmark, seal, globe, crest:
 *            the k_sources table in rg_icon.cpp.
 *   images   256, 64, 48, 32, 24, 16 px, 32-bit BGRA + AND mask (BMP icon images, the
 *            RT_ICON payload as is); resampled in premultiplied alpha (box; growing = pixel repeat + box), deterministic
 *            (integer arithmetic only), so two runs give the same bytes.
 *
 * Pure C++ with a C API; Windows-only parts (embed, window, exe check) are no-ops elsewhere.
 */
#ifndef RG_ICON_H
#define RG_ICON_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* sources (rg_icon.cpp k_sources: member, picture, cut); the default was RG_ICON_JASTER
 * until the USER picked: RG_ICON_DEFAULT below (docs/ICON.md "Candidates 2") */
enum { RG_ICON_JASTER = 0, RG_ICON_SHIP, RG_ICON_GALAXY, RG_ICON_LOGO, RG_ICON_BIRTHMARK, RG_ICON_SEAL,
       RG_ICON_GLOBE, RG_ICON_CREST, RG_ICON_SOURCES };
/* the icon of the game (USER pick 2026-11-10: the logo with the galaxy) */
#define RG_ICON_DEFAULT RG_ICON_LOGO
#define RG_ICON_IMAGES 6
extern const int rg_icon_sizes[RG_ICON_IMAGES];   /* 256, 64, 48, 32, 24, 16 */

typedef struct rg_icon_set {
    int n;                              /* images (RG_ICON_IMAGES when built) */
    int size[RG_ICON_IMAGES];
    uint8_t *rgba[RG_ICON_IMAGES];      /* size x size x 4, straight alpha, top row first */
} rg_icon_set;

/* source name ("jaster", "ship") -> RG_ICON_*, -1 unknown */
int rg_icon_source_by_name(const char *name);
const char *rg_icon_source_name(int source);

/* Build from an extracted data/ folder (DATA0_0.HD6 / .DAT).  0 ok; -1 with a reason in
 * err (missing file, unexpected layout). */
int rg_icon_build(const char *data_dir, int source, rg_icon_set *out, char *err, size_t errcap);
/* Build from a source picture already in memory (tests): w x h straight RGBA. */
int rg_icon_build_rgba(const uint8_t *rgba, int w, int h, rg_icon_set *out);
void rg_icon_free(rg_icon_set *s);

/* One image as an icon resource image (BITMAPINFOHEADER, BGRA bottom-up, AND mask);
 * malloc'd, *len set.  NULL on a bad index. */
uint8_t *rg_icon_image_bytes(const rg_icon_set *s, int i, size_t *len);
/* The whole set as a .ico file (malloc'd). */
uint8_t *rg_icon_ico_bytes(const rg_icon_set *s, size_t *len);
/* The RT_GROUP_ICON payload for RT_ICON ids first_id .. first_id + n - 1 (malloc'd). */
uint8_t *rg_icon_group_bytes(const rg_icon_set *s, int first_id, size_t *len);

/* Windows: add RT_GROUP_ICON 1 + RT_ICON 1..n (language neutral) to an exe on disk with
 * BeginUpdateResource / UpdateResource, replacing an earlier icon of ours.  The exe must
 * not be running.  0 ok, -1 (err).  Elsewhere -1. */
int rg_icon_embed_exe(const char *exe_path_utf8, const rg_icon_set *s, char *err, size_t errcap);
/* 1 when the exe file (NULL = this process's own module) has any RT_GROUP_ICON. */
int rg_icon_exe_has_icon(const char *exe_path_utf8);
/* Windows: WM_SETICON ICON_BIG + ICON_SMALL on the window (an HWND), at the system's icon
 * sizes.  0 ok.  The icons stay alive until rg_icon_window_release. */
int rg_icon_set_window(void *hwnd, const rg_icon_set *s);
void rg_icon_window_release(void);

#ifdef __cplusplus
}
#endif

#endif
