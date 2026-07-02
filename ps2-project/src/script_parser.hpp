/**
 * @file script_parser.hpp
 * @brief Dynamic disc script parser streaming data from cdrom0:\\ to prevent 32MB Main RAM overflow.
 */

#ifndef SEVENTH_VOW_SCRIPT_PARSER_HPP
#define SEVENTH_VOW_SCRIPT_PARSER_HPP

#include <tyra.h>
#include <vector>
#include <string>

namespace TheSeventhVow {

struct ZoneEntity {
    std::string type;
    float posX, posY, posZ;
    int triggerId;
    std::string assetPath;
};

struct ZoneMetadata {
    std::string regionName;
    std::string zoneTitle;
    int sectorLBA;
    std::string bgmPath;
    float fogDensity;
};

struct ZoneScriptData {
    ZoneMetadata metadata;
    std::vector<ZoneEntity> entities;
    std::vector<std::string> dialogues;
    std::vector<std::string> scriptCommands;
};

class ScriptParser {
public:
    ScriptParser();
    ~ScriptParser();

    /**
     * @brief Streams dynamic zones data from cdrom0:\\ files.
     * @param filepath Virtual/physical location on optical disc.
     * @return Fully parsed runtime structure without rebuilding binary.
     */
    ZoneScriptData loadZoneScript(const char* filepath);

    /**
     * @brief Check and execute raw SIF commands streamed off optical tracks.
     */
    void parseStreamingCommand(const std::string& commandLine);
};

} // namespace TheSeventhVow

#endif // SEVENTH_VOW_SCRIPT_PARSER_HPP
