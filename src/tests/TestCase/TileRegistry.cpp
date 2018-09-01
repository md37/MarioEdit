#include <gtest/gtest.h>

#include "classes/Scene/Tile/SceneRegistry.hpp"
#include "classes/Scene/Tile.hpp"

TEST(TileRegistryTest, test_get_dynamic_tiles_but_no_tiles) {
    SceneRegistry::clear();

    ASSERT_EQ(0, SceneRegistry::getDynamicTiles().size());
}

TEST(TileRegistryTest, test_get_dynamic_tiles_but_one_tile) {
    SceneRegistry::clear();

    sf::Sprite sprite;
    auto tile = std::make_shared<DynamicTile>(sprite, TileConfig());

    SceneRegistry::registerTile(tile);
    ASSERT_EQ(1, SceneRegistry::getDynamicTiles().size());
}

TEST(TileRegistryTest, test_get_dynamic_tiles_but_two_tiles) {
    SceneRegistry::clear();

    for (int i=0; i<2; i++) {
        sf::Sprite sprite;
        auto tile = std::make_shared<DynamicTile>(sprite, TileConfig());
        SceneRegistry::registerTile(tile);
    }

    ASSERT_EQ(2, SceneRegistry::getDynamicTiles().size());
}