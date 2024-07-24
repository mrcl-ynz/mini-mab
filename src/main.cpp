#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "mabs/epsilon_decreasing.h"
#include "mabs/epsilon_first.h"
#include "mabs/epsilon_greedy.h"

#include "casino.h"

constexpr uint32_t actions = 1000;
constexpr uint32_t iters = 10000;

int main() {
  std::srand(std::time(nullptr));

  Casino env = Casino(actions);
  auto reward_function = [&env](uint32_t action) {
    return static_cast<float>(env.eval_action(action));
  };

  EpsilonGreedyMAB agent1 = {actions, 0.9};
  agent1.train(iters, reward_function);

  float predicted = env.getWinningChance(agent1.getBestAction());
  float real = env.getWinningChance(env.getOptimal());
  std::cout << "Error relativo (epsilon greedy): " << (real - predicted) / real
            << std::endl;

  EpsilonFirstMAB agent2 = {actions, 0.9};
  agent2.train(iters, reward_function);

  predicted = env.getWinningChance(agent2.getBestAction());
  real = env.getWinningChance(env.getOptimal());
  std::cout << "Error relativo (epsilon first): " << (real - predicted) / real
            << std::endl;

  EpsilonFirstMAB agent3 = {actions, 0.9};
  agent3.train(iters, reward_function);

  predicted = env.getWinningChance(agent3.getBestAction());
  real = env.getWinningChance(env.getOptimal());
  std::cout << "Error relativo (epsilon decreasing): "
            << (real - predicted) / real << std::endl;
}
