// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <shooter/game_engine.h>

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

TEST_CASE("Test Enemy Initialization") {
  shooter::GameEngine game_engine_;
  game_engine_.InitializeEnemies();
  std::vector<shooter::Enemy> *enemies = game_engine_.GetAllEnemies();

  SECTION("Check Enemy Positions") {
    vec2 first_enemy_position = (*enemies)[1].GetEnemyPosition();
    vec2 second_enemy_position = (*enemies)[2].GetEnemyPosition();
    REQUIRE(first_enemy_position.x - second_enemy_position.x == 70);
  }

  SECTION("Check Enemy Vector Size") {
    REQUIRE(enemies->size() == 10);
  }

  SECTION("Check Enemy is_alive_ status") {
    int num_alive = 0;
    for (auto & enemy : *enemies) {
      if (enemy.CheckEnemyAlive()) {
        num_alive++;
      }
    }
    REQUIRE(num_alive == 10);
  }

  SECTION("Check KillEnemy()") {
    (*enemies)[1].KillEnemy();
    REQUIRE(!((*enemies)[1].CheckEnemyAlive()));
  }
}
