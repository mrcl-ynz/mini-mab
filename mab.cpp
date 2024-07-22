#include "mab.h"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <vector>

MultiArmedBandit::MultiArmedBandit(uint32_t K, float epsilon)
    : epsilon(epsilon) {
  Q = std::vector<float>(K, 0);
  N = std::vector<uint32_t>(K, 0);
}

uint32_t MultiArmedBandit::selectAction() {
  auto r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

  return (r < epsilon) ? (std::rand() % N.size()) : getBestAction();
}

void MultiArmedBandit::updateRewards(uint32_t action, float reward) {
  N[action] += 1;
  Q[action] += ((reward - Q[action]) / N[action]);
}

uint32_t MultiArmedBandit::getBestAction() {
  auto max = std::max_element(Q.begin(), Q.end());

  return std::distance(Q.begin(), max);
}
