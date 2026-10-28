// SPDX-License-Identifier: CC0-1.0
// Unit tests for the MVI movie converter (src/extract/mvi.cpp): a small synthetic movie
// built here (program stream, MPEG-2 headers, SShd/SSbd PCM), scrambled with the MVI
// keystream, then converted. Optional: with RG_DATA=<extracted data folder>, the seed is
// re-derived from SCUS_974.90 and the first part of a real movie is converted.
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../mvi.h"
#include "mvi_synth.h"

namespace fs = std::filesystem;
using Bytes = std::vector<uint8_t>;

static int g_fail = 0;
#define CHECK(cond)                                                                   \
    do {                                                                              \
        if (!(cond)) {                                                                \
            std::cerr << __FILE__ << ":" << __LINE__ << ": CHECK failed: " #cond "\n"; \
            ++g_fail;                                                                 \
        }                                                                             \
    } while (0)

namespace {

using namespace mvisynth;

uint32_t rd32(const std::string& s, size_t o) {
    return uint32_t(uint8_t(s[o])) | uint32_t(uint8_t(s[o + 1])) << 8 | uint32_t(uint8_t(s[o + 2])) << 16 |
           uint32_t(uint8_t(s[o + 3])) << 24;
}

void test_keystream() {
    const uint8_t* k = rgx::mvi::keystream();
    CHECK(k[0] == 0x55 && k[1] == 0x32 && k[2] == 0x29 && k[3] == 0x98);
    uint32_t w1 = rgx::mvi::kSeed * rgx::mvi::kMul;
    CHECK(k[4] == uint8_t(w1) && k[7] == uint8_t(w1 >> 24));
    // descramble() is position-aware: scrambling in odd pieces equals scrambling at once.
    Bytes a(5000, 0x5A), b = a;
    rgx::mvi::descramble(a.data(), a.size(), 0);
    rgx::mvi::descramble(b.data(), 3, 0);
    rgx::mvi::descramble(b.data() + 3, 2100, 3);
    rgx::mvi::descramble(b.data() + 2103, 2897, 2103);
    CHECK(a == b);
    CHECK(a[2048] == a[0] && a[4096 + 7] == a[7]);  // resets every sector
    // Seed derivation from an obfuscated key: obfuscate "ABCDEFG" the way the game stores it.
    const char* plain = "ABCDEFG";
    uint8_t stored[8] = {};
    uint8_t kk = 0x3E;
    for (int i = 0; i < 7; ++i) {
        stored[i] = uint8_t(plain[i] ^ kk);
        kk = uint8_t(kk * 13 + 1);
    }
    uint32_t want = uint32_t(uint8_t('A' + 'E')) | uint32_t(uint8_t('B' + 'F')) << 8 |
                    uint32_t(uint8_t('C' + 'G')) << 16 | uint32_t('D') << 24;
    CHECK(rgx::mvi::seed_from_stored_key(stored, 8) == want);
}

void check_convert(Synth& s) {
    build(s);
    Bytes enc = scramble(s.plain);
    std::string mpg, wav, err;
    rgx::mvi::MovieInfo mi;
    bool ok = rgx::mvi::convert_movie_memory(enc.data(), enc.size(), &mpg, &wav, &mi, &err);
    CHECK(ok);
    if (!ok) {
        std::cerr << "  error: " << err << "\n";
        return;
    }
    CHECK(mpg == std::string(s.expect_mpg.begin(), s.expect_mpg.end()));
    CHECK(mi.width == 512 && mi.height == 336 && mi.frame_rate_code == 4 && mi.aspect_code == 2);
    CHECK(mi.profile_level == 0x48);
    CHECK(mi.pictures == 3);
    CHECK(mi.audio_rate == s.rate && mi.audio_channels == 2 && mi.audio_interleave == s.il);
    CHECK(mi.audio_frames_in == uint64_t(s.frames));
    CHECK(mi.video_first_pts == s.vpts && mi.audio_first_pts == s.apts);
    CHECK(mi.packs == 1 && mi.audio_packets == 2 && mi.video_packets == 2);
    CHECK(wav.size() == 44 + s.expect_pcm.size());
    CHECK(wav.compare(0, 4, "RIFF") == 0 && wav.compare(8, 8, "WAVEfmt ") == 0);
    CHECK(rd32(wav, 4) == wav.size() - 8 && rd32(wav, 24) == s.rate && rd32(wav, 28) == s.rate * 4);
    CHECK(rd32(wav, 40) == s.expect_pcm.size());
    CHECK(wav.compare(44, std::string::npos, std::string(s.expect_pcm.begin(), s.expect_pcm.end())) == 0);
}

void test_convert() {
    Synth a;  // in sync
    check_convert(a);
    Synth b;  // audio starts 2 frames (20 ticks at 9 kHz) after video: silence prepended
    b.apts = b.vpts + 20;
    check_convert(b);
    Synth c;  // audio starts 3 frames before video: those frames are dropped
    c.apts = c.vpts - 30;
    check_convert(c);
}

void test_rejects() {
    Synth s;
    build(s);
    std::string mpg, wav, err;
    // Not scrambled: the first sector does not descramble to a pack header.
    CHECK(!rgx::mvi::convert_movie_memory(s.plain.data(), s.plain.size(), &mpg, &wav, nullptr, &err));
    CHECK(err.find("not an MVI") != std::string::npos);
    // Truncated in the middle of a packet.
    Bytes enc = scramble(s.plain);
    CHECK(!rgx::mvi::convert_movie_memory(enc.data(), 100, &mpg, &wav, nullptr, &err));
    CHECK(err.find("truncated") != std::string::npos);
    // Empty input.
    CHECK(!rgx::mvi::convert_movie_memory(enc.data(), 0, &mpg, &wav, nullptr, &err));
    // Unknown stream id.
    Bytes bad = s.plain;
    bad[14 + 12 + 3] = 0xC0;  // first video PES -> MPEG audio stream id
    bad = scramble(bad);
    CHECK(!rgx::mvi::convert_movie_memory(bad.data(), bad.size(), &mpg, &wav, nullptr, &err));
    CHECK(err.find("stream id") != std::string::npos);
}

// Optional: real data under RG_DATA.
void test_real_data() {
    const char* env = std::getenv("RG_DATA");
    if (!env) {
        std::cout << "RG_DATA not set: skipping the real-data checks\n";
        return;
    }
    fs::path data = fs::u8path(env);
    std::ifstream elf(data / "SCUS_974.90", std::ios::binary);
    std::string e((std::istreambuf_iterator<char>(elf)), std::istreambuf_iterator<char>());
    CHECK(e.size() > 0x100);
    if (e.size() <= 0x100) return;
    // Find the PT_LOAD segment holding 0x0044B330 and derive the seed from the key there.
    uint32_t phoff = rd32(e, 28);
    unsigned phentsize = uint8_t(e[42]) | uint8_t(e[43]) << 8, phnum = uint8_t(e[44]) | uint8_t(e[45]) << 8;
    bool found = false;
    for (unsigned i = 0; i < phnum; ++i) {
        size_t ph = phoff + size_t(i) * phentsize;
        uint32_t type = rd32(e, ph), off = rd32(e, ph + 4), va = rd32(e, ph + 8), fsz = rd32(e, ph + 16);
        if (type == 1 && va <= 0x44B330u && 0x44B330u < va + fsz) {
            const uint8_t* key = reinterpret_cast<const uint8_t*>(e.data()) + off + (0x44B330u - va);
            CHECK(rgx::mvi::seed_from_stored_key(key, 64) == rgx::mvi::kSeed);
            found = true;
        }
    }
    CHECK(found);
    // TITLE01 (8 MB) converts; numbers from docs/MVI.md.
    std::ifstream mv(data / "MOVIE" / "00" / "TITLE01.MVI", std::ios::binary);
    Bytes m((std::istreambuf_iterator<char>(mv)), std::istreambuf_iterator<char>());
    CHECK(m.size() == 8404996);
    std::string mpg, wav, err;
    rgx::mvi::MovieInfo mi;
    bool ok = rgx::mvi::convert_movie_memory(m.data(), m.size(), &mpg, &wav, &mi, &err);
    CHECK(ok);
    if (!ok) std::cerr << "  error: " << err << "\n";
    CHECK(mi.width == 512 && mi.height == 448 && mi.frame_rate_code == 5 && mi.audio_rate == 48048);
    CHECK(mi.pictures == 540 && mi.audio_frames_in == 865024 && mi.audio_shift_frames == 0);
    CHECK(mpg.size() == m.size());
    // A cut-off movie is refused (its audio is shorter than the SSbd length).
    CHECK(!rgx::mvi::convert_movie_memory(m.data(), 2 << 20, &mpg, &wav, nullptr, &err));
}

}  // namespace

int main() {
    test_keystream();
    test_convert();
    test_rejects();
    test_real_data();
    if (g_fail) {
        std::cerr << g_fail << " check(s) failed\n";
        return 1;
    }
    std::cout << "all rg-extract MVI tests passed\n";
    return 0;
}
