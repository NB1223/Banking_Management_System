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

void tree_init(TREE *pt)
{
    pt->root = NULL;
}

ACC* create_acc(long long int acc_no,int cid,char name[],long long int phone,int bal)//insert node is adding a new acc_no that time give bal=1000 explicitly
{
    ACC *newacc = malloc(sizeof(ACC));
    newacc->acc_no = acc_no;
    newacc->cust_id = cid;
    strcpy(newacc->name, name);
    newacc->phone = phone;
    newacc->balance = bal;
    newacc->head = NULL;
    newacc->tail = NULL;
    newacc->left = NULL;
    newacc->right = NULL;
    return newacc;
}

void display_details(ACC *p)//details without trans
{
    printf("\n\nAccount Number:%lld\n", p->acc_no);
    printf("Customer ID:%d\n", p->cust_id);
    printf("Customer Name:%s\n", p->name);
    printf("Phone No:%lld\n", p->phone);
    printf("Balance:%d\n", p->balance);

    TRANS *x;
    printf("Transactions: ");
    for (x = p->head; x != NULL; x = x->next)
        printf("%d ", x->trans);
    printf("\n");
}

void load_cust_info(TREE *pt,FILE *cust);
void load_trans_info(TREE *pt,FILE *trans);
void load_admin_info(ADMIN ad[],FILE *admin);
void add_transactions(ACC *account, int amt);
void insert(TREE *pt,long long int acc_no,int cid,char name[],long long int ph,int bal,int load);
ACC* searchI(TREE *pt,long long int ele);
void inorderTraversal(TREE *pt);
void inorder(ACC *p);

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

