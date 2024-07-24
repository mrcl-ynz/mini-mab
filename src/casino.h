#include <algorithm>
#include <cstdint>
#include <vector>

class Casino {
public:
  Casino(uint32_t N) {
    machines = {};
    for (uint32_t i = 0; i < N; ++i) {
      machines.push_back(SlotMachine());
    }
  }

  int32_t eval_action(uint32_t action) { return machines[action].play(); }

  float getWinningChance(uint32_t i) { return machines[i].winningChance; }

  uint32_t getOptimal() {
    auto comp = [](auto a, auto b) -> bool {
      return a.winningChance < b.winningChance;
    };

    auto max = std::max_element(machines.begin(), machines.end(), comp);

    return std::distance(machines.begin(), max);
  }

private:
  struct SlotMachine {
    float winningChance;

    SlotMachine()
        : winningChance(static_cast<float>(std::rand()) /
                        static_cast<float>(RAND_MAX)) {}

    int32_t play() {
      float r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

      return (r < winningChance) ? 1 : -1;
    }
  };

  std::vector<SlotMachine> machines;
};
