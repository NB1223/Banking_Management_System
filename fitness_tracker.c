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

typedef struct stack
{
    GOALS_H *top_hrs;
    GOALS_S *top_steps;

}STACK;

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
    int hrs;
    struct challenges *next;
}CHALL;

typedef struct list
{
	LOG *head_log;
    FOOD *head_food;
    TRACK *head_track;
    CHALL *head_chall;

}LIST;

void init_stack(STACK *ps)
{
    ps->top_hrs=NULL;
    ps->top_steps=NULL;
}

void init_date(DATE *dt)
{
    dt->day=0;
    dt->month=0;
    dt->year=0;
}

void init_list(LIST *pl)
{
	pl->head_log=NULL;
	pl->head_food=NULL;
	pl->head_track=NULL;
	pl->head_chall=NULL;
}

void init_hm(HM *hm)
{
    hm->age=0;
    hm->curr_bmi=0;
    hm->curr_height=0;
    hm->curr_weight=0;
    hm->gender='\0';
}

void init_chall(CHALL *chall)
{
    chall->hrs=0;
    chall->next=NULL;
}


int main()
{
    char name[20];
    STACK sobj;
    LIST obj;
    DATE dobj;
    HM hobj;
    CHALL cobj;

    init_stack(&sobj);
    init_list(&obj);
    init_date(&dobj);
    init_hm(&hobj);
    init_chall(&cobj);


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
