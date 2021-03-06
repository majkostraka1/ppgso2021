find_path(GLEW_INCLUDE_DIR GL/glew.h)
message("FIND_PATH ${GLEW_INCLUDE_DIR}")
if(NOT GLEW_LIBRARY)
    find_library(GLEW_LIBRARY_RELEASE NAMES GLEW glew32 glew glew32s PATH_SUFFIXES lib64 libx32)
    find_library(GLEW_LIBRARY_DEBUG NAMES GLEWd glew32d glewd PATH_SUFFIXES lib64)

    include(SelectLibraryConfigurations)
    select_library_configurations(GLEW)
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLEW REQUIRED_VARS GLEW_INCLUDE_DIR GLEW_LIBRARY)

if(GLEW_FOUND)
    set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
    message("-- Found GLEW: " ${GLEW_INCLUDE_DIRS})

    if(NOT GLEW_LIBRARIES)
        set(GLEW_LIBRARIES ${GLEW_LIBRARY})
    endif()
    message("-- GLEW_LIBRARIES: " ${GLEW_LIBRARIES})

    if (NOT TARGET GLEW::GLEW)
        add_library(GLEW::GLEW UNKNOWN IMPORTED)
        set_target_properties(GLEW::GLEW PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INCLUDE_DIRS}")

        if(GLEW_LIBRARY_RELEASE)
            set_property(TARGET GLEW::GLEW APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
            set_target_properties(GLEW::GLEW PROPERTIES IMPORTED_LOCATION_RELEASE "${GLEW_LIBRARY_RELEASE}")
        endif()

        if(GLEW_LIBRARY_DEBUG)
            set_property(TARGET GLEW::GLEW APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
            set_target_properties(GLEW::GLEW PROPERTIES IMPORTED_LOCATION_DEBUG "${GLEW_LIBRARY_DEBUG}")
        endif()

        if(NOT GLEW_LIBRARY_RELEASE AND NOT GLEW_LIBRARY_DEBUG)
            set_property(TARGET GLEW::GLEW APPEND PROPERTY IMPORTED_LOCATION "${GLEW_LIBRARY}")
        endif()
    endif()
endif()

mark_as_advanced(GLEW_INCLUDE_DIR)
