pid_estabilidade::pid_estabilidade(int pin_motor_a, int pin_motor_b)
{
	pinMode(pin_motor_a, output);
	pinMode(pin_motor_b, output);
	motor_a = pin_motor_a;
	motor_b = pin_motor_b;
}

void pid_estabilidade::controle_acl(float acl, float sp_acl, int pwm_ma, int pwm_mb, unsigned long dt){
	float p = 0, i = 0, d = 0, erro = 0, pid = 0;
	int retorno;
	
	erro = sp_acl - acl;
	p = cp_acl * erro;
	i += (ci_acl * erro) * dt;
	d = (erro * cd_acl) / dt;
	pid = p + i + d;
	
	if(pid >= 0){
		digitalWrite(motor_a, high);
		digitalWrite(motor_b, high);
	}
	else{
		digitalWrite(motor_a, low);
		digitalWrite(motor_b, low);
	}
}

void pid_estabilidade::controle_gir(float gir, float sp_gir, int pwm, int pwm_ma, int pwm_mb, unsigned long dt){
	
}
