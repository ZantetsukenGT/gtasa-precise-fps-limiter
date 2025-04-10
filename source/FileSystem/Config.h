#pragma once

#include <cstdint>

#include <fstream>
#include <string>

class Config
{
private:
    static inline constexpr char CONFIG_FILE[] = ".\\PreciseFramerateLimiter.cfg";

    Config() = delete;
    ~Config() = delete;

public:
    static inline constexpr int DEFAULT_FRAMERATE = 144;
    static inline constexpr int MINIMUM_FRAMERATE = 20;
    static inline constexpr int UNLIMITED_FRAMERATE = 0;

    static int ReadFramerateLimit()
    {
        std::ifstream cfgFile(CONFIG_FILE);
        if (!cfgFile)
        {
            return WriteFramerateLimit(DEFAULT_FRAMERATE);
        }

        std::string line;
        std::getline(cfgFile, line);
        cfgFile.close();

        int framerate;
        try
        {
            framerate = std::stoi(line);
        }
        catch (std::exception const&)
        {
            return WriteFramerateLimit(DEFAULT_FRAMERATE);
        }

        if (framerate == UNLIMITED_FRAMERATE)
        {
            return UNLIMITED_FRAMERATE;
        }

        if (framerate < MINIMUM_FRAMERATE)
        {
            return WriteFramerateLimit(DEFAULT_FRAMERATE);
        }
        return framerate;
    }

    static int WriteFramerateLimit(int value)
    {
        std::ofstream cfgFile(CONFIG_FILE, std::ios::out | std::ios::trunc);
        if (cfgFile)
        {
            cfgFile << std::to_string(value) << std::endl;
            cfgFile.close();
        }
        return value;
    }

    static int FramerateToUSecInterval(int value)
    {
        if (value == UNLIMITED_FRAMERATE) {
            return UNLIMITED_FRAMERATE;
        }

        constexpr double ONE_SECOND_IN_USEC = 1000000.0;
        double uSecInterval = ONE_SECOND_IN_USEC / (double)value;

        return (int)std::round(uSecInterval);
    }
};