void add_cust(TREE *pt,FILE *fp_cust)
{
    char name[20];
    long long int n1,lan=10000000000,uan=9999999999,phone;
    int n2,lci=1000000,uci=9999999,bal=1000;
    
    printf("\nYour Account Number:\n");
    n1=(rand()%(uan-lan+1)+lan);
    printf("%d\n",n1);
    
    printf("\nCustomer ID:\n");
    n2=(rand()%(uci-lci+1)+lci);
    printf("%d\n",n2);

    printf("\nEnter Account Holder Name:\n");
    scanf("%s",&name);
    printf("\nEnter Mobile Number:\n");
    scanf("%lld",&phone);

    printf("\nYour Account Balance\n");
    printf("%d\n",bal);
	ACC *newacc=create_acc(n1,n2,name,phone,bal);
    
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
    printf("\nAccount created successfully\n");
    printf("\nYOUR ACCOUNT NUMBER:%d",n1);
    printf("\nCustomer ID:%d",n2);

}
ACC* deleteR(ACC *p,long long int acc_no)
{
	ACC *q=NULL;
	if(p==NULL)
		return p;
	if(acc_no < p->acc_no)
		p->left=deleteR(p->left,acc_no);
	else if(acc_no > p->acc_no)
		p->right=deleteR(p->right,acc_no);
	else if(p->left == NULL)	//Single right child or leaf ACC case
	{
		q=p->right;
		free(p);
		return q;
	}
	else if(p->right==NULL)	//Single left child case
	{
		q=p->left;
		free(p);
		return q;
	}
	else	//ACC with 2 children, Replace with inorder successor
	{
		q=p->right;
		while(q->left!=NULL)
			q=q->left;
		
		p->acc_no=q->acc_no;
		p->right=deleteR(p->right,q->acc_no);
	}
	return p;
}
void deleteACC(TREE *pt,long long int ele)
{
	pt->root=deleteR(pt->root,ele);
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

void make_transactions(TREE *pt, ACC *send_acc)
{
    int amt;
    long long int r_acc;
    printf("\nEnter Amount to be Transfered - "); scanf("%d", &amt);
    printf("Enter Account number - "); scanf("%lld", &r_acc);

    if (amt < 0 || amt > send_acc->balance)
    {
        printf("--Transaction Invalid--\n");
        return;
    }
    ACC *rec_acc = searchI(pt, r_acc);

    add_transactions(send_acc, (-amt));
    send_acc->balance -= amt;

    if (rec_acc != NULL)
    {
        add_transactions(rec_acc, amt);
        rec_acc->balance += amt;
    }

    printf("Transaction Completed\n");
    printf("%d send to %lld", amt, r_acc);
}

void load_trans_info(TREE *pt, FILE *trans)
{
    // format - <account send from> <-ve amt>
    //          <amount send to> <+ve amt>
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

void write_cust(ACC* account, FILE *fp_cust)
{
    if (account == NULL)
        return;

    fprintf(fp_cust, "%lld, %d,%s, %lld, %d\n", account->acc_no, account->cust_id, account->name, account->phone, account->balance);
    write_cust(account->left, fp_cust);
    write_cust(account->right, fp_cust);
}

void write_trans(ACC *account, FILE *fp_trans)
{
    if (account == NULL )
        return;

    fprintf(fp_trans, "%lld", account->acc_no);

    TRANS* x;
    for (x = account->head; x != NULL; x = x->next)
        fprintf(fp_trans, ", %d", x->trans);
    fprintf(fp_trans, "\n");
    write_trans(account->left, fp_trans);
    write_trans(account->right, fp_trans);
}

void write(TREE *pt)
{
    FILE *fp_cust = fopen("Customer.csv", "w");
    FILE *fp_trans = fopen("transactions.csv", "w");

    fprintf(fp_cust, "Account Number, Customer ID, Name, Phone, Balance\n");
    write_cust(pt->root, fp_cust);

    write_trans(pt->root, fp_trans);

    fclose(fp_cust);
    fclose(fp_trans);
}

int main()
{
    FILE *fp_cust = fopen("Customer.csv", "r");
    FILE *fp_trans = fopen("transactions.csv", "r");
    FILE *fp_admin = fopen("Admin.csv", "r");
    // getchar();
    TREE tobj;
    // memset(&tobj, 0, sizeof(TREE));
    tree_init(&tobj);
    ADMIN *admin = calloc(3, sizeof(ADMIN));
    // ADMIN *admin=malloc(3*sizeof(ADMIN));

    if ((!fp_cust) || (!fp_trans) || (!fp_admin))
       return 0;

        //printf("all files opened\n");
        load_cust_info(&tobj, fp_cust); // wurks lessgoooo
        load_trans_info(&tobj, fp_trans);
        load_admin_info(admin, fp_admin); // works!!

        fclose(fp_admin);
        fclose(fp_cust);
        fclose(fp_trans);
        // selecting between admin or customer

    while (1)
    {
        printf("\n\nCustomer login(0) or Admin login(1) or Customer Signup(2) or logout(-1)? : ");
        int log_who;
        scanf("%d", &log_who);
        printf("\n\n");
        int logout = 0;
        if (log_who == 0)
        {
            int choice, cid;
            int logout = 0;
            long long int acc;
            printf("Please Enter Account Number: ");
            scanf("%lld", &acc);
            printf("Please Enter Customer ID: ");
            scanf("%d", &cid);
            ACC *p = searchI(&tobj, acc);
            if (p != NULL)
            {
                if (cid == p->cust_id)
                {
                    int op;
                    printf("\n\t\t~~~~~~~~~~Welcome %s!~~~~~~~~~~", p->name);
                    do
                    {
                        printf("\n\n1.See your details\n2.Transfer money\n3.Check Balance\n4.Delete Account\n5.Logout\n");
                        printf("What would you like to do?: ");
                        scanf("%d", &op);
                        printf("\t\t--------------------------------\n");
                        switch (op)
                        {
                        case 1:
                            display_details(p);
                            break;
                        case 2:
                            make_transactions(&tobj, p);
                            break;

                        case 3:
                            printf("\nBalance - %d", p->balance);
                            break;

                        case 4:
                            printf("Deleting Acoount ......\n");
                            // nishta's delete account
				deleteACC(&tobj,acc);
                            printf("Deleted \nlOGINING OUT ");

                        default:
                            logout = 1;
                            break;
                        }
                        printf("\n\t\t--------------------------------\n");
                    } while (!logout);
                }
            }
            else
            {
                printf("Account Number is incorrect.");
            }
        }

        else if (log_who == 1)
        {
            //neha's code
        }

        else if (log_who == 2)
        {
            // nishta's create account
		add_cust(&tobj,fp_cust);
        }
        

        else if (log_who == -1)
        {
            break;
        }
        
    }

    //inorderTraversal(&tobj); // works
    write(&tobj);
    return 0;
}

// transactions
// updating
// loading
