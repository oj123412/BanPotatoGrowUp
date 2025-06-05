add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")

-- Target LeviLamina 3 v1.2.0 for compatibility
-- add_requires("levilamina develop") to use develop version
-- please note that you should add bdslibrary yourself if using dev version
if is_config("target_type", "server") then
    add_requires("levilamina 1.2.0", {configs = {target_type = "server"}})
else
    add_requires("levilamina 1.2.0", {configs = {target_type = "client"}})
end

add_requires("levibuildscript")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

option("target_type")
    set_default("server")
    set_showmenu(true)
    set_values("server", "client")
option_end()

target("potato-bonemeal-blocker") -- Main plugin target
    add_rules("@levibuildscript/linkrule")
    add_rules("@levibuildscript/modpacker")
    add_cxflags( "/EHa", "/utf-8", "/W4", "/w44265", "/w44289", "/w44296", "/w45263", "/w44738", "/w45204")
    add_defines("NOMINMAX", "UNICODE")
    add_packages("levilamina")
    set_exceptions("none") -- To avoid conflicts with /EHa.
    set_kind("shared")
    set_languages("c++20")
    set_symbols("debug")
    add_headerfiles("src/mod/**.h")
    add_files("src/mod/**.cpp")
    add_includedirs("src")
    -- Optimization flags for release builds
    if is_mode("release") then
        add_cxflags("/O2", "/Ob2", "/Oi", "/Ot", "/Oy", "/GL")
        add_ldflags("/LTCG", "/OPT:REF", "/OPT:ICF")
        add_defines("NDEBUG")
    end

-- Test target for unit tests
target("potato-bonemeal-blocker-test")
    set_kind("binary")
    set_languages("c++20")
    add_defines("STANDALONE_TEST", "NOMINMAX", "UNICODE")
    add_headerfiles("src/mod/**.h")
    add_files("src/mod/PotatoBoneMealBlocker.cpp", "src/test/PotatoBoneMealBlockerTest.cpp")
    add_includedirs("src")
    set_symbols("debug")
    -- Mock LeviLamina dependencies for testing
    add_defines("MOCK_LEVILAMINA")
    set_default(false) -- Don't build by default

-- Benchmark target for performance testing
target("potato-bonemeal-blocker-benchmark")
    set_kind("binary")
    set_languages("c++20")
    add_defines("STANDALONE_BENCHMARK", "NOMINMAX", "UNICODE")
    add_headerfiles("src/mod/**.h")
    add_files("src/mod/PotatoBoneMealBlocker.cpp", "src/test/PerformanceBenchmark.cpp")
    add_includedirs("src")
    set_symbols("debug")
    -- Mock LeviLamina dependencies for benchmarking
    add_defines("MOCK_LEVILAMINA")
    set_default(false) -- Don't build by default

-- LL3 v1.2.0 compatibility test target
target("potato-bonemeal-blocker-ll3-test")
    set_kind("binary")
    set_languages("c++20")
    add_defines("STANDALONE_LL3_TEST", "NOMINMAX", "UNICODE")
    add_headerfiles("src/mod/**.h")
    add_files("src/mod/PotatoBoneMealBlocker.cpp", "src/test/LL3CompatibilityTest.cpp")
    add_includedirs("src")
    set_symbols("debug")
    -- Mock LeviLamina dependencies for testing
    add_defines("MOCK_LEVILAMINA")
    set_default(false) -- Don't build by default
