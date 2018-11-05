#include <gtest/gtest.h>

#include "classes/System/Collision.hpp"

sf::Vector2f point = {200.0f, 200.0f};
float width = 100.0f;
float height = 100.0f;
sf::Rect<float> first(point.x, point.y, width, height);

TEST(CollisionTest, test_dont_collide_from_top) {
    sf::Rect<float> second(point.x, point.y-height-20, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::None, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_top_on_bound) {
    sf::Rect<float> second(point.x, point.y-height, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Top, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_top_inside) {
    sf::Rect<float> second(point.x, point.y-height+20, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Top, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_dont_collide_from_left) {
    sf::Rect<float> second(point.x-width-20, point.y, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::None, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_left_on_bound) {
    sf::Rect<float> second(point.x-width, point.y, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Left, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_left_inside) {
    sf::Rect<float> second(point.x-width+20, point.y, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Left, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_dont_collide_from_bottom) {
    sf::Rect<float> second(point.x, point.y+height+20, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::None, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_bottom_on_bound) {
    sf::Rect<float> second(point.x, point.y+height, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Bottom, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_bottom_inside) {
    sf::Rect<float> second(point.x, point.y+height-20, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Bottom, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_dont_collide_from_right) {
    sf::Rect<float> second(point.x+width+20, point.y, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::None, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_right_on_bound) {
    sf::Rect<float> second(point.x+width, point.y, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Right, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_right_inside) {
    sf::Rect<float> second(point.x+width-20, point.y, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Right, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_top_left_more_top_than_left) {
    sf::Rect<float> second(point.x-width+20, point.y-height+30, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Left, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_top_right_more_top_than_right) {
    sf::Rect<float> second(point.x+width-20, point.y-height+30, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Right, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_left_top_more_left_than_top) {
    sf::Rect<float> second(point.x-width+30, point.y-height+20, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Top, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_left_bottom_more_left_than_bottom) {
    sf::Rect<float> second(point.x-width+30, point.y+height-20, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Bottom, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_bottom_right_more_bottom_than_right) {
    sf::Rect<float> second(point.x+width-20, point.y+height-30, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Right, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_bottom_left_more_bottom_than_left) {
    sf::Rect<float> second(point.x-width+20, point.y+height-30, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Left, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_right_bottom_more_right_than_bottom) {
    sf::Rect<float> second(point.x+width-30, point.y+height-20, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Bottom, collisionDetect.checkCollision(second));
}

TEST(CollisionTest, test_collide_from_right_top_more_right_than_top) {
    sf::Rect<float> second(point.x+width-30, point.y-height+20, width, height);

    Collision collisionDetect(first);
    ASSERT_EQ(Collision::Direction::Top, collisionDetect.checkCollision(second));
}