include_guard(GLOBAL)

enable_testing()

function(bin_from_file fname outname)
    get_filename_component(bname ${fname} NAME_WE)
    set(${outname} ${bname} PARENT_SCOPE)
    add_executable(${bname} ${fname})
    target_link_libraries (${bname}
        PRIVATE default::flags
    )
endfunction(bin_from_file)


