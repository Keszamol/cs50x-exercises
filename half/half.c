// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, float tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    float tip_percent = get_float("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, float tip)
{
    float sum_tax = ((bill / 100) * tax);
    float sum_tax_bill = sum_tax + bill;
    float sum_tip = ((sum_tax_bill / 100) * tip);
    float sum = sum_tax_bill + sum_tip;
    float sum_half = sum / 2;

    return sum_half;
}
