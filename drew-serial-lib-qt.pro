QT += core gui
QT += serialport
QT += uitools
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Packetizer/ros_encoding.cpp \
    Packetizer/util/CRCx/FastCRC/FastCRChw.cpp \
    QCustomPlot/qcustomplot.cpp \
    datalogger.cpp \
    filedownloader.cpp \
    main.cpp \
    mainwindow.cpp \
    serial_manager.cpp \
    serialportreader-async.cpp \
    serialportwriter-async.cpp

HEADERS += \
    DeviceSelector.h \
    MsgPack.h \
    MsgPack/MsgPack.h \
    MsgPack/MsgPack/Packer.h \
    MsgPack/MsgPack/Types.h \
    MsgPack/MsgPack/Unpacker.h \
    MsgPack/MsgPack/Utility.h \
    MsgPack/MsgPack/util/ArxContainer/ArxContainer.h \
    MsgPack/MsgPack/util/ArxContainer/ArxContainer/has_include.h \
    MsgPack/MsgPack/util/ArxContainer/ArxContainer/has_libstdcplusplus.h \
    MsgPack/MsgPack/util/ArxContainer/ArxContainer/initializer_list.h \
    MsgPack/MsgPack/util/ArxContainer/ArxContainer/replace_minmax_macros.h \
    MsgPack/MsgPack/util/ArxTypeTraits/ArxTypeTraits.h \
    MsgPack/MsgPack/util/ArxTypeTraits/ArxTypeTraits/functional.h \
    MsgPack/MsgPack/util/ArxTypeTraits/ArxTypeTraits/has_include.h \
    MsgPack/MsgPack/util/ArxTypeTraits/ArxTypeTraits/has_libstdcplusplus.h \
    MsgPack/MsgPack/util/ArxTypeTraits/ArxTypeTraits/initializer_list.h \
    MsgPack/MsgPack/util/ArxTypeTraits/ArxTypeTraits/replace_minmax_macros.h \
    MsgPack/MsgPack/util/ArxTypeTraits/ArxTypeTraits/tuple.h \
    MsgPack/MsgPack/util/ArxTypeTraits/ArxTypeTraits/type_traits.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/FileLogger.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/Manager.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/Types.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxContainer/ArxContainer.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxContainer/ArxContainer/has_include.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxContainer/ArxContainer/has_libstdcplusplus.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxContainer/ArxContainer/initializer_list.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxContainer/ArxContainer/replace_minmax_macros.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxTypeTraits/ArxTypeTraits.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxTypeTraits/ArxTypeTraits/functional.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxTypeTraits/ArxTypeTraits/has_include.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxTypeTraits/ArxTypeTraits/has_libstdcplusplus.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxTypeTraits/ArxTypeTraits/initializer_list.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxTypeTraits/ArxTypeTraits/replace_minmax_macros.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxTypeTraits/ArxTypeTraits/tuple.h \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxTypeTraits/ArxTypeTraits/type_traits.h \
    MsgPack/MsgPack/util/DebugLog/DebugLogDisable.h \
    MsgPack/MsgPack/util/DebugLog/DebugLogEnable.h \
    MsgPack/MsgPack/util/DebugLog/DebugLogRestoreState.h \
    MsgPack/MsgPack/util/TeensyDirtySTLErrorSolution/TeensyDirtySTLErrorSolution.h \
    MsgPack_types.h \
    Packetizer.h \
    Packetizer/Encoding.h \
    Packetizer/Types.h \
    Packetizer/util/ArxContainer/ArxContainer.h \
    Packetizer/util/ArxContainer/ArxContainer/has_include.h \
    Packetizer/util/ArxContainer/ArxContainer/has_libstdcplusplus.h \
    Packetizer/util/ArxContainer/ArxContainer/initializer_list.h \
    Packetizer/util/ArxContainer/ArxContainer/replace_minmax_macros.h \
    Packetizer/util/ArxSmartPtr/ArxSmartPtr.h \
    Packetizer/util/ArxSmartPtr/ArxSmartPtr/detail/has_include.h \
    Packetizer/util/ArxSmartPtr/ArxSmartPtr/detail/has_libstdcplusplus.h \
    Packetizer/util/ArxSmartPtr/ArxSmartPtr/detail/replace_minmax_macros.h \
    Packetizer/util/ArxSmartPtr/ArxSmartPtr/detail/shared_count.h \
    Packetizer/util/ArxSmartPtr/ArxSmartPtr/shared_ptr.h \
    Packetizer/util/ArxTypeTraits/ArxTypeTraits.h \
    Packetizer/util/ArxTypeTraits/ArxTypeTraits/functional.h \
    Packetizer/util/ArxTypeTraits/ArxTypeTraits/has_include.h \
    Packetizer/util/ArxTypeTraits/ArxTypeTraits/has_libstdcplusplus.h \
    Packetizer/util/ArxTypeTraits/ArxTypeTraits/initializer_list.h \
    Packetizer/util/ArxTypeTraits/ArxTypeTraits/replace_minmax_macros.h \
    Packetizer/util/ArxTypeTraits/ArxTypeTraits/tuple.h \
    Packetizer/util/ArxTypeTraits/ArxTypeTraits/type_traits.h \
    Packetizer/util/CRCx/CRCpp/CRCpp.h \
    Packetizer/util/CRCx/CRCx.h \
    Packetizer/util/CRCx/FastCRC/FastCRC.h \
    Packetizer/util/CRCx/FastCRC/FastCRC_cpu.h \
    Packetizer/util/CRCx/FastCRC/FastCRC_tables.h \
    Packetizer/util/CRCx/FastCRC/FastCRChw.h \
    Packetizer/util/CRCx/FastCRC/FastCRCsw.h \
    Packetizer/util/TeensyDirtySTLErrorSolution/TeensyDirtySTLErrorSolution.h \
    QCustomPlot/qcustomplot.h \
    datalogger.h \
    drew_util.h \
    filedownloader.h \
    mainwindow.h \
    mcu-vendor-id-table.h \
    serial_manager.h \
    serialportreader-async.h \
    serialportwriter-async.h \ \ \
    ui_serialComsPanel.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \ \ \
    MsgPack/.gitignore \
    MsgPack/LICENSE \
    MsgPack/MsgPack/util/ArxContainer/LICENSE \
    MsgPack/MsgPack/util/ArxContainer/README.md \
    MsgPack/MsgPack/util/ArxContainer/library.json \
    MsgPack/MsgPack/util/ArxContainer/library.properties \
    MsgPack/MsgPack/util/ArxTypeTraits/LICENSE \
    MsgPack/MsgPack/util/ArxTypeTraits/README.md \
    MsgPack/MsgPack/util/ArxTypeTraits/library.json \
    MsgPack/MsgPack/util/ArxTypeTraits/library.properties \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxContainer/LICENSE \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxContainer/README.md \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxContainer/library.json \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxContainer/library.properties \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxTypeTraits/LICENSE \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxTypeTraits/README.md \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxTypeTraits/library.json \
    MsgPack/MsgPack/util/DebugLog/DebugLog/util/ArxTypeTraits/library.properties \
    MsgPack/MsgPack/util/DebugLog/LICENSE \
    MsgPack/MsgPack/util/DebugLog/README.md \
    MsgPack/MsgPack/util/DebugLog/library.json \
    MsgPack/MsgPack/util/DebugLog/library.properties \
    MsgPack/MsgPack/util/TeensyDirtySTLErrorSolution/LICENSE \
    MsgPack/MsgPack/util/TeensyDirtySTLErrorSolution/README.md \
    MsgPack/README.md \
    MsgPack/library.json \
    MsgPack/library.properties \
    Packetizer/CMakeLists.txt \
    Packetizer/package.xml \
    Packetizer/util/ArxContainer/LICENSE \
    Packetizer/util/ArxContainer/README.md \
    Packetizer/util/ArxContainer/library.json \
    Packetizer/util/ArxContainer/library.properties \
    Packetizer/util/ArxSmartPtr/ArxSmartPtr/LICENSE_1_0.txt \
    Packetizer/util/ArxSmartPtr/LICENSE \
    Packetizer/util/ArxSmartPtr/README.md \
    Packetizer/util/ArxSmartPtr/library.json \
    Packetizer/util/ArxSmartPtr/library.properties \
    Packetizer/util/ArxTypeTraits/LICENSE \
    Packetizer/util/ArxTypeTraits/README.md \
    Packetizer/util/ArxTypeTraits/library.json \
    Packetizer/util/ArxTypeTraits/library.properties \
    Packetizer/util/CRCx/CMakeLists.txt \
    Packetizer/util/CRCx/CRCpp/LICENSE \
    Packetizer/util/CRCx/CRCpp/README.md \
    Packetizer/util/CRCx/FastCRC/LICENCE.md \
    Packetizer/util/CRCx/FastCRC/README.md \
    Packetizer/util/CRCx/FastCRC/keywords.txt \
    Packetizer/util/CRCx/LICENSE \
    Packetizer/util/CRCx/README.md \
    Packetizer/util/CRCx/library.json \
    Packetizer/util/CRCx/library.properties \
    Packetizer/util/CRCx/package.xml \
    Packetizer/util/TeensyDirtySTLErrorSolution/LICENSE \
    Packetizer/util/TeensyDirtySTLErrorSolution/README.md
