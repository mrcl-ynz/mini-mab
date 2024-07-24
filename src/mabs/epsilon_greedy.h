#include <algorithm>
#include <cstdint>
#include <functional>
#include <vector>

class EpsilonGreedyMAB {
public:
  EpsilonGreedyMAB(uint32_t actions, float epsilon) : epsilon(epsilon) {
    Q = std::vector<float>(actions, 0);
    N = std::vector<uint32_t>(actions, 0);
  }

  uint32_t getBestAction() {
    auto max = std::max_element(Q.begin(), Q.end());

    return std::distance(Q.begin(), max);
  }

  void train(uint32_t iters, std::function<float(uint32_t)> reward_function) {
    for (uint32_t i = 0; i < iters; ++i) {
      uint32_t action = selectAction();
      updateRewards(action, reward_function(action));
    }
  }

private:
  std::vector<float> Q;
  std::vector<uint32_t> N;
  float epsilon;

  void updateRewards(uint32_t action, float reward) {
    N[action]++;
    Q[action] += (reward - Q[action]) / N[action];
  }

  uint32_t selectAction() {
    float r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

    return (r < epsilon) ? std::rand() % N.size() : getBestAction();
  }
};
