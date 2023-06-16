#include "fileSystemHelpers.hpp"

#include "gameEngine.hpp"

namespace FileSystemHelpers
{
    std::string folderNameToPath(const std::string &folder)
    {
        GameEngine &engine = GameEngine::getInstance();

        if (folder == "DEFAULT_ASSETS")
        {
            return engine.defaultAssetFolder().string();
        }
        if (folder == "PROJECT_ASSETS")
        {
            return engine.projectAssetFolder().string();
        }

        return folder;
    }
} // namespace FileSystemHelpers
