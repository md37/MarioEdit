#include <gtest/gtest.h>

#include "classes/Scene/Tile/TileRegistry.hpp"
#include "classes/Scene/Tile.hpp"

TEST(TileRegistryTest, test_get_dynamic_tiles_but_no_tiles) {
    TileRegistry::clear();

    ASSERT_EQ(0, TileRegistry::getDynamicTiles().size());
}

TEST(TileRegistryTest, test_get_dynamic_tiles_but_one_tile) {
    TileRegistry::clear();

    sf::Sprite sprite;
    auto tile = std::make_shared<DynamicTile>(sprite, TileConfig());

    TileRegistry::registerTile(tile);
    ASSERT_EQ(1, TileRegistry::getDynamicTiles().size());
}

TEST(TileRegistryTest, test_get_dynamic_tiles_but_two_tiles) {
    TileRegistry::clear();

    for (int i=0; i<2; i++) {
        sf::Sprite sprite;
        auto tile = std::make_shared<DynamicTile>(sprite, TileConfig());
        TileRegistry::registerTile(tile);
    }

    ASSERT_EQ(2, TileRegistry::getDynamicTiles().size());
}