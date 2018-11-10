#include <gtest/gtest.h>

#include <thread>
#include <SFML/System/Vector2.hpp>
#include "classes/System/Animation/Animation.hpp"

class TestAnimation : public Animation {

public:

    TestAnimation(): Animation(30, false) {

    }

    void animate() override {
        isStopped = true;
    }

};

TEST(AnimationTest, test_by_default_is_not_stopped) {
    TestAnimation animation;
    EXPECT_FALSE(animation.isFinished());
}

TEST(AnimationTest, test_finished_afer_animate) {
    TestAnimation animation;
    animation.animate();
    EXPECT_TRUE(animation.isFinished());
}

TEST(AnimationTest, test_finished_afer_stop) {
    TestAnimation animation;
    animation.stop();
    EXPECT_TRUE(animation.isFinished());
}

TEST(AnimationTest, test_finished_afer_time) {
    TestAnimation animation;
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    EXPECT_TRUE(animation.isFinished());
}

TEST(AnimationTest, test_finished_afer_start_callback) {
    TestAnimation animation;
    bool value = false;
    animation.setStartCallback([&value]() mutable {
        value = true;
    });
    animation.runStartCallback();
    EXPECT_TRUE(value);
}

TEST(AnimationTest, test_finished_afer_finish_callback) {
    TestAnimation animation;
    bool value = false;
    animation.setFinishCallback([&value]() mutable {
        value = true;
    });
    animation.runFinishCallback();
    EXPECT_TRUE(value);
}