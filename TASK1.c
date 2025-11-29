#include<stdio.h>

float recursion(float loan,float repay,float interest,int year,float*totalrepay){
float actualrepay=0;
if(year==0||loan<=0){
    return 1;
}

float debtwithinterest=loan+(5.0/100)*loan;

if(debtwithinterest<repay){
	actualrepay=debtwithinterest;}
	
	else actualrepay=repay;

float newloan = debtwithinterest -actualrepay ;

printf("\nYear %d: Remaining loan = %.2f\n", 4 - year,newloan);

*totalrepay+=actualrepay;
return recursion(newloan,repay,interest,year-1,totalrepay);
}


int main(){
    float loan=100000.0;
    float repay=40000.0;
    float interest;
float totalrepay=0.0;

recursion(loan,repay,interest,3,&totalrepay);
printf("\n\nTotal repayment over 3 years: %.2f\n",totalrepay);
return 0;
}
