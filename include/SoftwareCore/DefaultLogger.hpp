#pragma once

#ifndef DefaultLogger

#include <SoftwareCore/Singleton.hpp>
#include <SoftwareCore/Logger.hpp>

#define DefaultLogger ::Core::Singleton<::Core::Logger>::GetInstance()

#endif