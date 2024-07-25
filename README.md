# Multi-Armed Bandits

Implementaciones de Multi-Armed Bandit con tres estrategias de
exploración/explotación basadas en un parámetro $\epsilon$. Explorar consiste
en elegir de forma aleatoria una acción (brazo), mientras que explotar consiste
en elegir la acción con mayor recompensa hasta el momento.

- Epsilon-greedy: Selecciona estocásticamente una acción, donde $\epsilon$ es
  la probabilidad de explorar.
- Epsilon-first: Para un entrenamiento de $N$ iteraciones, se explora en las
  primeras $N \cdot \epsilon$ iteraciones.
- Epsilon-decreasing: Similar a epsilon-greedy, pero el parámetro $\epsilon$ va
  decreciendo con cada iteración.

En este trabajo las implementaciones de MAB se utilizan para resolver el
problema de identificación del mejor brazo (BAI). En particular, se tiene un
entorno con distintas máquinas tragamonedas con distintas posibilidades de
pago, y el trabajo del agente es encontrar la máquina donde sea más conveniente
jugar.
