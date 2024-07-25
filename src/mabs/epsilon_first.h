#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <vector>

/// Implementación de MAB con epsilon-first
class EpsilonFirstMAB {
public:
  EpsilonFirstMAB(uint32_t actions, float epsilon) : epsilon(epsilon) {
    Q = std::vector<float>(actions, 0);
    N = std::vector<uint32_t>(actions, 0);
  }

  uint32_t getBestAction() {
    auto max = std::max_element(Q.begin(), Q.end());

    return std::distance(Q.begin(), max);
  }

  void train(uint32_t iters, std::function<float(uint32_t)> reward_function) {
    for (uint32_t i = 0; i < iters; ++i) {
      uint32_t action = selectAction(i, iters);
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

  /// Selecciona una acción, haciendo `iters` * `epsilon` iteraciones de
  /// exploración, y el resto de explotación
  uint32_t selectAction(uint32_t i, uint32_t iters) {
    return (i < iters * epsilon) ? std::rand() % N.size() : getBestAction();
  }
};
