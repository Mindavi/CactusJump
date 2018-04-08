#include "gtest/gtest.h"
#include "asset.h"
#include "player.h"
#include "obstacle.h"

TEST(obstacle_test, collides_with_player) {
    int16_t x_position_player = 20;
    int16_t x_position_obstacle = 20;
    int16_t asset_width = 10;
    int16_t asset_height = 10;
    Asset asset(asset_width, asset_height, nullptr);
    Player player(x_position_player, asset);
    Obstacle obstacle(asset, x_position_obstacle);
    
    ASSERT_TRUE(obstacle.CollidesWith(player));
}

TEST(obstacle_test, doesnt_collide_with_player) {
    int16_t x_position_player = 20;
    int16_t x_position_obstacle = 40;
    int16_t asset_width = 10;
    int16_t asset_height = 10;
    Asset asset(asset_width, asset_height, nullptr);
    Player player(x_position_player, asset);
    Obstacle obstacle(asset, x_position_obstacle);
    
    ASSERT_FALSE(obstacle.CollidesWith(player));
}
