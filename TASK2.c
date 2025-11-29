#include<stdio.h>
int fuelcalculation(float o,float c,float r,float s,float p,float t){
float fuel;
	if(p>t){
		printf("The spacecraft successfully landed in 9 planets and the fuel remaining is %f",fuel);	
	
		return 1;
		
	}
	 fuel=o-c+r;
	 
	if((int)p%4==0){
		
		fuel=fuel+s;
	}
	printf("Planet %d: Fuel Remaining = %.2f\n", (int)p,fuel);
	if(fuel<=0){
		printf("The fuel burns out only %.1f planet the space craft landed successfully",p);
		return 0;
	}
	
	return fuelcalculation(fuel,c,r,s,p+1,t);
	
}

int main(){
	float originalfuel,consumption=25.0;
	float solarbonus=25.0,plants=1.0,Totalplants=9.0,recharge=10.0;
	printf("How many fuel you are fuelling to spacecraft:");
	scanf("%f",&originalfuel);
	
	fuelcalculation(originalfuel,consumption,recharge,solarbonus,plants,Totalplants);
	return 0;
	
}
