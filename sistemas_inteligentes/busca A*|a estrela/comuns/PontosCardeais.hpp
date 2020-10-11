/**Pontos cardeais: o agente se movimenta em uma direção apontada por um dos
 * pontos cardeais. São utilizados como parâmetros da ação ir(ponto)
*/

#ifndef C___PONTOSCARDEAIS_HPP
#define C___PONTOSCARDEAIS_HPP

#include <vector>

class PontosCardeais {
  public:
  static constexpr int N = 0;
  static constexpr int NE = 1;
  static constexpr int L = 2;
  static constexpr int SE = 3;
  static constexpr int S = 4;
  static constexpr int SO = 5;
  static constexpr int O = 6;
  static constexpr int NO = 7;

  /**Strings que correspondem as ações */
  std::vector<const char *> acao = {"N", "NE", "L", "SE", "S", "SO", "O", "NO"};

  public:
  PontosCardeais() = default;

  ~PontosCardeais() = default;
};


#endif // C___PONTOSCARDEAIS_HPP
