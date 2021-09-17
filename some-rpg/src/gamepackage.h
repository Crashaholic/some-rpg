#ifndef GAMEPKG_H
#define GAMEPKG_H
#include "game/serializable.h"

namespace PlatformSystem
{
    class GamePackage : Game::Serializable
    {
        public:
            // semi soft-coding the directories, might be useful?

            path dataDirectory = "data";

            path dataFragBiomes = "biomes";
            path dataFragEntities = "entities";
            path dataFragItems = "items";
            path dataFragItemFx = "itemEffects";
            path dataFragAddons = "addons";
            path dataFragPkgMain = "gremspo";



            // idea: have a whole thing where the base game is also a package that
            // you can get data from.
            // using c++17's filesystem, be able to read a directory and get the files in there.

    };
}
#endif // GAMEPKG_H
