//banking management system using Trees (BST)
#include<stdio.h>
#include<stdlib.h>
//#include<conio.h>
#include<string.h>

typedef struct transactions
{
    int trans;
    struct transactions *next;

}TRANS;

typedef struct account
{
    long long int acc_no;
    int cust_id;
    int balance;
    char name[20];
    long long int phone;
    TRANS *head;
    TRANS *tail;
    struct account *left;
    struct account *right;

}ACC;

typedef struct tree
{
    ACC *root;

}TREE;

typedef struct admin
{
    char ad_name[10];
    char ad_id[7];

}ADMIN;

void tree_init(TREE *pt);
ACC* create_acc(long long int acc_no,int cid,char name[],long long int phone,int bal);//insert node is adding a new acc_no that time give bal=1000 explicitly
void display_details(ACC *p);//details without trans
void load_cust_info(TREE *pt,FILE *cust);
void load_trans_info(TREE *pt,FILE *trans);
void load_admin_info(ADMIN ad[],FILE *admin);
void add_transactions(ACC *account, int amt);
void insert(TREE *pt,long long int acc_no,int cid,char name[],long long int ph,int bal,int load);
ACC* searchI(TREE *pt,long long int ele);
void inorderTraversal(TREE *pt);
void inorder(ACC *p);

int main()
{
    FILE* fp_cust = fopen("Customer.csv", "r");
    FILE* fp_trans = fopen("transactions.csv", "r");
    FILE* fp_admin = fopen("Admin.csv", "r");
    //getchar();
    TREE tobj;
    //memset(&tobj, 0, sizeof(TREE));
    tree_init(&tobj);
    ADMIN *admin=calloc(3,sizeof(ADMIN));
    //ADMIN *admin=malloc(3*sizeof(ADMIN));



    if ((!fp_cust)||(!fp_trans)||(!fp_admin))
        printf("Can't open file\n");
    else
    {
        printf("all files opened\n");
        load_cust_info(&tobj,fp_cust);//wurks lessgoooo
        load_trans_info(&tobj, fp_trans);
        load_admin_info(admin,fp_admin);//works!!

        fclose(fp_admin);
        fclose(fp_cust);
        fclose(fp_trans);
        //selecting between admin or customer
        
        // printf("Customer login(0) or Admin login(1)?: ");
        // int log_who;
        // scanf("%d",&log_who);
        // int logout=0;
        // while(log_who==0)
        // {
        //     int choice,acc,cid;
        //     printf("Please Enter Account Number: ");
        //     scanf("%lld",&acc);
        //     printf("Please Enter Customer ID: ");
        //     scanf("%lld",&cid);
        //     ACC *p=searchI(&tobj,acc);
        //     if(p!=NULL)
        //     {
        //         if(cid==p->cust_id)
        //         {
        //             int op;
        //             printf("Welcome %s!\n",p->name);
        //             do
        //             {
        //                 printf("1.See your details\n2.Transfer money\n3.Check Balance\n");
        //                 printf("What would you like to do?: ");
        //                 scanf("%d",&op);
        //                 switch (op)
        //                 {
        //                     case 1:
        //                         break;
        //                     case 2:
        //                         break;
        //                     case 3:
        //                         break;
                            
        //                     default:
        //                         break;
        //                 }
        //             } while (!logout);
        //         }
        //     }
        //     else
        //     {
        //         printf("Account Number is incorrect.");
        //     }
        // } 
        
    }

    inorderTraversal(&tobj); //works
}

void tree_init(TREE *pt)
{
    pt->root=NULL;
}

ACC* create_acc(long long int acc_no,int cid,char name[],long long int phone,int bal)
{
    ACC* newacc=malloc(sizeof(ACC));
    newacc->acc_no=acc_no;
    newacc->cust_id=cid;
    strcpy(newacc->name,name);
    newacc->phone=phone;
    newacc->balance=bal;
    newacc->head=NULL;
    newacc->tail=NULL;
    newacc->left=NULL;
    newacc->right=NULL;
    return newacc;

}

