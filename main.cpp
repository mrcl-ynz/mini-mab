#include "mab.cpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <vector>

struct SlotMachine {
  float winningChance;

  SlotMachine(float p) : winningChance(p) {}

  int32_t play() {
    float r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

    return (r < winningChance) ? 1 : -1;
  }
};

const uint32_t actions = 100;
const uint32_t iters = 100000;

int main() {
  std::srand(std::time(nullptr));

  std::vector<SlotMachine> machines = {};
  // Generar una máquina tragamoneda por cada acción posible.
  for (uint32_t i = 0; i < actions; ++i) {
    auto p = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    machines.push_back(SlotMachine(p));
  }

  MultiArmedBandit bandit = {actions, 0.9};

  for (uint32_t i = 0; i < iters; ++i) {
    auto action = bandit.selectAction();
    auto reward = machines[action].play();

    bandit.updateRewards(action, reward);
  }

  // Determinar la máquina con mejor recompensa real.
  auto max_it = std::max_element(machines.begin(), machines.end(),
                                 [](SlotMachine a, SlotMachine b) {
                                   return a.winningChance < b.winningChance;
                                 });
  uint32_t best = std::distance(machines.begin(), max_it);
  std::cout << "La máquina con mejor probabilidad de ganar es la #" << best
            << std::endl;

  // Determinar la máquina con mejor recompensa estimada
  uint32_t predicted = bandit.getBestAction();
  std::cout << "La mejor acción determinada por el MAB es jugar en la máquina #"
            << predicted << std::endl;

  // Calcular la diferencia relativa entre el estimado y el real como métrica de
  // error
  std::cout << "Error relativo: "
            << 1 - machines[predicted].winningChance /
                       machines[best].winningChance
            << std::endl;
}
