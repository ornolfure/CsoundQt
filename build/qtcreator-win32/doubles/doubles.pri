CSOUND_DIR         = C:\_progs\Csound64
LIBSNDFILE_DIR     = C:\_dev\libsndfile-1_0_17
NSIS_DIR           = C:\_dev\nsis

QUTECSOUND_SRC_DIR = C:\_dev\svn\QuteCsound\trunk\qutecsound\src



QUTECSOUND_BUILD_INSTALLER = 1

CONFIG(debug, debug|release) \
{
    QUTECSOUND_BUILD_INSTALLER = 0
}
else \
{
    !exists($${NSIS_DIR}\makensis.exe) \
    {
        message(NSIS installer compiler was not found in the specified directory.)
        message(...skipping installer compilation.)

        QUTECSOUND_BUILD_INSTALLER = 0
    }
}



!build_pass \
{
    message(Generating QuteCsound Makefile for double precision \(64-bit\) Csound...)
}



CONFIG(debug, debug|release) \
{
    TARGET = qutecsound-d-debug
}
CONFIG(release, debug|release) \
{
    TARGET = qutecsound-d
}



include($${QUTECSOUND_SRC_DIR}\common.pri)



qute_cpp \
{
    LIBS += \
    $${CSOUND_DIR}\bin\libcsound64.a \
}


OTHER_FILES += \
$${QUTECSOUND_SRC_DIR}\windows-installer-doubles.nsi



qutecsound_post_build.target = all
QMAKE_EXTRA_TARGETS += qutecsound_post_build

contains(QUTECSOUND_BUILD_INSTALLER, 1) \
{
    qutecsound_post_build.depends += qutecsound_installer

    qutecsound_installer.commands = \
    $${NSIS_DIR}\makensis.exe /V4 "$${QUTECSOUND_SRC_DIR}\windows-installer-doubles.nsi"

    QMAKE_EXTRA_TARGETS += qutecsound_installer
}
