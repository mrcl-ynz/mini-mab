#include <cstdint>
#include <vector>

/// Implementación simple de MAB utilizando la estrategia epsilon-greedy
class MultiArmedBandit {
public:
  /**
   * Inicializa un MAB.
   *
   * @param K Cantidad de brazos.
   * @param epsilon Coeficiente que determina exploración vs explotación.
   */
  MultiArmedBandit(uint32_t, float);

  /// Entrega el indice de la acción con mayor recompensa esperada.
  uint32_t getBestAction();

  /**
   * Selecciona una acción (brazo) para ejecutar. Eligiendo si explorar (elegir
   * aleatoriamente) o explotar (seleccionar el brazo con mejor recompensa
   * conocida) en base a epsilon.
   *
   * @returns indice de la acción a tomar.
   */
  uint32_t selectAction();

  /**
   * Actualiza los parámetros internos al recibir la recompensa para una acción.
   *
   * @param action acción realizada.
   * @param reward recompensa asociada a la acción.
   */
  void updateRewards(uint32_t, float);

private:
  /// Estimado del premio en promedio para cada brazo.
  std::vector<float> Q;
  /// Cantidad de veces que se ha escogido cada brazo.
  std::vector<uint32_t> N;

  float epsilon;
};
