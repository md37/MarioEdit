#include <gtest/gtest.h>

#include "classes/Editor/ObjectRegistry.hpp"
#include "classes/Editor/Tile.hpp"

TEST(ObjectRegistryTest, test_get_dynamic_tiles_but_no_tiles) {
    ObjectRegistry::clear();

    ASSERT_EQ(0, ObjectRegistry::getDynamicTiles().size());
}

TEST(ObjectRegistryTest, test_get_dynamic_tiles_but_one_tile) {
    ObjectRegistry::clear();

    sf::Sprite sprite;
    auto tile = std::make_shared<DynamicTile>(sprite, TileConfig());

    ObjectRegistry::registerTile(tile);
    ASSERT_EQ(1, ObjectRegistry::getDynamicTiles().size());
}

TEST(ObjectRegistryTest, test_get_dynamic_tiles_but_two_tiles) {
    ObjectRegistry::clear();

    for (int i=0; i<2; i++) {
        sf::Sprite sprite;
        auto tile = std::make_shared<DynamicTile>(sprite, TileConfig());
        ObjectRegistry::registerTile(tile);
    }

    ASSERT_EQ(2, ObjectRegistry::getDynamicTiles().size());
}