FIND_PATH(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h
    HINTS
    ENV SDL2MIXERDIR
    ENV SDL2DIR
    PATH_SUFFIXES SDL2
    include/SDL2 include
    PATHS ${SDL2_MIXER_PATH}
)

IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(VC_LIB_PATH_SUFFIX lib/x64)
ELSE()
    SET(VC_LIB_PATH_SUFFIX lib/x86)
ENDIF()

FIND_LIBRARY(SDL2_MIXER_LIBRARY
    NAMES SDL2_mixer
    HINTS
    ENV SDL2MIXERDIR
    ENV SDL2DIR
    PATH_SUFFIXES lib bin ${VC_LIB_PATH_SUFFIX}
    PATHS ${SDL2_MIXER_PATH}
)

IF(SDL2_MIXER_INCLUDE_DIR AND EXISTS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h")
    FILE(STRINGS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL2_MIXER_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_MIXER_MAJOR_VERSION[ \t]+[0-9]+$")
    FILE(STRINGS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL2_MIXER_VERSION_MINOR_LINE REGEX "^#define[ \t]+SDL_MIXER_MINOR_VERSION[ \t]+[0-9]+$")
    FILE(STRINGS "${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h" SDL2_MIXER_VERSION_PATCH_LINE REGEX "^#define[ \t]+SDL_MIXER_PATCHLEVEL[ \t]+[0-9]+$")
    STRING(REGEX REPLACE "^#define[ \t]+SDL_MIXER_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_MIXER_VERSION_MAJOR "${SDL2_MIXER_VERSION_MAJOR_LINE}")
    STRING(REGEX REPLACE "^#define[ \t]+SDL_MIXER_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL2_MIXER_VERSION_MINOR "${SDL2_MIXER_VERSION_MINOR_LINE}")
    STRING(REGEX REPLACE "^#define[ \t]+SDL_MIXER_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" SDL2_MIXER_VERSION_PATCH "${SDL2_MIXER_VERSION_PATCH_LINE}")
    SET(SDL2_MIXER_VERSION_STRING ${SDL2_MIXER_VERSION_MAJOR}.${SDL2_MIXER_VERSION_MINOR}.${SDL2_MIXER_VERSION_PATCH})
    UNSET(SDL2_MIXER_VERSION_MAJOR_LINE)
    UNSET(SDL2_MIXER_VERSION_MINOR_LINE)
    UNSET(SDL2_MIXER_VERSION_PATCH_LINE)
    UNSET(SDL2_MIXER_VERSION_MAJOR)
    UNSET(SDL2_MIXER_VERSION_MINOR)
    UNSET(SDL2_MIXER_VERSION_PATCH)
ENDIF()

SET(SDL2_MIXER_LIBRARIES ${SDL2_MIXER_LIBRARY})
SET(SDL2_MIXER_INCLUDE_DIRS ${SDL2_MIXER_INCLUDE_DIR})

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(SDL2_mixer
    REQUIRED_VARS SDL2_MIXER_LIBRARIES SDL2_MIXER_INCLUDE_DIRS
    VERSION_VAR SDL2_MIXER_VERSION_STRING)

SET(SDLMIXER_LIBRARY ${SDL2_MIXER_LIBRARIES})
SET(SDLMIXER_INCLUDE_DIR ${SDL2_MIXER_INCLUDE_DIRS})
SET(SDLMIXER_FOUND ${SDL2_MIXER_FOUND})

MARK_AS_ADVANCED(SDL2_MIXER_LIBRARY SDL2_MIXER_INCLUDE_DIR)
