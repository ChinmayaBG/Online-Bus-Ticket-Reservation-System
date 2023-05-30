#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
int id,quan;
char from[20],to[20],date[10];
float mrp;
struct node *next;
}NODE;
void menu(NODE*);
void owner(NODE*);
void customer(NODE*);
NODE* add_route(NODE*);
void mod_route(NODE*);
NODE* del_route(NODE*);
void bill(NODE*);
void display(NODE*);
NODE* search(NODE*);
NODE* search2(NODE*,int);
int updater(int,int);
void file(NODE*);
NODE* nodes(NODE*);
NODE* add_route2(NODE*,int,int,char*,char*,char*,float);
void menu(NODE *first)
{
int choice;
char username[25],password[25];
FILE *fp;
while(1)
{
printf("\t\t\t\t------------------------------\n");
printf("\t\t\t\t BUS TICKET RESERVATION \n");
printf("\t\t\t\t------------------------------\n");
printf("\n1 : OWNER\n2 : CUSTOMER\n3 : EXIT\n");
printf("\nEnter your choice : ");
scanf("%d",&choice);
switch(choice)
{
case 1 : printf("\nEnter the username : ");
scanf("%s",username);
printf("\nEnter the password : ");
scanf("%s",password);
if((strcmp(username,"admin")==0 && strcmp(password,"admin")==0))
owner(first);
else
printf("\nInvalid Login Credentials\n");
break;
case 2 : customer(first);
break;
case 3 : fp = fopen("bus_tickets.txt","w");
fclose(fp);
file(first);
exit(0);
default : printf("\nPlease enter a valid choice ");
}
}
}
void file(NODE *first)
{
FILE *fp;
fp = fopen("bus_tickets.txt","a");
while(first != NULL)
{
fprintf(fp,"%d\t\t%s\t\t%s\t\t%s\t%.2f\t%d\n",first->id,first->from,first->to,first->date,first->mrp,first->quan);
first = first->next;
}
fclose(fp);
}
void owner(NODE *first)
{
int choice;
while(1)
{
printf("\n1 : ADD ROUTE\n2 : MODIFY ROUTE DETAILS\n3 : DELETE ROUTE\n4 : RETURN BACKTO MAIN MENU\n");
printf("\nEnter your choice : ");
scanf("%d",&choice);
switch(choice)
{
case 1 : first = add_route(first);
break;
case 2 : if(first==NULL)
printf("\nNo route to be modified\n");
else
mod_route(first);
break;
case 3 : if(first==NULL)
printf("\nNo route to be deleted\n");
else
first = del_route(first);
break;
case 4 : menu(first);
break;
default : printf("Enter a valid choice");
}
}
}
void customer(NODE *first)
{
int choice;
while(1)
{
printf("\n1 : BUY A TICKET\n2 : RETURN BACK TO MAIN MENU\n");
printf("\nEnter your choice : ");
scanf("%d",&choice);
switch(choice)
{
case 1 : bill(first);
break;
case 2 : menu(first);
break;
default : printf("Enter a valid choice");
}
}
}
NODE* add_route(NODE *first)
{
NODE *newnode,*temp;
newnode=(NODE*)malloc(sizeof(NODE));
newnode->next=NULL;
printf("\nEnter the route ID : ");
scanf("%d",&newnode->id);
printf("\nEnter the number of tickets available : ");
scanf("%d",&newnode->quan);
printf("\nEnter the boarding station : ");
scanf("%s",newnode->from);
printf("\nEnter the destination : ");
scanf("%s",newnode->to);
printf("\nEnter the date : ");
scanf("%s",newnode->date);
printf("\nEnter the price : ");
scanf("%f",&newnode->mrp);
if(first==NULL)
first=newnode;
else
{
temp=first;
while (temp->next!=NULL)
temp=temp->next;
temp->next=newnode;
}
printf("\nRoute %d is added",newnode->id);
return first;
}
NODE* add_route2(NODE *first,int id,int quan,char to[],char from[],char date[],float mrp)
{
NODE *newnode,*temp;
newnode=(NODE*)malloc(sizeof(NODE));
newnode->next=NULL;
newnode->id = id;
newnode->quan = quan;
strcpy(newnode->from,from);
strcpy(newnode->to,to);
strcpy(newnode->date,date);
newnode->mrp = mrp;
if(first==NULL)
first=newnode;
else
{
temp=first;
while (temp->next!=NULL)
temp=temp->next;
temp->next=newnode;
}
return first;
}
NODE* nodes(NODE *first)
{
FILE *fp;
NODE *newnode;
newnode=(NODE*)malloc(sizeof(NODE));
newnode->next = NULL;
fp = fopen("bus_tickets.txt","r");
while((fscanf(fp,"%d%s%s%s%f%d",&newnode->id,newnode->from,newnode->to,newnode->date,&newnode->mrp,&newnode->quan))!= EOF)
first =
add_route2(first,newnode->id,newnode->quan,newnode->to,newnode->from,newnode->date,newnode->
mrp);
fclose(fp);
return first;
}
NODE* search(NODE *first)
{
int key;
NODE *temp;
temp=first;
if(first==NULL)
printf("\nEmpty list");
else
{
printf("\nEnter the route ID to be modified:");
scanf("%d",&key);
while (temp!=NULL && temp->id!=key)
{
temp=temp->next;
}
}
return temp;
}
NODE* search2(NODE *first,int key)
{
NODE *temp;
temp=first;
while (temp!=NULL && temp->id!=key)
temp=temp->next;
return temp;
}
void mod_route(NODE *first)
{
NODE *temp;
printf("\n\n------------------------------------------------------------------------------------\n");
printf("\nTICKET ID\tBOARDING\tDESTINATION\tDATE\t\tMRP\tQUANTITY\n");
printf("------------------------------------------------------------------------------------\n");
display(first);
temp=search(first);
if(temp==NULL)
printf("\nThere is no route with such an ID\n");
else
{
printf("\nEnter the new price : ");
scanf("%f",&temp->mrp);
printf("\nEnter the new number of tickets : ");
scanf("%d",&temp->quan);
}
}
NODE* del_route(NODE *first)
{
NODE *temp,*prev=NULL;
int key;
printf("\n\n------------------------------------------------------------------------------------\n");
printf("\nTICKET ID\tBOARDING\tDESTINATION\tDATE\t\tMRP\tQUANTITY\n");
printf("------------------------------------------------------------------------------------\n");
display(first);
printf("Enter the route ID to be deleted : ");
scanf("%d",&key);
temp = first;
while (temp->next!=NULL&&key!=temp->id)
{
prev=temp;
temp=temp->next;
}
if(prev==NULL)
{
first=temp->next;
free(temp);
}
else if(temp->next==NULL)
{
if(key==temp->id)
{
prev->next=NULL;
free(temp);
}
else
printf("No such ID exists in the list");
}
else
{
prev->next=temp->next;
free(temp);
}
return(first);
}
int updater(int m,int n)
{
if(m > n)
return 0;
else if(m<n)
return n-m;
else
return 0;
}
void bill(NODE *first)
{
int num[100],quan[100],a=0,d,id;
char choice;
float amt = 0,total=0;
NODE *temp;
if(first==NULL)
{
printf("No tickets available\n");
return;
}
printf("\n\n------------------------------------------------------------------------------------\n");
printf("\nTICKET ID\tBOARDING\tDESTINATION\tDATE\t\tMRP\tQUANTITY\n");
printf("------------------------------------------------------------------------------------\n");
display(first);
printf("\t\t\t\t------------------------------\n");
printf("\t\t\t\t PLEASE PLACE AN ORDER \n");
printf("\t\t\t\t------------------------------\n");
do
{ m:
printf("\nEnter Product ID : ");
scanf("%d",&num[a]);
temp=search2(first,num[a]);
while (temp==NULL)
{
printf("No such ID exist");
printf("Enter the new ID");
scanf("%d",&num[a]);
temp=search2(first,num[a]);
}
if(temp->quan==0)
{
printf("\nTicket not available for the given id\n Please provide another ID : ");
goto m;
}
printf("Enter the number of tickets : ");
scanf("%d",&quan[a]);
a++;
printf("\n Do you want to buy another ticket?\n");
printf("If Yes, press y else n : ");
getchar();
scanf("%c",&choice);
}
while(choice == 'y');
printf("\n\n\t\t\t--------------------------------BILL-------------------------------------\n");
printf("\nTICKET ID\tBOARDING\tDESTINATION\tDATE\t\tMRP\tQUANTITY\tAMOUNT\n");
for(int k=0;k<a;k++)
{
temp=search2(first,num[k]);
d=updater(quan[k],temp->quan);
if(d==0)
quan[k]=temp->quan;
temp->quan=d;
amt=temp->mrp*quan[k];
total=total+amt;
printf("\n%d\t\t%s\t\t%s\t\t%s\t%.2f\t%d\t\t%.2f\n",temp->id,temp->from,temp->to,temp->date,temp->mrp,quan[k],amt);
}
printf("----------------------------------------------------------------------------------------------------------------\n");
printf("\nTotal amount : %.2f\n",total);
}
void display(NODE *first)
{
if(first==NULL)
return;
while (first!=NULL)
{
printf("\n%d\t\t%s\t\t%s\t\t%s\t%.2f\t%d\n",first->id,first->from,first->to,first->date,first->mrp,first->quan);
first=first->next;
}
}
int main()
{
NODE *first=NULL;
first = nodes(first);
menu(first);
return 0;
}