//pino 5 controla a direção da rotação (HIGH p/ sentido horário, LOW p/ antihorário)
//pino 6 controla o passo. A cada HIGH, um passo é dado (1,8 graus)

#include "soc/gpio_reg.h"
#include "driver/gpio.h"
#include "stdint.h"
#include "driver/gptimer.h"

//função delay
void delay(int ciclos){
  for(volatile int i=0; i<=ciclos*1000; i++);
}


int n_de_pulsos;
int contador = 100;
//callback (coisa que é executada quando o alarme é disparado)
bool callback(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data)
  {
    if (contador<=n_de_pulsos){   
      gpio_set_level(6, 1);
      gpio_set_level(6, 0); 

      contador++;
    }

    else{
      gpio_set_level(6, 0);
      gpio_set_level(10, 1);//quando estiver pronto, o LED ver acende
    } //!!! por algum motivo não está funcionando!!!

    return false;
  }
//fim do callback


void app_main() {
    
  
  //#####################################
  //CONFIGURAÇÕES DO USUÁRIO 
  uint8_t volume_desejado_ml = 3; //exemplo para 3 ml
  uint8_t diametro_seringa = 2;//diâmetro do corpo/barril da seringa em cm
  uint8_t raio_da_engr = 1;//raio da engrenagem que move o êmbolo
  //#####################################
  

  float area_transv_seringa = 3.1415*((diametro_seringa/2)*(diametro_seringa/2)); //Area do circulo = 3.1415 * r² 
  
  int n_de_pulsos = volume_desejado_ml/(area_transv_seringa*0.0314)*(raio_da_engr); //demonstração da fórmula na documentação
  
  //Código para uma roda de 1 cm de raio:
  //como o motor tem um passo de 1.8 grau, e a roda tem 1 cm de raio => cada passo faz com que a ampola se mova aprox. 0.0314 cm
  //(pois 1.8 grau = 0.0314 rad, e o raio da roda é 10 [para trocar a roda, apenas multiplicar 0.0314 pelo valor do raio em cm])
  //para calcular o volume final de líquido desejado, é necessário saber o diâmetro da ampola da seringa em cm





  //início da config dos GPIOs
  gpio_reset_pin(5); //5 é o pino da direção
  gpio_reset_pin(6); //6 é o pino do step
  gpio_reset_pin(10); //7 é o pino que acende o led verde, comunicando o final

  gpio_set_direction(5, GPIO_MODE_OUTPUT);
  gpio_set_direction(6, GPIO_MODE_OUTPUT);
  gpio_set_direction(10, GPIO_MODE_OUTPUT);

  gpio_set_level(5, 1);//set da direção
  //-----------------------------fim da config dos GPIOs;



  //início da config do timer
  gptimer_config_t timer_cfg = {
      .clk_src = GPTIMER_CLK_SRC_DEFAULT,//quando upar na placa, trocar pra APB
      .resolution_hz = 1000,
      .direction = GPTIMER_COUNT_UP
  };
    
  gptimer_handle_t timer = NULL;
  gptimer_new_timer(&timer_cfg, &timer);
  //------------------------fim da config do timer



  //início da config do alarme e callback
  gptimer_alarm_config_t alarm = {
      .alarm_count = 500,
      .flags.auto_reload_on_alarm = true
  };

  //
  gptimer_set_alarm_action(timer, &alarm);

  gptimer_event_callbacks_t cbs = {
    .on_alarm = callback,
  };

  gptimer_register_event_callbacks(timer, &cbs, NULL);
    //-------------------------fim da config do alarme e callback

    
  gptimer_enable(timer);
  gptimer_start(timer); //início do timer


}

//usar o I2C com um display e interface do usuário pra proxima parte da disciplina

