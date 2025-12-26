set_project("XRay")
set_license("MIT")
set_description("XRay - A simple raylib example project using xmake")
set_languages("cxx23")

-- x-release-please-start-version
set_version("0.3.0")
-- x-release-please-end

add_rules("mode.debug", "mode.release")

add_requires("raylib 5.5")
add_requires("pugixml 1.15")
add_requires("cli11 2.6")
add_requires("spdlog 1.16")

target("xray")
    set_kind("binary")

    add_files("src/**.cpp")

    add_packages("raylib")
    add_packages("pugixml")
    add_packages("cli11")
    add_packages("spdlog")

    if is_plat("windows") then
        add_defines("WIN32_LEAN_AND_MEAN", "NOGDI", "NOUSER")
    end

    if is_mode("release") and is_plat("windows") then
        add_ldflags("-Wl,-subsystem,windows")
    end