
//pino 5 controla a direção da rotação (HIGH p/ sentido horário, LOW p/ antihorário)
//pino 6 controla o passo. A cada HIGH, um passo é dado (1;8 graus)

#include "soc/gpio_reg.h"
#include "stdint.h"
#include "stdio.h"

void app_main() {
  
  REG_WRITE(GPIO_ENABLE_REG, 1100000); //enable nos pinos 5 e 6 p/ usar como gpio 
  
  //Código para uma roda de 1 cm de raio:
  //como o motor tem um passo de 1.8 grau, e a roda tem 1 cm de raio => cada passo faz com que a ampola se mova aprox. 0.0314 cm
  //(pois 1.8 grau = 0.0314 rad, e o raio da roda é 10 [para trocar a roda, apenas multiplicar 0.0314 pelo valor do raio em cm])
  //para calcular o volume final de líquido desejado, é necessário saber o diâmetro da ampola da seringa em cm

  
  REG_WRITE(GPIO_OUT_REG, 100000); //HIGH no pino 5 > direção no sentido horario
  


  //#####################################
  //CONFIGURAÇÕES DO USUÁRIO 
  uint8_t volume_desejado_ml = 30; //exemplo para 3 ml
  uint8_t diametro_seringa = 2;//diâmetro do corpo/barril da seringa em cm
  uint8_t raio_da_engr = 1;//raio da engrenagem que move o êmbolo
  //#####################################
  

  uint8_t area_transv_seringa = 3.1415*((diametro_seringa/2)*(diametro_seringa/2)); //Area do circulo = 3.1415 * r² 
  
  uint8_t n_de_pulsos = volume_desejado_ml/(area_transv_seringa*0.0314)*(raio_da_engr); //demonstração da fórmula na documentação




  void delay(int ciclos){
    for (volatile int i=0;i<=1000*ciclos;i++);
  }



  int injetar(int n_pulsos){
    for(volatile int i=0; i<=n_pulsos; i++){
      REG_WRITE(GPIO_OUT_W1TS_REG,1000000);
      delay(1000);
      REG_WRITE(GPIO_OUT_W1TC_REG,1000000);
      delay(1000); //pq está piscando com frequencia maior que 1Hz?

    }

    printf("Injeção Completa!");
    return(0);
  }

  injetar(n_de_pulsos);

}

//colocar uma interrupção para caso o usuário deseja abortar a injeção.
