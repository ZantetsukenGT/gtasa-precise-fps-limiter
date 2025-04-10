#pragma once

#include <fstream>
#include <string>

class Logging
{
private:
    static inline constexpr char LOG_FILE[] = ".\\PreciseFramerateLimiter.log";
    static inline bool isFirstLog = true;

    Logging() = delete;
    ~Logging() = delete;

public:
    static void WriteLine(std::string_view line)
    {
        std::ios::openmode flags;
        if (isFirstLog)
        {
            isFirstLog = false;
            flags = std::ios::out | std::ios::trunc;
        }
        else
        {
            flags = std::ios::out | std::ios::app;
        }

        std::ofstream cfgFile(LOG_FILE, flags);
        cfgFile << line << std::endl;
        cfgFile.close();
    }
};

