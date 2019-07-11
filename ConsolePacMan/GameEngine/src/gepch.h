#pragma once

// Precompiled header includes
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>

#include <chrono>
#include <thread>
#include <atomic>
#include <condition_variable>

// Including our log functions for everything
#include "GameEngine/Log.h"

#ifndef UNICODE
#error Please enable UNICODE for your compiler! VS: Project Properties -> General -> Character Set -> Use Unicode.
#endif

#ifdef GE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
