// SPDX-License-Identifier: CC0-1.0
// rg_icon tests (docs/ICON.md): resampler, .ico / group layout, determinism, the exe
// embed (Windows: on copies of this test exe), and the real data when RG_ICON_DATA names
// an extracted data/ folder.   ctest -L icon
#include "rg_icon.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

static int g_fail;
#define CHECK(c)                                                         \
    do {                                                                 \
        if (!(c)) {                                                      \
            fprintf(stderr, "%s:%d: CHECK(%s)\n", __FILE__, __LINE__, #c); \
            g_fail++;                                                    \
        }                                                                \
    } while (0)

static uint32_t rd32(const uint8_t *p) { return p[0] | p[1] << 8 | p[2] << 16 | (uint32_t)p[3] << 24; }

// a 40 x 48 picture: opaque colour (200, 100, 50) inside a transparent 4-px border
static std::vector<uint8_t> sample(int w, int h) {
    std::vector<uint8_t> v((size_t)w * h * 4, 0);
    for (int y = 4; y < h - 4; y++)
        for (int x = 4; x < w - 4; x++) {
            uint8_t *p = &v[((size_t)y * w + x) * 4];
            p[0] = 200; p[1] = 100; p[2] = 50; p[3] = 255;
        }
    return v;
}

static void t_resample() {
    auto src = sample(40, 48);
    rg_icon_set s;
    CHECK(rg_icon_build_rgba(src.data(), 40, 48, &s) == 0);
    CHECK(s.n == RG_ICON_IMAGES);
    for (int i = 0; i < s.n; i++) {
        int t = s.size[i];
        CHECK(t == rg_icon_sizes[i]);
        // the centre is the flat colour at every size; the corner is transparent
        const uint8_t *c = &s.rgba[i][((size_t)(t / 2) * t + t / 2) * 4];
        CHECK(c[0] == 200 && c[1] == 100 && c[2] == 50 && c[3] == 255);
        CHECK(s.rgba[i][3] == 0);
        // no colour where alpha is 0, colour never brighter than the source (premultiplied)
        for (int k = 0; k < t * t; k++) {
            const uint8_t *p = &s.rgba[i][(size_t)k * 4];
            if (!p[3]) CHECK(!p[0] && !p[1] && !p[2]);
            CHECK(p[0] <= 201 && p[1] <= 101 && p[2] <= 51);
        }
    }
    // 1:1 size (48 from a 48-high picture is not 1:1 in x; use a 48x48 one) is a copy
    auto sq = sample(48, 48);
    rg_icon_set q;
    CHECK(rg_icon_build_rgba(sq.data(), 48, 48, &q) == 0);
    CHECK(q.size[2] == 48 && !memcmp(q.rgba[2], sq.data(), sq.size()));
    rg_icon_free(&q);
    // deterministic: same bytes twice
    rg_icon_set s2;
    CHECK(rg_icon_build_rgba(src.data(), 40, 48, &s2) == 0);
    for (int i = 0; i < s.n; i++) CHECK(!memcmp(s.rgba[i], s2.rgba[i], (size_t)s.size[i] * s.size[i] * 4));
    rg_icon_free(&s2);
    rg_icon_free(&s);
}

static void t_layout() {
    auto src = sample(40, 48);
    rg_icon_set s;
    CHECK(rg_icon_build_rgba(src.data(), 40, 48, &s) == 0);
    size_t n = 0, gn = 0;
    uint8_t *ico = rg_icon_ico_bytes(&s, &n);
    uint8_t *grp = rg_icon_group_bytes(&s, 1, &gn);
    CHECK(ico && grp);
    if (ico && grp) {
        CHECK(ico[2] == 1 && ico[4] == RG_ICON_IMAGES);
        CHECK(gn == 6 + 14u * RG_ICON_IMAGES);
        size_t total = 6 + 16u * RG_ICON_IMAGES;
        for (int i = 0; i < RG_ICON_IMAGES; i++) {
            const uint8_t *e = ico + 6 + i * 16, *g = grp + 6 + i * 14;
            int t = rg_icon_sizes[i];
            CHECK(e[0] == (t == 256 ? 0 : t) && e[1] == e[0]);
            uint32_t bytes = rd32(e + 8), off = rd32(e + 12);
            CHECK(bytes == 40 + (uint32_t)(t * t * 4) + (uint32_t)(((t + 31) / 32) * 4 * t));
            CHECK(off == total);
            CHECK(rd32(ico + off) == 40 && rd32(ico + off + 4) == (uint32_t)t && rd32(ico + off + 8) == (uint32_t)(2 * t));
            CHECK(!memcmp(g, e, 12) && (g[12] | g[13] << 8) == 1 + i);
            // bottom-up BGRA: the first stored row is the picture's last; the mask marks the corner
            const uint8_t *px = ico + off + 40;
            CHECK(px[3] == 0);
            const uint8_t *mask = px + (size_t)t * t * 4;
            CHECK(mask[0] & 0x80);
            total += bytes;
        }
        CHECK(total == n);
    }
    free(ico);
    free(grp);
    rg_icon_free(&s);
}

static void t_sources() {
    CHECK(rg_icon_source_by_name("jaster") == RG_ICON_JASTER);
    CHECK(rg_icon_source_by_name("ship") == RG_ICON_SHIP);
    CHECK(rg_icon_source_by_name("x") == -1);
    rg_icon_set s;
    char err[256];
    CHECK(rg_icon_build("no-such-dir", RG_ICON_JASTER, &s, err, sizeof err) == -1 && err[0]);
}

#ifdef _WIN32
#include <windows.h>
static bool copy_file(const char *from, const char *to) { return CopyFileA(from, to, FALSE) != 0; }
static std::vector<uint8_t> slurp(const char *p) {
    std::vector<uint8_t> v;
    FILE *f = fopen(p, "rb");
    if (!f) return v;
    int c;
    while ((c = fgetc(f)) != EOF) v.push_back((uint8_t)c);
    fclose(f);
    return v;
}

static void t_embed(const char *self, const char *dir) {
    auto src = sample(40, 48);
    rg_icon_set s;
    CHECK(rg_icon_build_rgba(src.data(), 40, 48, &s) == 0);
    std::string a = std::string(dir) + "/embed_a.exe", b = std::string(dir) + "/embed_b.exe";
    CHECK(copy_file(self, a.c_str()) && copy_file(self, b.c_str()));
    CHECK(!rg_icon_exe_has_icon(a.c_str()));
    char err[256] = "";
    CHECK(rg_icon_embed_exe(a.c_str(), &s, err, sizeof err) == 0);
    CHECK(rg_icon_embed_exe(b.c_str(), &s, err, sizeof err) == 0);
    CHECK(rg_icon_exe_has_icon(a.c_str()));
    auto va = slurp(a.c_str()), vb = slurp(b.c_str()), vs = slurp(self);
    CHECK(!va.empty() && va == vb);   // deterministic
    CHECK(va.size() > vs.size());
    // the shell can load the group at 32 and 16 px
    HMODULE m = LoadLibraryExA(a.c_str(), nullptr, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE);
    CHECK(m != nullptr);
    if (m) {
        HICON i32 = (HICON)LoadImageA(m, MAKEINTRESOURCEA(1), IMAGE_ICON, 32, 32, 0);
        HICON i16 = (HICON)LoadImageA(m, MAKEINTRESOURCEA(1), IMAGE_ICON, 16, 16, 0);
        CHECK(i32 && i16);
        if (i32) DestroyIcon(i32);
        if (i16) DestroyIcon(i16);
        FreeLibrary(m);
    }
    // embedding again replaces (same bytes as once)
    CHECK(rg_icon_embed_exe(a.c_str(), &s, err, sizeof err) == 0);
    CHECK(slurp(a.c_str()) == vb);
    // the window icon path
    HWND w = CreateWindowExA(0, "STATIC", "icon", WS_POPUP, 0, 0, 8, 8, nullptr, nullptr, nullptr, nullptr);
    CHECK(w != nullptr);
    if (w) {
        CHECK(rg_icon_set_window(w, &s) == 0);
        CHECK(SendMessageA(w, WM_GETICON, ICON_BIG, 0) != 0);
        CHECK(SendMessageA(w, WM_GETICON, ICON_SMALL, 0) != 0);
        DestroyWindow(w);
        rg_icon_window_release();
    }
    DeleteFileA(a.c_str());
    DeleteFileA(b.c_str());
    rg_icon_free(&s);
}
#endif

static void t_data() {
    const char *d = getenv("RG_ICON_DATA");
    if (!d || !*d) {
        printf("data: skipped (RG_ICON_DATA not set)\n");
        return;
    }
    for (int src = 0; src < RG_ICON_SOURCES; src++) {
        rg_icon_set s;
        char err[256] = "";
        int rc = rg_icon_build(d, src, &s, err, sizeof err);
        if (rc) fprintf(stderr, "data %s: %s\n", rg_icon_source_name(src), err);
        CHECK(rc == 0);
        if (rc) continue;
        // not blank at 32 px: visible pixels, not one flat colour; cut-outs have clear pixels
        int seen = 0, clear = 0, lo = 255, hi = 0;
        for (int k = 0; k < 32 * 32; k++) {
            const uint8_t *p = &s.rgba[3][(size_t)k * 4];
            seen += p[3] >= 128;
            clear += p[3] == 0;
            if (p[3] >= 128) {
                lo = p[1] < lo ? p[1] : lo;
                hi = p[1] > hi ? p[1] : hi;
            }
        }
        if (seen <= 100 || hi - lo < 40)
            fprintf(stderr, "data %s: %d visible, green %d..%d\n", rg_icon_source_name(src), seen, lo, hi);
        CHECK(seen > 100 && hi - lo >= 40);
        if (src == RG_ICON_JASTER || src == RG_ICON_LOGO || src == RG_ICON_BIRTHMARK || src == RG_ICON_GLOBE)
            CHECK(clear > 50);
        rg_icon_free(&s);
    }
}

int main(int argc, char **argv) {
    const char *which = argc > 1 ? argv[1] : "all";
    const char *dir = argc > 2 ? argv[2] : ".";
    bool all = !strcmp(which, "all");
    if (all || !strcmp(which, "resample")) t_resample();
    if (all || !strcmp(which, "layout")) t_layout();
    if (all || !strcmp(which, "sources")) t_sources();
#ifdef _WIN32
    if (all || !strcmp(which, "embed")) {
        char self[MAX_PATH];
        GetModuleFileNameA(nullptr, self, MAX_PATH);
        t_embed(self, dir);
    }
#else
    (void)dir;
#endif
    if (all || !strcmp(which, "data")) t_data();
    if (g_fail) {
        fprintf(stderr, "%d check(s) failed\n", g_fail);
        return 1;
    }
    printf("ok (%s)\n", which);
    return 0;
}
