
//píno 5 controla a direção da rotação (HIGH p/ sentido horário, LOW p/ antihorário)
//pino 6 controla o passo. A cada HIGH, um passo é dado (1;8 graus)

#include "soc/gpio_reg.h"
#include "stdint.h"

void app_main() {
  
  REG_WRITE(GPIO_ENABLE_REG, 1100000); //enable nos pinos 5 e 6 p/ usar como gpio 
  
  //Código para uma roda de 1 cm de raio:
  //como o motor tem um passo de 1.8 grau, e a roda tem 1 cm de raio => cada passo faz com que a ampola se mova aprox. 0.0314 cm
  //(pois 1.8 grau = 0.0314 rad, e o raio da roda é 1 [para trocar a roda, apenas multiplicar 0.314 pelo valor do raio em cm])
  //para calcular o volume final de líquido desejado, é necessário saber o diâmetro da ampola da seringa.

  
  REG_WRITE(GPIO_OUT_REG, 100000); //HIGH no pino 5 > direção no sentido horario
  


  //código feito presumindo uma ampola com 2 cm de diâmetro

  uint8_t ml = 3; //exemplo para 3 ml
  uint8_t diametro //diâmetro da seringa em ml 


  int numero_de_pulsos = 

  for 
  REG_WRITE(GPIO_OUT_REG, 1000000)

}
