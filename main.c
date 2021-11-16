#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct CityNode;
 struct CityNode* head;
 struct CityNode{
char cityName [50] ;
int Rank;
double NOT;
struct CityNode * next;

};
/////////////////////////////////
struct AVLnode;
typedef struct AVLnode *AVLT;
struct AVLnode{
    char Cname [50];
    struct CityNode * head;
    AVLT Left;
    AVLT Right;
    int Height;
};

AVLT isHere(AVLT ,char [50]);
AVLT insert (AVLT  , char [50],char [50] , int ,double );
struct CityNode* insertCity(int , char* , double  );

/////////////////////////////////////////////////////////////////
 AVLT root = NULL;

 struct CityNode * head=NULL;
char* cut(char line[100]){
  char* RANK = strtok(line,"*");
  char* CITY=strtok(NULL,"*");
  char* COUNTRY=strtok(NULL,"*");
  char* NOTou=strtok(NULL,"*");
  //printf("%s\n",RANK);
 // printf("%s\n",CITY);
 // printf("%s\n",COUNTRY);
  //printf("%s\n",NOTou);
   int r= atoi(RANK);
   double n=atof(NOTou);

   if(isHere(root,COUNTRY)==NULL){
    root = insert(root, COUNTRY,CITY,r,n);
   // root->head=NULL;
   // head=NULL;

   //root->head=insertCity(r,CITY,n);

  // head=NULL;

   }
   else{
   root=isHere(root,COUNTRY);

    head=root->head;
   root->head=insertCity(r,CITY,n);

   head=NULL;

   }
   return COUNTRY;
   }
////////////////////////////////////////////
struct CityNode* insertCity(int r, char* city, double n)
{
    struct CityNode* temp = (struct CityNode*) malloc(sizeof(struct CityNode));

    strcpy(temp ->cityName, city);
     temp ->Rank =r;
     temp->NOT=n;
     temp->next=head;
     head =temp;

     printf("\n");

    return head;

}
void printCityOfcountry(struct CityNode * h)
{

    while(h !=NULL)
    {
        printf("%s\n",h->cityName);

        h= h->next;
    }
}
////////////////////////////////////
int getHeight (AVLT t){
    if(t==NULL)
        return -1;
    else
        return t->Height;
}
/////////////////////////////
int MAX (int x, int y){
    if(x>y)
        return x;
    else
        return y;
}
////////////////////////////////////////////////
AVLT singleRotateLeft(AVLT K2) {
    AVLT K1;
    K1        = K2->Left;
    K2->Left  = K1->Right;
    K1->Right = K2;

    K2->Height = 1 + MAX(getHeight(K2->Right) , getHeight(K2->Left));
    K1->Height = 1 + MAX(getHeight(K2) , getHeight(K1->Left));

    return K1;
}
////////////////////////////////////////////////
AVLT singleRotateRight(AVLT K1) {
    AVLT K2;
    K2        = K1->Right;
    K1->Right  = K2->Left;
    K2->Left = K1;

    K1->Height = 1 + MAX(getHeight(K1->Left) , getHeight(K1->Right));
    K2->Height = 1 + MAX(getHeight(K1) , getHeight(K2->Right));

    return K2;
}
////////////////////////////////////////////////
AVLT doubleRotateLeft(AVLT K3) {
    K3->Left  = singleRotateRight(K3->Left);
    return singleRotateLeft(K3);
}
////////////////////////////////////////////////
AVLT doubleRotateRight(AVLT K3) {
    K3->Right  = singleRotateLeft(K3->Right);
    return singleRotateRight(K3);
}
////////////////////////////////////////////////
AVLT insert (AVLT t , char c[50],char city[50] , int r,double n){
    if(t==NULL){
        t=(struct AVLnode*)malloc(sizeof (struct AVLnode));
        strcpy(t->Cname,c);
          t->head=NULL;
    head=NULL;

   t->head=insertCity(r,city,n);

   head=NULL;


        t->Height=0;
        t->Left= t->Right=NULL;

    }
    else if(strcmp(c , t-> Cname)<0){
        t->Left=insert(t->Left,c,city,r,n);
        if(getHeight(t->Left) - getHeight(t->Right) >= 2){
            if(c[0]< t->Left->Cname[0])
                t=singleRotateLeft(t);
            else
                t=doubleRotateLeft(t);
        }
    }
    else if(c[0] > t->Cname[0]){
        t->Right = insert(t->Right , c,city,r,n);
        if(getHeight(t->Right) - getHeight(t->Left) >= 2){
            if(c[0] > t->Right->Cname[0])
                t=singleRotateRight(t);
            else
                t=doubleRotateRight(t);
        }
    }

    t->Height = 1 + MAX(getHeight(t->Right) , getHeight(t->Left));

    return t;
}
////////////////////////////////////////////////////////////////////////////
void printInOrder(AVLT t){
    if(t!= NULL){
       printInOrder(t->Left);
       printf("%s\t\n",t->Cname);

       printCityOfcountry(t->head);
printf("\n******************\n");
       printInOrder(t->Right);}

}
////////////////////////////////////////////////////////////////////////////

