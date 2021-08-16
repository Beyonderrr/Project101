#include<stdio.h>

int main()
{
    float weight, height, bmi;
    printf("Enter your weight(kg) : ");
    scanf("%f", &weight);
    printf("Enter your height(m) : ");
    scanf("%f", &height);
    bmi = weight / (height * height);
    printf("Your BMI : %.1f\n", bmi);
    if (bmi <= 18.5)
        printf("Underweight");
    else if (bmi <= 24.9)
        printf("Normal");
    else if (bmi <= 29.9)
        printf("Overweight");
    else if (bmi >= 30)
        printf("Obese");



    return 0;
}