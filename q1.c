#include <stdio.h>

double calculaterepayment(double loan, double interestrate, int years, double installment, double extrapayment);

int main() {
    double loan=100000;
    double interestrate=0.05; 
    int years=3;
    double installment=35000;
    double extrapayment=0;

    double totalrepayment=calculaterepayment(loan, interestrate, years, installment, extrapayment);

    printf("Total repayment over %d years = %.2f\n", years, totalrepayment);

    return 0;
}

double calculaterepayment(double loan, double interestrate, int years, double installment, double extrapayment) {
    if (loan <= 0 || years == 0) {
        return 0; 
    }

    double interestamount = loan * interestrate; 
    double remainingloan = loan + interestamount - installment - extrapayment;



    printf("Year %d: Remaining loan = %.2f\n", 4 - years, remainingloan);

    return (installment + extrapayment + interestamount) + 
           calculaterepayment(remainingloan, interestrate, years - 1, installment, extrapayment);
}