AVLT isHere(AVLT t,char c[50]){
 if(t==NULL)
    return NULL;
 if (strcmp(t->Cname,c)==0){
     return t;
   head=  t->head;
     }
     else if (t->Cname[0]<c[0])
     return isHere(t->Left,c);

        else
         return isHere(t->Right,c);

}
void isHere2(AVLT t,char c[50]){
    int x=0;
    if(t!= NULL){
       isHere2(t->Left,c);
      if(strcmp(c,t->Cname)==0){printf("your country is FOUND");x++;}

       isHere2(t->Right,c);
    }

}

void countNumberOfCity(AVLT root , double counter){
if(root!=NULL)
 {
     countNumberOfCity(root->Left,counter);

   head= root->head;
while(head!=NULL){
counter=counter+head->NOT;

head=head->next;
}
printf("%f\n",counter);


     countNumberOfCity(root->Right,counter);
    }
}


void toIntert(AVLT root,char COUNTRY [50],char CITY [50], int r, double n){
    int press;
if(isHere(root,COUNTRY)==NULL){
    root = insert(root, COUNTRY,CITY,r,n);
    //root->head=NULL;
   // head=NULL;

  //head=NULL;

   printf("to make sure that your country is inserted press 1");
    scanf("%d",&press);
       if(press==1)printInOrder(root);
       printf("\nnow you can find the new country , it is inserted! \n ");
   }
   else{

   printf("cannot insert because it is exiest");

   //toIntert( root->Left, COUNTRY , CITY ,  r,  n);toIntert( root->Right, COUNTRY , CITY ,  r,  n);
   }
}
/////////////////////////////////////////////////////////////////////////////////
int main()
{FILE * file;

      char* country;
        char line [150];
       file=fopen("city.txt","r");
       while(!feof(file) ){
       fgets(line,150,file);
       country=cut(line);}
       int numberoftask;
        int taskcount = 1;
        char toSearch [50] ;

      char  Countrytoinsert[50];
      char  Citytoinsert[50];
      int Ranktoinsert;
      double NOTtoinsert;
        while(taskcount>0)
    {
       printf("\nthere is many tasks to do , chose one of them:\n");
       printf("task 1 is for print the countries inserted in a sorted way\n");
       printf("task 2 is for search for a specific country \n");
       printf("task 3 is for insert a new country\n");
       printf("task 4 is for delete a country\n");
       printf("task 5 is for calculate the tree height\n");
       printf("task 6 is for printing information about the countries with its number of tourist cities and total number of tourists\n");
       scanf("%d",&numberoftask);
        if(numberoftask==1)
        {printf("\n\n================================================\n\n");
    printf("---------------- print Tree elements in IN-order-------------\n\n");
    printInOrder(root);
    printf("\n\n================================================\n\n");



       }

    else if (numberoftask==2){printf("enter the country that you want to search for:\n");
    scanf("%s",&toSearch);
  isHere2(root,toSearch);

    }
  else if (numberoftask==3){
        printf("enter the country name:\n");
        scanf("%s",&Countrytoinsert);
  printf("you have to insert at least one city for the new country , enter a city name:\n");
        scanf("%s",&Citytoinsert);
        printf("enter the number of tourists for this city:\n");
        scanf("%f",&NOTtoinsert);
        printf("enter the rank of this city:\n");
        scanf("%d",&Ranktoinsert);
        toIntert(root,Countrytoinsert,Citytoinsert, Ranktoinsert, NOTtoinsert);


  }

    }

    return 0;
}
