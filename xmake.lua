add_rules("mode.debug", "mode.release")

set_policy("build.warning", true)
set_warnings("all", "extra")
set_config("mode", "debug")

option("only_ascii")
    set_default("autoconfig")
    set_showmenu(true)
    set_values("autoconfig", "y", "n")


target("test")
    add_includedirs("./")
    add_files("**.cpp")

    if get_config("only_ascii") == "autoconfig" then
        if is_plat("mingw") then
            add_defines("ONLY_ASCII")
        end
    elseif has_config("only_ascii") then
        add_defines("ONLY_ASCII")
    end

    if is_plat("mingw") then
        add_ldflags("-static")
    end