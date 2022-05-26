#pragma once
#ifndef HT_SERIAL_MSGPACK_H
#define HT_SERIAL_MSGPACK_H

#include "MsgPack/MsgPack/util/DebugLog/DebugLog.h"
#ifdef MSGPACK_DEBUGLOG_ENABLE
#include "MsgPack/util/DebugLog/DebugLogEnable.h"
#else
#include "MsgPack/MsgPack/util/DebugLog/DebugLogDisable.h"
#endif

#include "MsgPack/MsgPack/Types.h"
#include "MsgPack/MsgPack/Packer.h"
#include "MsgPack/MsgPack/Unpacker.h"
#include "MsgPack/MsgPack/Utility.h"

namespace MsgPack = arduino::msgpack;

#include "MsgPack/MsgPack/util/DebugLog/DebugLogRestoreState.h"

#endif  // ARDUINOMSGPACK_H
