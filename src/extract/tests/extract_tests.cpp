// SPDX-License-Identifier: CC0-1.0
// Unit tests for rg-extract: hash vectors, and extraction of small synthetic disc images
// (single and dual layer, multi-extent file, duplicate across layers), including the
// wrong-image refusal paths.
#include <chrono>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../extract.h"
#include "../hash.h"
#include "../mvi.h"
#include "mvi_synth.h"

namespace fs = std::filesystem;

static int g_fail = 0;
#define CHECK(cond)                                                                   \
    do {                                                                              \
        if (!(cond)) {                                                                \
            std::cerr << __FILE__ << ":" << __LINE__ << ": CHECK failed: " #cond "\n"; \
            ++g_fail;                                                                 \
        }                                                                             \
    } while (0)

namespace {

std::string sha1_of(const std::string& s) {
    rgx::Sha1 h;
    h.update(s.data(), s.size());
    return h.finish_hex();
}
std::string sha256_of(const std::string& s) {
    rgx::Sha256 h;
    h.update(s.data(), s.size());
    return h.finish_hex();
}

void test_hashes() {
    CHECK(sha1_of("") == "da39a3ee5e6b4b0d3255bfef95601890afd80709");
    CHECK(sha1_of("abc") == "a9993e364706816aba3e25717850c26c9cd0d89d");
    CHECK(sha1_of("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") ==
          "84983e441c3bd26ebaae4aa1f95129e5e54670f1");
    CHECK(sha256_of("") == "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    CHECK(sha256_of("abc") == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    CHECK(sha256_of("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") ==
          "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
    // One million 'a', fed in uneven pieces to exercise the buffering.
    std::string a(1000000, 'a');
    rgx::Sha1 h1;
    rgx::Sha256 h2;
    size_t off = 0, step = 1;
    while (off < a.size()) {
        size_t n = std::min(step, a.size() - off);
        h1.update(a.data() + off, n);
        h2.update(a.data() + off, n);
        off += n;
        step = step * 3 % 997 + 1;
    }
    CHECK(h1.finish_hex() == "34aa973cd4c4daa4f61eeb2bdbad27316534016f");
    CHECK(h2.finish_hex() == "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0");
}

void test_system_cnf() {
    auto id = rgx::parse_system_cnf("BOOT2 = cdrom0:\\SCUS_974.90;1\r\nVER = 1.01\r\nVMODE = NTSC\r\n");
    CHECK(id.serial == "SCUS-97490");
    CHECK(id.version == "1.01");
    CHECK(id.region == "USA (NTSC-U)");
    auto pal = rgx::parse_system_cnf("BOOT2 = cdrom0:\\SCES_123.45;1\nVER = 1.00\n");
    CHECK(pal.serial == "SCES-12345");
    CHECK(pal.region == "Europe (PAL)");
}

// ---- synthetic ISO builder ----

struct Rec {
    std::string name;  // "." and ".." encoded as \0 and \1
    uint32_t lba;
    uint32_t size;
    uint8_t flags;
};

void put32(std::vector<uint8_t>& v, size_t o, uint32_t x) {
    for (int i = 0; i < 4; ++i) {
        v[o + i] = uint8_t(x >> (8 * i));
        v[o + 7 - i] = uint8_t(x >> (8 * i));
    }
}

void dir_record(std::vector<uint8_t>& img, size_t off, const Rec& r, size_t* used) {
    size_t len = 33 + r.name.size();
    if (len & 1) ++len;
    img[off] = uint8_t(len);
    put32(img, off + 2, r.lba);
    put32(img, off + 10, r.size);
    img[off + 25] = r.flags;
    img[off + 28] = 1;
    img[off + 31] = 1;
    img[off + 32] = uint8_t(r.name.size());
    std::memcpy(&img[off + 33], r.name.data(), r.name.size());
    *used = len;
}

void write_dir(std::vector<uint8_t>& img, uint32_t abs_sector, const std::vector<Rec>& recs) {
    size_t off = size_t(abs_sector) * 2048, used = 0;
    for (const Rec& r : recs) {
        dir_record(img, off, r, &used);
        off += used;
    }
}

void write_pvd(std::vector<uint8_t>& img, uint32_t abs_sector, uint32_t vol_blocks, uint32_t root_rel) {
    size_t o = size_t(abs_sector) * 2048;
    img[o] = 1;
    std::memcpy(&img[o + 1], "CD001", 5);
    img[o + 6] = 1;
    std::memcpy(&img[o + 8], "PLAYSTATION", 11);
    put32(img, o + 80, vol_blocks);
    img[o + 128] = 0x00;
    img[o + 129] = 0x08;  // 2048 LE
    img[o + 130] = 0x08;
    img[o + 131] = 0x00;  // BE
    size_t used;
    dir_record(img, o + 156, Rec{std::string(1, '\0'), root_rel, 2048, 2}, &used);
    size_t t = o + 2048;  // terminator
    img[t] = 255;
    std::memcpy(&img[t + 1], "CD001", 5);
    img[t + 6] = 1;
}

void fill(std::vector<uint8_t>& img, uint32_t sector, const std::string& s) {
    std::memcpy(&img[size_t(sector) * 2048], s.data(), s.size());
}

std::string pattern(size_t n, int seed) {
    std::string s(n, '\0');
    uint32_t x = 0x12345678u + uint32_t(seed);
    for (auto& c : s) {
        x = x * 1103515245u + 12345u;
        c = char(x >> 24);
    }
    return s;
}

struct Synth {
    std::string cnf = "BOOT2 = cdrom0:\\SLUS_123.45;1\r\nVER = 1.00\r\nVMODE = NTSC\r\n";
    std::string big1 = pattern(2048, 1), big2 = pattern(100, 2);
    std::string shared = pattern(3000, 3), shared_l1;
    std::string a = "hello", l1only = "layer one!";
    std::string bad_name;  // when set, replaces A.TXT;1
};

// Layer 0: volume of 30 sectors. Layer 1 starts at 30-16 = 14, PVD at 30, 22 sectors.
std::vector<uint8_t> build_iso(const Synth& s, bool dual) {
    const uint32_t v0 = 30, l1 = v0 - 16, v1 = 22;
    std::vector<uint8_t> img(size_t(dual ? l1 + v1 : v0) * 2048, 0);
    // garbage in the unused sector between the two BIG.BIN extents
    fill(img, 22, pattern(2048, 9));
    write_pvd(img, 16, v0, 18);
    write_dir(img, 18, {{std::string(1, '\0'), 18, 2048, 2},
                        {std::string(1, '\1'), 18, 2048, 2},
                        {"BIG.BIN;1", 21, 2048, 0x80},
                        {"BIG.BIN;1", 23, 100, 0},
                        {"DIR", 19, 2048, 2},
                        {"EMPTY.;1", 0, 0, 0},
                        {"SHARED.DAT;1", 24, 3000, 0},
                        {"SYSTEM.CNF;1", 20, uint32_t(s.cnf.size()), 0}});
    write_dir(img, 19, {{std::string(1, '\0'), 19, 2048, 2},
                        {std::string(1, '\1'), 18, 2048, 2},
                        {s.bad_name.empty() ? "A.TXT;1" : s.bad_name, 26, uint32_t(s.a.size()), 0}});
    fill(img, 20, s.cnf);
    fill(img, 21, s.big1);
    fill(img, 23, s.big2);
    fill(img, 24, s.shared);
    fill(img, 26, s.a);
    if (dual) {
        write_pvd(img, l1 + 16, v1, 18);
        write_dir(img, l1 + 18, {{std::string(1, '\0'), 18, 2048, 2},
                                 {std::string(1, '\1'), 18, 2048, 2},
                                 {"L1ONLY.BIN;1", 21, uint32_t(s.l1only.size()), 0},
                                 {"SHARED.DAT;1", 19, 3000, 0}});
        fill(img, l1 + 19, s.shared_l1.empty() ? s.shared : s.shared_l1);
        fill(img, l1 + 21, s.l1only);
    }
    return img;
}

fs::path g_tmp;

fs::path write_image(const std::string& name, const std::vector<uint8_t>& img) {
    fs::path p = g_tmp / name;
    std::ofstream(p, std::ios::binary).write(reinterpret_cast<const char*>(img.data()), std::streamsize(img.size()));
    return p;
}

std::string read_file(const fs::path& p) {
    std::ifstream f(p, std::ios::binary);
    std::ostringstream s;
    s << f.rdbuf();
    return s.str();
}

std::string sha1_file(const fs::path& p) { return sha1_of(read_file(p)); }

int run(const fs::path& iso, const fs::path& out, const std::string& expect, bool force, std::string* err_text,
        bool movies = true) {
    rgx::Options o;
    o.convert_movies = movies;
    o.iso = iso;
    o.out = out;
    o.expect_sha1 = expect;
    o.force = force;
    o.progress = false;
    std::ostringstream log, err;
    o.log = &log;
    o.err = &err;
    int rc = rgx::run_extract(o);
    if (err_text) *err_text = err.str();
    return rc;
}

void test_dual_layer_extract() {
    Synth s;
    fs::path iso = write_image("dual.iso", build_iso(s, true));
    std::string good = sha1_file(iso);
    fs::path out = g_tmp / "out_dual";

    std::string err;
    CHECK(run(iso, out, good, false, &err) == rgx::kOk);
    CHECK(read_file(out / "SYSTEM.CNF") == s.cnf);
    CHECK(read_file(out / "BIG.BIN") == s.big1 + s.big2);  // multi-extent, gap skipped
    CHECK(fs::exists(out / "EMPTY") && fs::file_size(out / "EMPTY") == 0);
    CHECK(read_file(out / "DIR" / "A.TXT") == s.a);
    CHECK(read_file(out / "SHARED.DAT") == s.shared);
    CHECK(read_file(out / "L1ONLY.BIN") == s.l1only);
    CHECK(!fs::exists(g_tmp / "out_dual.partial"));
    CHECK(!fs::exists(out / ".rg-extract-partial"));
    std::string m = read_file(out / "MANIFEST.tsv");
    CHECK(m.find("# source_sha1\t" + good + "\n") != std::string::npos);
    CHECK(m.find("SHARED.DAT\t3000\t" + sha256_of(s.shared) + "\t24\tL0:24,L1:33\n") != std::string::npos);
    CHECK(m.find("BIG.BIN\t2148\t" + sha256_of(s.big1 + s.big2) + "\t21\tL0:21\n") != std::string::npos);
    CHECK(m.find("L1ONLY.BIN\t10\t" + sha256_of(s.l1only) + "\t35\tL1:35\n") != std::string::npos);
    CHECK(m.find("DIR/A.TXT\t5\t") != std::string::npos);
    CHECK(m.rfind("# rg-extract manifest v2\n", 0) == 0);
    CHECK(m.find("# volume\t0\t0\t30\n# volume\t1\t14\t22\n") != std::string::npos);
    // No movies on this disc: the converted section is present and empty.
    const std::string empty_section = "# section\tconverted\npath\tsize\tsha256\tsource\tkind\n";
    CHECK(m.size() > empty_section.size() && m.substr(m.size() - empty_section.size()) == empty_section);

    // An existing complete extraction is refused without --force, replaced with it.
    CHECK(run(iso, out, good, false, &err) == rgx::kOutputExists);
    std::ofstream(out / "stale.txt") << "x";
    CHECK(run(iso, out, good, true, &err) == rgx::kOk);
    CHECK(!fs::exists(out / "stale.txt"));
    CHECK(!fs::exists(g_tmp / "out_dual.old"));
    CHECK(read_file(out / "SHARED.DAT") == s.shared);
}

void test_single_layer_extract() {
    Synth s;
    fs::path iso = write_image("single.iso", build_iso(s, false));
    fs::path out = g_tmp / "out_single";
    CHECK(run(iso, out, sha1_file(iso), false, nullptr) == rgx::kOk);
    CHECK(read_file(out / "BIG.BIN") == s.big1 + s.big2);
    CHECK(!fs::exists(out / "L1ONLY.BIN"));
}

void test_wrong_image_refused() {
    Synth s;
    fs::path iso = write_image("wrong.iso", build_iso(s, true));
    fs::path out = g_tmp / "out_wrong";
    std::string err;
    // Expected hash differs from the image: refused after the pass, nothing left behind.
    CHECK(run(iso, out, std::string(40, '0'), false, &err) == rgx::kWrongImage);
    CHECK(err.find("SLUS-12345") != std::string::npos);
    CHECK(!fs::exists(out));
    CHECK(!fs::exists(g_tmp / "out_wrong.partial"));

    // Built-in check: this image is not SCUS-97490, refused up front and named.
    CHECK(run(iso, out, "", false, &err) == rgx::kWrongImage);
    CHECK(err.find("SLUS-12345 (USA (NTSC-U)) version 1.00") != std::string::npos);
    CHECK(!fs::exists(out));

    // Another release of the game is named.
    Synth eu;
    eu.cnf = "BOOT2 = cdrom0:\\SCES_545.52;1\r\nVER = 1.00\r\nVMODE = PAL\r\n";
    fs::path eiso = write_image("eu.iso", build_iso(eu, true));
    CHECK(run(eiso, out, "", false, &err) == rgx::kWrongImage);
    CHECK(err.find("Rogue Galaxy (Europe), SCES-54552 (Europe (PAL)) version 1.00") != std::string::npos);

    // Same serial and version as the accepted disc but different bytes: still refused.
    Synth fake;
    fake.cnf = "BOOT2 = cdrom0:\\SCUS_974.90;1\r\nVER = 1.01\r\nVMODE = NTSC\r\n";
    fs::path fiso = write_image("fake.iso", build_iso(fake, true));
    CHECK(run(fiso, out, "", false, &err) == rgx::kWrongImage);
    CHECK(err.find("not a clean copy") != std::string::npos);
    CHECK(!fs::exists(out));

    // A one-byte change in file data changes the image hash: refused.
    std::vector<uint8_t> img = build_iso(s, true);
    std::string good = sha1_of(std::string(img.begin(), img.end()));
    img[size_t(26) * 2048] ^= 1;
    fs::path tiso = write_image("tampered.iso", img);
    CHECK(run(tiso, out, good, false, &err) == rgx::kWrongImage);
    CHECK(!fs::exists(out));
}

void test_malformed() {
    std::string err;
    // Layer copies that disagree.
    Synth s;
    s.shared_l1 = pattern(3000, 77);
    fs::path iso = write_image("mismatch.iso", build_iso(s, true));
    CHECK(run(iso, g_tmp / "out_mm", sha1_file(iso), false, &err) == rgx::kMalformedIso);
    CHECK(!fs::exists(g_tmp / "out_mm"));
    // Names that would escape the output folder or can't exist on Windows.
    for (const char* bad : {"..", "CON.TXT;1", "A:B;1"}) {
        Synth b;
        b.bad_name = bad;
        fs::path p = write_image("badname.iso", build_iso(b, true));
        CHECK(run(p, g_tmp / "out_bad", sha1_file(p), false, &err) == rgx::kMalformedIso);
        CHECK(!fs::exists(g_tmp / "out_bad"));
    }
    // Truncated image: layer-1 file data cut off.
    std::vector<uint8_t> img = build_iso(Synth(), true);
    img.resize(img.size() - 2048);
    fs::path t = write_image("trunc.iso", img);
    CHECK(run(t, g_tmp / "out_tr", sha1_file(t), false, &err) == rgx::kMalformedIso);
    // Missing file.
    CHECK(run(g_tmp / "nope.iso", g_tmp / "out_tr", "", false, &err) == rgx::kUnreadableIso);
}

// MOVIE/<dir>/*.MVI files are converted into converted/MOVIE/<dir>/ (docs/EXTRACT.md);
// the originals stay byte-identical, and a movie that does not convert is only a warning.
void test_movie_conversion() {
    mvisynth::Synth ms;
    mvisynth::build(ms);
    mvisynth::Bytes mv = mvisynth::scramble(ms.plain);
    const std::string good(mv.begin(), mv.end()), bad = pattern(5000, 5), cnf = Synth().cnf;
    const uint32_t good_at = 22, bad_at = good_at + uint32_t((good.size() + 2047) / 2048);
    const uint32_t vol = bad_at + uint32_t((bad.size() + 2047) / 2048);
    std::vector<uint8_t> img(size_t(vol) * 2048, 0);
    write_pvd(img, 16, vol, 18);
    const std::string dot(1, '\0'), dotdot(1, '\1');
    write_dir(img, 18, {{dot, 18, 2048, 2}, {dotdot, 18, 2048, 2}, {"MOVIE", 19, 2048, 2},
                        {"SYSTEM.CNF;1", 21, uint32_t(cnf.size()), 0}});
    write_dir(img, 19, {{dot, 19, 2048, 2}, {dotdot, 18, 2048, 2}, {"00", 20, 2048, 2}});
    write_dir(img, 20, {{dot, 20, 2048, 2}, {dotdot, 19, 2048, 2}, {"BAD.MVI;1", bad_at, uint32_t(bad.size()), 0},
                        {"GOOD.MVI;1", good_at, uint32_t(good.size()), 0}});
    fill(img, 21, cnf);
    fill(img, good_at, good);
    fill(img, bad_at, bad);
    fs::path iso = write_image("movies.iso", img);
    std::string sha = sha1_file(iso), err;

    std::string want_mpg, want_wav, why;
    CHECK(rgx::mvi::convert_movie_memory(mv.data(), mv.size(), &want_mpg, &want_wav, nullptr, &why));

    fs::path out = g_tmp / "out_movies";
    CHECK(run(iso, out, sha, false, &err) == rgx::kOk);
    CHECK(read_file(out / "MOVIE" / "00" / "GOOD.MVI") == good);
    CHECK(read_file(out / "MOVIE" / "00" / "BAD.MVI") == bad);
    fs::path conv = out / "converted" / "MOVIE" / "00";
    CHECK(read_file(conv / "GOOD.mpg") == want_mpg);
    CHECK(read_file(conv / "GOOD.wav") == want_wav);
    CHECK(!fs::exists(conv / "BAD.mpg") && !fs::exists(conv / "BAD.wav"));
    CHECK(err.find("warning: 'MOVIE/00/BAD.MVI' not converted") != std::string::npos);
    std::string m = read_file(out / "MANIFEST.tsv");
    // Disc rows keep the v1 format; converted rows follow in their own section.
    CHECK(m.find("MOVIE/00/GOOD.MVI\t" + std::to_string(good.size()) + "\t" + sha256_of(good) + "\t" +
                 std::to_string(good_at) + "\tL0:" + std::to_string(good_at) + "\n") != std::string::npos);
    size_t sec = m.find("# section\tconverted\n");
    CHECK(sec != std::string::npos && m.find("converted/") > sec);
    size_t failed = m.find("# convert_failed\tMOVIE/00/BAD.MVI\t");
    CHECK(failed != std::string::npos && failed > sec);
    CHECK(m.find("converted/MOVIE/00/GOOD.mpg\t" + std::to_string(want_mpg.size()) + "\t" + sha256_of(want_mpg) +
                 "\tMOVIE/00/GOOD.MVI\tmovie-video\n") != std::string::npos);
    CHECK(m.find("converted/MOVIE/00/GOOD.wav\t" + std::to_string(want_wav.size()) + "\t" + sha256_of(want_wav) +
                 "\tMOVIE/00/GOOD.MVI\tmovie-audio\n") != std::string::npos);
    CHECK(m.find("BAD.mpg") == std::string::npos);

    // --no-movies: originals only.
    fs::path out2 = g_tmp / "out_nomovies";
    CHECK(run(iso, out2, sha, false, &err, false) == rgx::kOk);
    CHECK(read_file(out2 / "MOVIE" / "00" / "GOOD.MVI") == good);
    CHECK(!fs::exists(out2 / "converted"));
    CHECK(read_file(out2 / "MANIFEST.tsv").find("converted/") == std::string::npos);
}

}  // namespace

int main() {
    g_tmp = fs::temp_directory_path() /
            ("rg-extract-tests-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    fs::create_directories(g_tmp);
    test_hashes();
    test_system_cnf();
    test_dual_layer_extract();
    test_single_layer_extract();
    test_wrong_image_refused();
    test_malformed();
    test_movie_conversion();
    if (g_fail) {
        std::cerr << g_fail << " check(s) failed; test files kept in " << g_tmp.u8string() << "\n";
        return 1;
    }
    std::error_code ec;
    fs::remove_all(g_tmp, ec);
    std::cout << "all rg-extract tests passed\n";
    return 0;
}
