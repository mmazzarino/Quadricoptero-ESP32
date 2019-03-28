#include <Arduino.h>
#define cp_acl                //constantes 
#define cp_gir
#define ci_acl
#define ci_gir
#define cd_acl
#define cd_gir 



class pid_estabilidade
{ 
  
public:
    pid_estabilidade(int pin_motor_a, int pin_motor_b); //construtor
    
    void controle_acl(float acl, float sp_acl, int pwm_ma, int pwm_mb, unsigned long dt);
    
    void controle_gir(float gir, float sp_gir, int pwm_ma, int pwm_mb, unsigned long dt);
  
private:
    float set_point;
    float vlr_mpu;
    int motor_a, motor_b;
};
