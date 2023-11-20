#include<stdio.h>
#include<stdlib.h>

typedef struct goals_steps
{
    int achieved_steps;
    int total_steps;
    struct goals_steps *next;

}GOALS_S;

typedef struct goals_hrs
{
    int achieved_hrs;
    int total_hrs;
    struct goals_hrs *next;

}GOALS_H;

typedef struct date
{
    int day;
    int month;
    int year;
}DATE;

typedef struct workout_log
{
    DATE date;
    char workout_name[30];
    int hrs;
    
}LOG;

typedef struct nutrition
{
    char breakfast[30];
    char lunch[30];
    char dinner[30];
    double calories;

}FOOD;

typedef struct health_metric
{
    double curr_weight;
    double curr_height;
    double curr_bmi;
    char gender;
    int age;
    char name[20];
}HM;

typedef struct tracking_parameters
{
    int height;
    int weight;
    int steps;
    int water;
    int calories;
    DATE date;

}TRACK;

typedef struct challenges
{
    char chall_name[20];
}CHALL;

int main()
{
    char name[20];
    printf("Please enter your name - "); scanf("%s", name);

    printf("\t\t-------------------------\n\t\t\tWelcome %s !!\n", name);

    int level;
    printf("Choose Difficulty Level - \n1.Beginner \n2.Intermidiate \n3.Advanced\n ~"); scanf("%d", &level);

    switch (level)
    {
    case 1:
        printf("Here in beginner");
        break;

    case 2:
        printf("Here in Intermidiate");
        break;

    case 3:
        printf("Here in Advanced");
        break;

    default:
        printf("Enter Valid Output");
        break;
    }    
}


int main()
{
    char name[20];
    printf("Please enter your name - "); scanf("%s", name);

    printf("\t\t-------------------------\n\t\t\tWelcome %s !!\n", name);

    int level;
    printf("Choose Difficulty Level - \n1.Beginner \n2.Intermidiate \n3.Advanced\n ~"); scanf("%d", &level);

    switch (level)
    {
    case 1:
        printf("Here in beginner");
        break;

    case 2:
        printf("Here in Intermidiate");
        break;

    case 3:
        printf("Here in Advanced");
        break;

    default:
        printf("Enter Valid Output");
        break;
    }    
}
