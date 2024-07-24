#include "mab.h"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <vector>

MultiArmedBandit::MultiArmedBandit(uint32_t actions, float epsilon)
    : epsilon(epsilon) {
  Q = std::vector<float>(actions, 0);
  N = std::vector<uint32_t>(actions, 0);
}

uint32_t MultiArmedBandit::selectAction() {
  auto r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

  return (r < epsilon) ? (std::rand() % N.size()) : getBestAction();
}

void MultiArmedBandit::updateRewards(uint32_t action, float reward) {
  N[action]++;
  Q[action] += (reward - Q[action]) / N[action];
}

uint32_t MultiArmedBandit::getBestAction() {
  auto max = std::max_element(Q.begin(), Q.end());

  return std::distance(Q.begin(), max);
}
