#include<stdio.h>
int calculatefuel(int fuel, int consumption, int recharge, int solarbonus, int planet, int totalplanets);

int main(){
	int fuel,consumption,recharge,solarbonus,totalplanets,planet=1;
	
	
	printf("enter initial fuel\n");
	scanf("%d",&fuel);
	
	printf("enter fuel consumption\n");
	scanf("%d",&consumption);
	
	printf("enter recharge amount\n");
	scanf("%d",&recharge);
	
	printf("enter solar bonus \n");
	scanf("%d",&solarbonus);
	
	printf("enter no of planets\n");
	scanf("%d",&totalplanets);
	

	
	calculatefuel( fuel,  consumption,  recharge,  solarbonus,  planet,  totalplanets);
	return 0;
	
}
int calculatefuel(int fuel, int consumption, int recharge, int solarbonus, int planet, int totalplanets){
	if (fuel<=0 ){
	return	printf("insufficient petrol\n");
		
	}
	if(planet>totalplanets){
	return	printf("visited all planets\n");
		
	}

		fuel-=consumption;
		if(planet%3==0){
			fuel+=recharge;
			}
		if (planet%4==0){
			fuel+=solarbonus;
		
		}	
		printf("planet%d:fuel remaining=%d\n",planet,fuel);
		
	return	calculatefuel(fuel, consumption, recharge, solarbonus, planet + 1, totalplanets);

	}
