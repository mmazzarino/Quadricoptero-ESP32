pid_estabilidade::pid_estabilidade(int pin_motor_a, int pin_motor_b)
{
	pinMode(pin_motor_a, output);
	pinMode(pin_motor_b, output);
	motor_a = pin_motor_a;
	motor_b = pin_motor_b;
}

int pid_estabilidade::controle_acl(float acl, float sp_acl, int pwm_ma, int pwm_mb, unsigned long dt){
	
}

int pid_estabilidade::controle_gir(float gir, float sp_gir, int pwm, int pwm_ma, int pwm_mb, unsigned long dt){
	
}