void load_cust_info(TREE *pt,FILE *cust)
{
    int row = 0,column;
    char buffer[1024],name[20];
    int cid,balance;
    long long int acc_no,ph;

 
        while (fgets(buffer,1024, cust))
        {
            column = 0;
            row++;
 
            // To avoid printing of column headers
            if (row == 1)
                continue;
 
            // Splitting the data
            const char* value = strtok(buffer, ",");
 
            while (value) {
                // acc_no number
                if (column == 0) {
                    acc_no=atoll(value);
                    value = strtok(NULL, ",");
                    column++;
                }
 
                // customer id
                if (column == 1) {
                    cid=atoi(value);
                    value = strtok(NULL, ",");
                    column++;
                }
 
                // name
                if (column == 2) {
                    strcpy(name,value);
                    value = strtok(NULL, ",");
                    column++;
                }

                //Phone
                if (column == 3) {
                    ph=atoll(value);
                    value = strtok(NULL, ",");
                    column++;
                }

                //balance
                if (column == 4) {
                    balance=atoi(value);
                    value = strtok(NULL, ",");
                }
 
                insert(pt,acc_no,cid,name,ph,balance,1);
                
                
            }
        }
}

void add_transactions(ACC *account, int amt)
{
    TRANS *newNode = malloc(sizeof(TRANS));
    newNode->trans = amt;
    newNode->next = NULL;

   if (account->head == NULL)
    {
        account->head = newNode;
        account->tail = newNode;
    }
    else
    {
        account->tail->next = newNode;
        account->tail = newNode;
    }
}

void load_trans_info(TREE *pt, FILE *trans)
{
    // format - <account send from> <-ve amt>
    //          <amount send to> <+ve amt>
    printf("hi");
    char buffer[1024];
    int row = 0;
    while (fgets(buffer, 1024, trans)) // reads line
    {
        ACC *acc = NULL;
        row = 0;
        const char *value = strtok(buffer, ",");
        while (value)
        {
                if (row == 0) // reads acc id
                {
                    long long int acc_no = atoll(value);
                    acc = searchI(pt, acc_no);
                    row++;
                }
                else // reads transactions
                {
                    int transa = atoi(value);
                    add_transactions(acc, transa);
                    row++;
                }
                value = strtok(NULL, ",");
        }
        printf("%lld - ", acc->acc_no);
    }
}

void load_admin_info(ADMIN ad[],FILE *admin)
{
    int row = -2,column;
    char buffer[1024],name[20],id[10];

 
        while (fgets(buffer,1024, admin))
        {
            column = 0;
            row++;
 
            // To avoid printing of column headers
            if (row == -1)
                continue;
 
            // Splitting the data
            const char* value = strtok(buffer, ",");
            
 
            while (value) {
                // name
                if (column == 0) {
                    strcpy(ad[row].ad_name,value);
                    value = strtok(NULL, ",");
                    column++;
                }
 
                // admin id
                if (column == 1) {
                    strcpy(ad[row].ad_id,value);
                    value = strtok(NULL, ",");
                    column++;
                }  
            }

        }
    //printf("HO");

}



//adding new acc_no give bal as 1000 in arg
void display_details(ACC *p)
{
    printf("Account Number:%lld\n",p->acc_no);
    printf("Customer ID:%d\n",p->cust_id);
    printf("Customer Name:%s\n",p->name);
    printf("Phone No:%lld\n",p->phone);
    printf("Balance:%d\n",p->balance);

    TRANS *x;
    printf("Transactions: ");
    for (x = p->head; x != NULL; x = x->next)
        printf("%d ", x->trans);
    printf("\n\n");

}
void insert(TREE *pt,long long int acc,int cid,char name[],long long int ph,int bal,int load)
{
	
    if (!load)
    {
        bal=1000;
        //for new acc condition
    }
    ACC *newacc=create_acc(acc,cid,name,ph,bal);
	if(pt->root==NULL)
		pt->root=newacc;
	else
	{
		ACC *p=pt->root;
		ACC *q=NULL;
		
		while(p!=NULL)
		{
			q=p;
			if(newacc->acc_no < p->acc_no)
				p=p->left;
			else
				p=p->right;
		}
		if(newacc->acc_no < q->acc_no)
			q->left=newacc;
		else
			q->right=newacc;
	}	
}

ACC* searchI(TREE *pt,long long int ele)
{
	ACC *p=pt->root;
	
	while(p!=NULL)
	{
		if(ele == p->acc_no)
			return p;
		else if(ele < p->acc_no)
			p=p->left;
		else 
			p=p->right;
	}
	return NULL;
}

void inorder(ACC *p)
{
	if(p!=NULL)
	{
		inorder(p->left);
		display_details(p);
		inorder(p->right);
	}
}
void inorderTraversal(TREE *pt)
{
	if(pt->root!=NULL)
		inorder(pt->root);
	else
		printf("Empty Tree\n");
}
