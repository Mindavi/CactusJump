#include "gtest/gtest.h"
#include "asset.h"
#include "player.h"
#include "obstacle.h"

TEST(collision_test, collides_with_player) {
    int16_t x_position_player = 20;
    int16_t x_position_obstacle = 30;
    int16_t asset_width = 10;
    int16_t asset_height = 10;
    Asset asset(asset_width, asset_height, nullptr);
    Player player(x_position_player, asset);
    Obstacle obstacle(asset, x_position_obstacle);

    ASSERT_TRUE(obstacle.CollidesWith(player));
}

TEST(collision_test, doesnt_collide_with_player) {
    int16_t x_position_player = 20;
    int16_t x_position_obstacle = 31;
    int16_t asset_width = 10;
    int16_t asset_height = 10;
    Asset asset(asset_width, asset_height, nullptr);
    Player player(x_position_player, asset);
    Obstacle obstacle(asset, x_position_obstacle);

    ASSERT_FALSE(obstacle.CollidesWith(player));
}

TEST(collision_test, player_jumps_over_object) {
    int16_t x_position_player = 20;
    // distance is so that the player doesn't collide here
    int16_t x_position_obstacle = 31;
    int16_t asset_width = 10;
    int16_t asset_height = 5;
    Asset asset(asset_width, asset_height, nullptr);
    Player player(x_position_player, asset);
    Obstacle obstacle(asset, x_position_obstacle);

    // if player collided already, it's game over
    ASSERT_FALSE(obstacle.CollidesWith(player));

    player.Jump();
    player.UpdateYPosition();

    // assumption: the player velocity is 9, which is defined in the player.h file
    ASSERT_NE(0, player.GetYPosition());
    obstacle.UpdateXPosition();

    ASSERT_FALSE(obstacle.CollidesWith(player));
}

TEST(collision_test, player_behind_object) {
    int16_t x_position_player = 31;
    int16_t x_position_obstacle = 20;
    int16_t asset_width = 10;
    int16_t asset_height = 5;
    Asset asset(asset_width, asset_height, nullptr);
    Player player(x_position_player, asset);
    Obstacle obstacle(asset, x_position_obstacle);
    ASSERT_FALSE(obstacle.CollidesWith(player));
}
