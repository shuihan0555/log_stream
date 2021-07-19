# 1. spdlog_stream
1. support with cpp-stream
2. support fmt print

# 2. syntax 
## 2.1 fmt
```cpp
INFO("info message for {}, {}", 1,2); // will output info message for 1, 2
```

## 2.2 stream

```cpp
log_info<<"info message for "<<1<<", "<<2;
```

# 3. logger level

name|level|description
----|-----|-----------
trace|spdlog::level::level_enum::trace|trace: 0
debug|spdlog::level::level_enum::debug|debug: 1
audit|spdlog::level::level_enum::audit|audit: 2
info|spdlog::level::level_enum::info|info: 3
warn|spdlog::level::level_enum::warn|warn: 4
error|spdlog::level::level_enum::error|error: 5
critical|spdlog::level::level_enum::critical|critical: 6
off|spdlog::level::level_enum::off|off: 7, close all logger

