#include <stdio.h>
#include <ctype.h>

int powerfunc(int base, int times){
	int answer,i;
	answer = 1;
	i = 0;
	while(i<times){
		answer = answer * base;
		i++;
	}
	return answer;
}

double atof(char s[]){
	double val,power,exp;
	int i,sign,expsign;

	for (i = 0;isspace(s[i]);i++);

	sign = (s[i] == '-') ? -1 : 1;

	if(s[i] == '+' || s[i] == '-')
		i++;
	for(val = 0.0 ; isdigit(s[i]);i++)
		val = 10.0 * val + (s[i] - '0');
	if(s[i] == '.')
		i++;
	for(power = 1.0 ; isdigit(s[i]);i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	if(s[i] == 'e' || s[i] == 'E'){
		i++;
	}
	if(s[i] == '-'){
		expsign = -1;
		i++;
	}
	else if(s[i] == '+'){
		expsign = 1;
	}
	else{
		expsign = 1;
	}

	for(exp = 0;isdigit(s[i]);i++){
		exp = exp * 10 + (s[i] - '0');
	}
	if(expsign == -1){
		return ((sign * val / power ) / powerfunc(10,exp));
	}
	return (( sign * val / power ) * powerfunc(10,exp));
}

int main(){
	char s[100];
	scanf("%s",s);
	printf("The answer is %.10lf\n",atof(s));
}
