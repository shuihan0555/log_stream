// ==============================================================================
// Copyright 2021 The LatticeX Foundation
// This file is part of the Rosetta library.
//
// The Rosetta library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// The Rosetta library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with the Rosetta library. If not, see <http://www.gnu.org/licenses/>.
// ==============================================================================
#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <sstream>
#include <mutex>
#include <memory>

#define SPDLOG_LOGGER_STREAM(log, lvl) 	LogStream(log, lvl, spdlog::source_loc{__FILE__, __LINE__, __FUNCTION__}) == LogLine()

#ifndef SPDLOG_ROSETTA_LOGGER_NAME 
#define SPDLOG_ROSETTA_LOGGER_NAME "Rosetta"
#endif

#ifndef SPDLOG_ROSETTA_LOGGER_LEVEL
#define SPDLOG_ROSETTA_LOGGER_LEVEL spdlog::level::level_enum::info
#endif

// set file:line as debug version log
#if defined(DEBUG)
#ifndef SPDLOG_ROSETTA_LOGGER_PATTERN
#define SPDLOG_ROSETTA_LOGGER_PATTERN "%Y-%m-%d %H:%M:%S.%e|%^%l%$|%s:%#|%v"
#endif
#else
#ifndef SPDLOG_ROSETTA_LOGGER_PATTERN
#define SPDLOG_ROSETTA_LOGGER_PATTERN "%Y-%m-%d %H:%M:%S.%e|%^%l%$|%v"
#endif
#endif


#ifndef SPDLOG_ROSETTA_LOGGER_ASYNC_QUEUE_SIZE 
#define SPDLOG_ROSETTA_LOGGER_ASYNC_QUEUE_SIZE  32768 // 32K
#endif

#ifndef SPDLOG_ROSETTA_LOGGER_ASYNC_THREAD_SIZE 
#define SPDLOG_ROSETTA_LOGGER_ASYNC_THREAD_SIZE  2 // two threads for logger 
#endif

/* stream style for logger begin */
class LogLine 
{
	public:
		LogLine() {
		}

		template<typename T> LogLine& operator<<(const T& t) { 
			ss_ << t; 

			return *this; 
		}

		std::string str() const { 
			return ss_.str(); 
		}

	private:
		std::ostringstream ss_;
};


class LogStream 
{
	public:
		LogStream(const char* task_id, spdlog::level::level_enum lvl, spdlog::source_loc loc);
		LogStream(const std::string& task_id, spdlog::level::level_enum lvl, spdlog::source_loc loc);
		bool operator==(const LogLine& line);
		~LogStream() = default;

	private:
		std::shared_ptr<spdlog::logger> log_;
		spdlog::source_loc loc_;
		spdlog::level::level_enum lvl_;
};

#define tlog_trace_(task_id) SPDLOG_LOGGER_STREAM(task_id, spdlog::level::trace)
#define tlog_debug_(task_id) SPDLOG_LOGGER_STREAM(task_id, spdlog::level::debug)
#define tlog_audit_(task_id) SPDLOG_LOGGER_STREAM(task_id, spdlog::level::audit)
#define tlog_info_(task_id) SPDLOG_LOGGER_STREAM(task_id, spdlog::level::info)
#define tlog_warn_(task_id) SPDLOG_LOGGER_STREAM(task_id, spdlog::level::warn)
#define tlog_error_(task_id) SPDLOG_LOGGER_STREAM(task_id, spdlog::level::err)
#define tlog_fatal_(task_id) SPDLOG_LOGGER_STREAM(task_id, spdlog::level::critical)

#define log_trace tlog_trace_("")
#define log_debug tlog_debug_("")
#define log_audit tlog_audit_("")
#define log_info  tlog_info_("")
#define log_warn tlog_warn_("") 
#define log_error tlog_error_("")
#define log_fatal tlog_fatal_("")

#define tlog_trace tlog_trace_(context_->TASK_ID)
#define tlog_debug tlog_debug_(context_->TASK_ID)
#define tlog_audit tlog_audit_(context_->TASK_ID)
#define tlog_info  tlog_info_(context_->TASK_ID)
#define tlog_warn tlog_warn_(context_->TASK_ID) 
#define tlog_error tlog_error_(context_->TASK_ID)
#define tlog_fatal tlog_fatal_(context_->TASK_ID)

#include"logger_stream.hpp"
