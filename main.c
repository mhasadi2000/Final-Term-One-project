#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include <string.h>


char visual[200][200];//global array for show game

//int X,Y,o;

struct Node
{
    char name[10];
    int scoure;
    int x;
    int y;
    int index;
    struct Node *next;
    struct Node *previous;
};

struct blocks
{
    char kind;
    int scoure;
    int i;
    int j;
};

struct blocks A[200];

void reset(struct Node *head)
{
    struct Node *curNode;
    curNode = head;
    int i=0;
    while (curNode!=NULL)
    {
        printf("reset\n");
        curNode->scoure=0;
        i++;
        curNode->index=i;
        curNode = curNode->next;
    }

}
char * searchIndex(int i,struct Node *head)
{
    struct Node *curNode;
    curNode = head;
    int index=1;
    while (index!=i)
    {
        curNode = curNode->next;
        index++;
    }
    return curNode->name;
}

int searchBlocks(char name[],int n,struct Node *head)
{
    int c,i,j;
    struct Node *curr;
    curr = head;
    while (curr!=NULL)
    {
        if (strcmpi(curr->name,name)==0)
        {
            i= curr->x;
            j= curr->y;
            break;
        }
        curr = curr->next;
    }

    for (c = 0; c < n*n; c++)
    {
        if (A[c].i==i && A[c].j==j)
        {
            printf("kind of des block:\t%c\n",A[c].kind);
            switch(A[c].kind)
            {
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
            }
            //return A[c].kind;
        }
    }
    return 0;
}

int IsEmpty(char name[],struct Node *head)
{
    int i,j,counter=0;
    struct Node *curr, *curNode =head;
    curr = head;
    while (curr!=NULL)
    {
        if(strcmpi(curr->name, name)==0)
        {
            i=curr->x;
            j=curr->y;
        }
        curr = curr->next;
    }
    while (curNode!=NULL)
    {
        if(curNode->x==i && curNode->y==j)
        {
            counter++;
            if(counter<1)
            {
                printf("is not empty\n");
                return -1;
            }
        }
        curNode=curNode->next;
    }
    printf("IsEmpty\n");
    return 1;
}

struct Node * createList(int n,struct blocks A[],struct Node *head)
{
    //int NOP=1;

    struct Node *newNode, *temp;
    int x,y, i,c;
    char name[10];
    bool condition=true;

    head = malloc(sizeof(struct Node));

    if (head == NULL)
    {
        printf("Unable to allocate memory. Exiting from app.");
        exit(0);
    }
    /* Input head node data from user */
    printf("Enter data of node 1 (name/x/y):\n ");
    scanf("%s", name);
    scanf("%d", &x);
    scanf("%d", &y);
    while(1)
    {
        c=searchBlocks(name,n,head);
        if(c == 3)
        {
            printf("!!the selected block is forbidden!!\n");
            printf("Enter data of node 1 (name/x/y):\n ");
            scanf("%s", name);
            scanf("%d", &x);
            scanf("%d", &y);
        }
        break;
        //condition=false;
    }

    strcpy(head->name,name);  // Link data field with data
    head->x = x; // Link data field with data
    head->y = y; // Link data field with data
    head->next = NULL; // Link address field to NULL

    temp = head;

    /*
     * Create n nodes and add to the list
     */
    for (i = 2; i <= n; i++)
    {
        newNode = malloc(sizeof(struct Node));

        /* If memory is not allocated for newNode */
        if (newNode == NULL)
        {
            printf("Unable to allocate memory. Exiting from app.");
            exit(0);
        }

        printf("Enter data of node %d (name/x/y):\n ", i);
        scanf("%s", name);
        scanf("%d", &x);
        scanf("%d", &y);
        condition = true;
        while(condition)
        {
            if(searchBlocks(name,n,head)== 3 || IsEmpty(name,head)== -1)
            {
                printf("!!the selected block is forbidden!!\n");
                printf("Enter data of node %d (name/x/y):\n ",i);
                scanf("%s", name);
                scanf("%d", &x);
                scanf("%d", &y);
            }
            else
            {
                condition=false;
            }
        }
        strcpy(newNode->name,name);  // Link data field of newNode
        newNode->x = x; // Link data field of newNode
        newNode->y = y; // Link data field of newNode
        newNode->next = NULL; // The newNode should point to nothing

        temp->next = newNode; // Link previous node i.e. temp to the newNode
        temp = temp->next;
    }
    return head;
}

int check(int w, int e,struct Node *head)
{
    int i=(e-1)/2,j=(w-1)/2;
    int index;
    struct Node *curNode;

    index = 0;
    curNode = head;

    // Iterate till last element until key is not found
    while (curNode != NULL && (curNode->x != i || curNode->y!=j))
    {
        //printf("checking\n");
        index++;
        curNode = curNode->next;
    }


    return (curNode != NULL) ? index : -1;
}

int change(char name[],char a,struct blocks A[],int n,struct Node *head)
{
    struct Node *curNode;
    curNode = head;
    int xa,ya,i,j;
    char esm[10];


    while (curNode != NULL && (strcmpi(curNode->name, name )))
    {
        curNode = curNode->next;
    }
    xa= curNode->x;
    ya= curNode->y;
    switch(a)
    {
    case 'w':
        i = xa+0;
        j = ya-1;
        break;
    case 's':
        i = xa+0;
        j = ya+1;
        break;
    case 'd':
        if(xa%2==0)
        {
            i = xa+1;
            j = ya+0;
        }
        else
        {
            i = xa+1;
            j = ya+1;
        }
        break;
    case 'a':
        if(xa%2==0)
        {
            i = xa-1;
            j = ya+0;
        }
        else
        {
            i = xa-1;
            j = ya+1;
        }
        break;
    case 'e':
        if(xa%2==0)
        {
            i = xa+1;
            j = ya-1;
        }
        else
        {
            i = xa+1;
            j = ya+0;
        }
        break;
    case 'q':
        if(xa%2==0)
        {
            i = xa-1;
            j = ya-1;
        }
        else
        {
            i = xa-1;
            j = ya+0;
        }
        break;
    default:
        printf("please enter one of those (q,w,e,a,s,d)\n");
        scanf("%s",esm);
        change(esm,a,A,n,head);
        break;
    }
    curNode->x = i;
    curNode->y = j;
    if(searchBlocks(name,n,head)== 3 || IsEmpty(name,head)== -1)
    {
        curNode->x = xa;
        curNode->y = ya;
        printf("!!the selected block is forbidden!!\n");
        return -1;
    }
    else
    {
        printf("des\t%d/%d\n",curNode->x,curNode->y);
    }
    return 1;
}

void printNodes(struct Node *head)
{
    struct Node * curr = head;
    while (curr!=NULL)
    {
        printf("\n%s/ ",curr->name);
        printf("%d/",curr->x);
        printf("%d/",curr->y);
        curr = curr->next;
    }
    printf("\n");
}

void jadval(int n,struct Node *head,int counter)
{
    int i,j;
    visual[0][0]=' ';
    if (n%2==0)
    {
        for(i=0; i<2*n+2; i++)
        {
            if(i==0 && (i!=0 || j!=0) )
            {
                for(j=0; j<2*n+1; j++)
                {
                    if(j%4==1)
                    {
                        visual[i][j]='_';
                    }
                    else
                    {
                        visual[i][j]=' ';
                    }
                }
            }
            if(i==1&& (i!=0 || j!=0))
            {
                for(j=0; j<2*n; j++)
                {
                    if(j%4==0)
                    {
                        visual[i][j]='/';
                    }
                    else if(j%4==1)
                    {
                        //printf("in jadval");
                        if(check(i,j,head)!= -1)
                        {

                            //printf("index: %d\n",check(i,j));
                            printf("check%d\n",check(i,j,head));
                            if(counter==1){
                                visual[i][j]='x';
                            }else{
                                visual[i][j]='o';
                            }

                        }
                        else
                        {
                            visual[i][j]=' ';
                        }
                    }
                    else if(j%4==2)
                    {
                        visual[i][j]='\\';
                    }
                    else if(j%4==3)
                    {
                        visual[i][j]='_';
                    }
                }
                visual[i][j]=' ';
            }
            if(i>1 && i%2==0)
            {
                for(j=0; j<2*n+1; j++)
                {
                    if(j%4==0)
                    {
                        visual[i][j]='\\';
                    }
                    else if(j%4==1)
                    {
                        visual[i][j]='_';
                    }
                    else if(j%4==2)
                    {
                        visual[i][j]='/';
                    }
                    else if(j%4==3)
                    {
                        //printf("in jadval");
                        if(check(i,j,head) != -1)
                        {
                            printf("check%d\n",check(i,j,head));
                            //printf("index: %d\n",check(i,j));
                            // printf("%c",check(i,j));
                            if(counter==1){
                                visual[i][j]='x';
                            }else{
                                visual[i][j]='o';
                            }
                        }
                        else
                        {
                            visual[i][j]=' ';
                        }
                    }
                }

            }
            if(i>1 && i%2!=0)
            {
                for(j=0; j<2*n+1; j++)
                {
                    if(j%4==0)
                    {
                        visual[i][j]='/';
                    }
                    else if(j%4==1)
                    {
                        //printf("in jadval");
                        if(check(i,j,head)!= -1)
                        {
                            printf("check%d\n",check(i,j,head));
                            //printf("index: %d\n",check(i,j));
                            //printf("%c",check(i,j));
                            if(counter==1){
                                visual[i][j]='x';
                            }else{
                                visual[i][j]='o';
                            }
                        }
                        else
                        {
                            visual[i][j]=' ';
                        }
                    }
                    else if(j%4==2)
                    {
                        visual[i][j]='\\';
                    }
                    else if(j%4==3)
                    {
                        visual[i][j]='_';
                    }
                }

            }
            if(i==2*n+1)
            {
                for(j=0; j<2*n+1; j++)
                {
                    if(j<2)
                    {
                        visual[i][j]=' ';
                    }
                    else if(j%4==0)
                    {
                        visual[i][j]='/';
                    }
                    else if(j%4==1)
                    {
                        visual[i][j]=' ';
                    }
                    else if(j%4==2)
                    {
                        visual[i][j]='\\';
                    }
                    else if(j%4==3)
                    {
                        visual[i][j]='_';
                    }
                }

            }

        }
    }
    else
    {
        for(i=0; i<2*n+1; i++)
        {
            if(i==0 && (i!=0 || j!=0) )
            {
                for(j=0; j<2*n+1; j++)
                {
                    if(j%4==1)
                    {
                        visual[i][j]='_';
                    }
                    else
                    {
                        visual[i][j]=' ';
                    }
                }
            }
            if(i!=0 && i%2==0)
            {
                for(j=0; j<2*n+1; j++)
                {
                    if(j%4==0)
                    {
                        visual[i][j]='\\';
                    }
                    else if(j%4==1)
                    {
                        visual[i][j]='_';
                    }
                    else if(j%4==2)
                    {
                        visual[i][j]='/';
                    }
                    else if(j%4==3)
                    {
                        visual[i][j]=' ';
                    }
                }

            }
            if(i!=0 && i%2!=0)
            {
                for(j=0; j<2*n+1; j++)
                {
                    if(j%4==0)
                    {
                        visual[i][j]='/';
                    }
                    else if(j%4==1)
                    {
                        visual[i][j]=' ';
                    }
                    else if(j%4==2)
                    {
                        visual[i][j]='\\';
                    }
                    else if(j%4==3)
                    {
                        visual[i][j]='_';
                    }
                }

            }
        }
    }
}

void show(int n)
{
    int i,j,k,c=0,d=0,m=0,counter=0;
    if(n%2==0)
    {
        printf("     ");
        for(k=0; k<n; k++)
        {
            printf("%d ",d);
            d++;
        }
        for(i=0; i<2*n+2; i++)
        {
            printf("\n");
            if(counter==0)
            {
                printf("    ");
                for(j=0; j<2*n+1; j++)
                {
                    printf("%c",visual[i][j]);
                }
            }
            else
            {
                if(counter<2*n+1)
                {
                    if(m==2)
                    {
                        m=0;
                        c++;
                    }
                    printf("%d   ",c);
                    m++;
                    for(j=0; j<2*n+1; j++)
                    {
                        printf("%c",visual[i][j]);
                    }
                }
                else
                {
                    printf("    ");
                    for(j=0; j<2*n+1; j++)
                    {
                        printf("%c",visual[i][j]);
                    }
                }


            }
            counter++;
        }
    }
    else
    {
        for(k=0; k<n; k++)
        {
            printf(" %d  ",d);
            d++;
        }
        for(i=0; i<2*n+1; i++)
        {
            for(j=0; j<2*n+1; j++)
            {
                printf("%c",visual[i][j]);
            }

            printf("\n");
            if(counter%2==1)
            {
                printf("%d   ",c);
                c++;
            }
            else
            {
                printf("    ");
            }
            counter++;
        }
    }
    printf("\n");
    printf("\n");
}

int energyCheck(char name[],struct Node *head)                //////////
{
    struct Node * curNode = head;
    while (curNode!=NULL)
    {
        printf("energyCheck\n");
        if(strcmpi(curNode->name,name)==0)
        {
            if(curNode->scoure >= 80)
            {
                printf("MITOSES is possible\n");
                return 1;
            }
            return -1;
        }
        curNode = curNode->next;
    }
}

void Mitos(char name[],struct blocks A[],int n,struct Node *head)                     //////////
{
    int i,j,position,r2,xa,ya;
    struct Node *newNode, *temp,*currNode;
    currNode = head;
    char NewName1[10],NewName2[10];
    srand(time(NULL));

    newNode = (struct Node*)malloc(sizeof(struct Node));

    if(newNode == NULL)
    {
        printf("Unable to allocate memory.");
    }
    else
    {
        printf("enter 2 new name\n");
        scanf("%s",NewName1);
        scanf("%s",NewName2);
        strcpy(newNode->name, NewName1);
        newNode->scoure = 40;
        newNode->next = NULL;
        while(currNode!=NULL)
        {
            if(strcmpi(currNode->name,name) == 0)
            {
                position = (currNode->index) + 1;
                xa=currNode->x;
                ya=currNode->y;
            }
            currNode = currNode->next;
        }
here:
        r2=rand()%6;
        printf("r2: %d",r2);
        switch(r2)
        {
        case 1:
            i = xa+0;
            j = ya-1;
            break;
        case 4:
            i = xa+0;
            j = ya+1;
            break;
        case 3:
            if(xa%2==0)
            {
                i = xa+1;
                j = ya+0;
            }
            else
            {
                i = xa+1;
                j = ya+1;
            }
            break;
        case 5:
            if(xa%2==0)
            {
                i = xa-1;
                j = ya+0;
            }
            else
            {
                i = xa-1;
                j = ya+1;
            }
            break;
        case 2:
            if(xa%2==0)
            {
                i = xa+1;
                j = ya-1;
            }
            else
            {
                i = xa+1;
                j = ya+0;
            }
            break;
        case 0:
            if(xa%2==0)
            {
                i = xa-1;
                j = ya-1;
            }
            else
            {
                i = xa-1;
                j = ya+0;
            }
            break;
        default:
            printf("make a rand is impossible\n");
            break;
        }

        newNode->x=i;
        newNode->y=j;

        if(searchBlocks(NewName1,n,head)==3 || i<0 || j<0 || i>=n || j>=n)
        {
            printf("thats not possible\n it is going to make another choice\n");
            goto here;
        }


        temp = head;
        // Traverse to the n-1 position
        for(i=2; i<=position-1; i++)
        {
            temp = temp->next;

            if(temp == NULL)
                break;
        }

        if(temp != NULL)
        {
            /* Link address part of new node */
            newNode->next = temp->next;

            /* Link address part of n-1 node */
            temp->next = newNode;
            strcpy(temp->name,NewName2);                 /////who to delete previous name.
            temp->scoure = 40;

            if(temp->x == newNode->x && temp->x == newNode->x)
            {
                goto here;
            }
            printf("DATA INSERTED SUCCESSFULLY\n");
        }
        else
        {
            printf("UNABLE TO INSERT DATA AT THE GIVEN POSITION\n");
        }
    }
}

void gainEnergy(char name[],int n,struct Node *head)                //////////
{
    struct Node *currNode = head;
    int i,x,y,c;
    while(currNode!=NULL)
    {
        if(strcmpi(currNode->name,name) == 0)
        {
            i=currNode->scoure;
            x=currNode->x;
            y=currNode->y;
            break;
        }
        currNode = currNode->next;
    }
    for (c = 0; c < n*n; c++)
    {
        if (A[c].i==x && A[c].j==y)
        {
            //X=i;
            //Y=j;
            if(A[c].scoure > 15 && i<85)
            {
                currNode->scoure = i+15;
                A[c].scoure -=15;
                printf("energy has been gained\n");
                return;
            }
            else if(i<85)
            {
                currNode->scoure = i+(100-i);
                A[c].scoure -=15;
                printf("energy of the cell is more than 85\n");
                printf("energy has been gained\n");
                return;
            }
            else if(A[c].scoure < 15)
            {
                currNode->scoure = i+A[c].scoure;
                A[c].scoure =0;
                printf("energy of the block became empty\n");
                printf("energy has been gained\n");
                return;
            }
        }
    }

}

void SAVE(FILE *fp,struct blocks A[],int n,int NOP,struct Node *head,struct Node *team1,struct Node *team2)                              //////////
{
    int c=0,i=0,i1,i2;

    char name[10];
    fp = fopen( "load.bin", "wb" );
    if(fp== NULL)
    {
        printf("Cannot create file\n");
        return ;
    }

    fwrite(&n,sizeof(int),1,fp);
    fwrite(&NOP,sizeof(int),1,fp);
    struct Node *curr=head;
    if(NOP==1)                                ///////////////////
    {

        while(curr!=NULL)
        {
            i++;
            curr=curr->next;
        }
        fwrite(&i,sizeof(int),1,fp);
    }
    else
    {
        struct Node *curr1=team1;
        while(curr!=NULL)
        {
            i1++;
            curr=curr->next;
        }
        struct Node *curr=team2;
        while(curr!=NULL)
        {
            i2++;
            curr=curr->next;
        }
        fwrite(&i1,sizeof(int),1,fp);
        fwrite(&i2,sizeof(int),1,fp);
    }


    for(c=0; c<n*n; c++)
    {
        fwrite(&A[c].kind,sizeof(char),1,fp);
        fwrite(&A[c].scoure,sizeof(int),1,fp);
        fwrite(&A[c].i,sizeof(int),1,fp);
        fwrite(&A[c].j,sizeof(int),1,fp);
        printf("%c/%d/%d/%d\t",A[c].kind,A[c].scoure,A[c].j,A[c].i);
    }
    if(NOP==1)                                                     /////////////////////
    {
        struct Node *curNode = head;

        while(curNode!=NULL)
        {
            fwrite(&curNode->name, sizeof(name),1, fp );
            fwrite(&curNode->scoure, sizeof(int),1, fp );
            fwrite(&curNode->x, sizeof(int),1, fp );
            fwrite(&curNode->y, sizeof(int),1, fp );
            printf("%s/%d/%d/%d\t",curNode->name,curNode->scoure,curNode->x,curNode->y);
            curNode = curNode->next;
        }
        fclose(fp);
        printf("data of the map saved\n");
    }
    else
    {
        struct Node *curNode1 = team1, *curNode2 = team2;
        while(curNode1!=NULL)
        {
            fwrite(&curNode1->name, sizeof(name),1, fp );
            fwrite(&curNode1->scoure, sizeof(int),1, fp );
            fwrite(&curNode1->x, sizeof(int),1, fp );
            fwrite(&curNode1->y, sizeof(int),1, fp );
            printf("%s/%d/%d/%d\t",curNode1->name,curNode1->scoure,curNode1->x,curNode1->y);
            curNode1 = curNode1->next;
        }
        fclose(fp);
        printf("data of team1 the map saved\n");



        while(curNode2!=NULL)
        {
            fwrite(&curNode2->name, sizeof(name),1, fp );
            fwrite(&curNode2->scoure, sizeof(int),1, fp );
            fwrite(&curNode2->x, sizeof(int),1, fp );
            fwrite(&curNode2->y, sizeof(int),1, fp );
            printf("%s/%d/%d/%d\t",curNode2->name,curNode2->scoure,curNode2->x,curNode2->y);
            curNode2 = curNode2->next;
        }
        fclose(fp);
        printf("data of the map saved\n");
    }

}

struct Node * Load(FILE *fp,FILE *fpout,struct blocks A[],struct Node *head,struct Node *team1,struct Node *team2)
{
    int c=0,i,j,m,NOP,NON,NON1,NON2;// NOP:number of players  NON:number of nodes
    //struct Node *curNode = head;
    char name[10];
    fp = fopen( "load.bin", "rb" );
    fread(&m,sizeof(int),1,fp);
    fread(&NOP,sizeof(int),1,fp);
    if(NOP==1)
    {
        fread(&NON,sizeof(int),1,fp);
    }
    else
    {
        fread(&NON1,sizeof(int),1,fp);
        fread(&NON2,sizeof(int),1,fp);
    }

    if(NOP==1)                                           //////////////////
    {
        for(i=0; i<m; i++)
        {
            for(j=0; j<m; j++)
            {
                fread(&A[c].kind,sizeof(char),1,fp);
                fread(&A[c].scoure,sizeof(int),1,fp);
                fread(&A[c].i,sizeof(int),1,fp);
                fread(&A[c].j,sizeof(int),1,fp);
                printf("%c/%d/%d/%d\n",A[c].kind,A[c].scoure,A[c].i,A[c].j);
                c++;
            }
            printf("\n");
        }
        struct Node *newNode, *temp;
        int x,y, k;

        head = malloc(sizeof(struct Node));

        if (head == NULL)
        {
            printf("Unable to allocate memory. Exiting from app.");
            exit(0);
        }
        printf("head\n");
        fread(&head->name, sizeof(name),1, fp);
        fread(&head->scoure, sizeof(int),1, fp);
        fread(&head->x, sizeof(int),1, fp);
        fread(&head->y, sizeof(int),1, fp);
        printf("%s/%d/%d/%d\n",head->name,head->scoure,head->x,head->y);
        head->next = NULL; // Link address field to NULL

        temp = head;

        /*
         * Create n nodes and add to the list
         */
        for (k = 2; k <=NON ; k++)
        {
            newNode = malloc(sizeof(struct Node));

            /* If memory is not allocated for newNode */
            if (newNode == NULL)
            {
                printf("Unable to allocate memory. Exiting from app.");
                exit(0);
            }

            printf("newNode\n");
            fread(&newNode->name, sizeof(name),1, fp);
            fread(&newNode->scoure, sizeof(int),1, fp);
            fread(&newNode->x, sizeof(int),1, fp);
            fread(&newNode->y, sizeof(int),1, fp);
            printf("%s/%d/%d/%d\n",newNode->name,newNode->scoure,newNode->x,newNode->y);

            newNode->next = NULL; // The newNode should point to nothing

            temp->next = newNode; // Link previous node i.e. temp to the newNode
            temp = temp->next;
        }
    }
    else
    {


        struct Node *newNode2, *temp2;
        int x,y, k;

        team1 = malloc(sizeof(struct Node));

        if (team1 == NULL)
        {
            printf("Unable to allocate memory. Exiting from app.");
            exit(0);
        }
        printf("team1\n");
        fread(&team1->name, sizeof(name),1, fp);
        fread(&team1->scoure, sizeof(int),1, fp);
        fread(&team1->x, sizeof(int),1, fp);
        fread(&team1->y, sizeof(int),1, fp);
        printf("%s/%d/%d/%d\n",team1->name,team1->scoure,team1->x,team1->y);
        team1->next = NULL; // Link address field to NULL

        temp2 = team1;

        /*
         * Create n nodes and add to the list
         */
        for (k = 2; k <=NON1 ; k++)
        {
            newNode2 = malloc(sizeof(struct Node));

            /* If memory is not allocated for newNode */
            if (newNode2 == NULL)
            {
                printf("Unable to allocate memory. Exiting from app.");
                exit(0);
            }

            printf("newNode2\n");
            fread(&newNode2->name, sizeof(name),1, fp);
            fread(&newNode2->scoure, sizeof(int),1, fp);
            fread(&newNode2->x, sizeof(int),1, fp);
            fread(&newNode2->y, sizeof(int),1, fp);
            printf("%s/%d/%d/%d\n",newNode2->name,newNode2->scoure,newNode2->x,newNode2->y);

            newNode2->next = NULL; // The newNode should point to nothing

            temp2->next = newNode2; // Link previous node i.e. temp to the newNode
            temp2 = temp2->next;
        }



        struct Node *newNode1, *temp1;
        //int x,y, k;

        team2 = malloc(sizeof(struct Node));

        if (team2 == NULL)
        {
            printf("Unable to allocate memory. Exiting from app.");
            exit(0);
        }
        printf("team2\n");
        fread(&team2->name, sizeof(name),1, fp);
        fread(&team2->scoure, sizeof(int),1, fp);
        fread(&team2->x, sizeof(int),1, fp);
        fread(&team2->y, sizeof(int),1, fp);
        printf("%s/%d/%d/%d\n",team2->name,team2->scoure,team2->x,team2->y);
        team2->next = NULL; // Link address field to NULL

        temp1 = team2;

        /*
         * Create n nodes and add to the list
         */
        for (k = 2; k <=NON2 ; k++)
        {
            newNode1 = malloc(sizeof(struct Node));

            /* If memory is not allocated for newNode */
            if (newNode1 == NULL)
            {
                printf("Unable to allocate memory. Exiting from app.");
                exit(0);
            }

            printf("newNode1\n");
            fread(&newNode1->name, sizeof(name),1, fp);
            fread(&newNode1->scoure, sizeof(int),1, fp);
            fread(&newNode1->x, sizeof(int),1, fp);
            fread(&newNode1->y, sizeof(int),1, fp);
            printf("%s/%d/%d/%d\n",newNode1->name,newNode1->scoure,newNode1->x,newNode1->y);

            newNode1->next = NULL; // The newNode should point to nothing

            temp1->next = newNode1; // Link previous node i.e. temp to the newNode
            temp1 = temp1->next;
        }
    }
    return head;
    //return m;
}

void singleplayer(FILE *fp,FILE *fpout,struct blocks A[],struct Node *head,struct Node *team1,struct Node *team2)
{
     struct Node *curNode;
     char select[10];
     int n,i,j,u=0,o=0,number,choice,ch,start,test,index,NOP;
     fp = fopen("map2.bin","rb");
        if(fp==NULL)
            return 1;
        NOP=1;
        fread(&n,sizeof(int),1,fp);
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                fread(&A[o].kind,sizeof(char),1,fp);
                A[o].scoure =100;
                A[o].i=j;
                A[o].j=i;
                printf("%c/%d/%d/%d\t",A[o].kind,A[o].scoure,A[o].i,A[o].j);
                o++;
            }
            printf("\n");
        }
        printf("\n");
        jadval(n,head,0);
        show(n);
        printf("LEARNING point...... \n");
        printf("upside is ROW number\n");
        printf("leftside is COLUMN number\n");
        printf("\n");
        printf("how many cells do you want in the map\n");
        scanf("%d",&number);
        system("cls");
        head=createList(number,A,head);
        reset(head);

        srand(time(NULL));
        jadval(n,head,0);
        show(n);
        bool condition=true;
        while(condition)
        {
jump:
            printf("Please choose one of your cells:\n");
            //struct Node *curNode;
            curNode = head;
            u=0;
            while (curNode != NULL )
            {
                u++;
                printf("%d] %s (%d,%d)\n",u,curNode->name,curNode->x,curNode->y);
                curNode = curNode->next;
            }
            scanf("%d",&index);
            strcpy(select, searchIndex(index,head));

            printf("1)Move\n2)split a cell\n3)boost energy\n4)save\n5)exit\n");
            scanf("%d",&choice);
            if(choice==1)
            {
                printf("MOVE BY (q,w,e,a,s,d)\n");
                ch=getch();
                if(change(select,ch,A,n,head) == -1)
                {
                    goto jump;
                }
                system("cls");
                jadval(n,head,0);
                show(n);
            }
            else if(choice==2)
            {
                printf("search %d\n",searchBlocks(select,n,head));
                if(searchBlocks(select,n,head)==2)
                {
                    if( energyCheck(select,head)==1)
                    {
                        Mitos(select,A,n,head);
                        jadval(n,head,0);
                        show(n);
                    }
                    else
                    {
                        printf("your energy is not enogh\n");
                    }

                }
                else
                {
                    printf("MITOSES in this block is impossible\n");
                }

            }
            else if(choice==3)
            {
                printf("search %d\n",searchBlocks(select,n,head));
                if(searchBlocks(select,n,head)==1 )
                {
                    gainEnergy(select,n,head);
                    jadval(n,head,0);
                    show(n);
                }
                else
                {
                    printf("you cannot gain energy from this block\n");
                }
            }
            else if(choice==4)
            {
                team1=NULL;
                team2=NULL;
                SAVE(fpout,A,n,NOP,head,team1,team2);
            }
            else if(choice==5)
            {
                printf("i hope you enjoy the game\n");
                condition=false;
                fclose(fp);
                return 0;
            }
        }
}

void multiplayer(FILE *fp,FILE *fpout,struct blocks A[],struct Node *head,struct Node *team1,struct Node *team2)
{
    //struct Node *team1,*team2,*head;
    int i,j,n,number,o,counter=0,u,index,choice,ch;
    char select[10];
    o=0;
    int NOP=2;
    fp = fopen("map2.bin","rb");
    if(fp==NULL)
        return 1;
    fread(&n,sizeof(int),1,fp);
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            fread(&A[o].kind,sizeof(char),1,fp);
            A[o].scoure =100;
            A[o].i=j;
            A[o].j=i;
            printf("%c/%d/%d/%d\t",A[o].kind,A[o].scoure,A[o].i,A[o].j);
            o++;
        }
        printf("\n");
    }
    printf("\n");
    //jadval(n,head,0);
    jadval(n,team1,0);
    jadval(n,team2,1);
    show(n);
    printf("LEARNING point...... \n");
    printf("upside is ROW number\n");
    printf("leftside is COLUMN number\n");
    printf("\n");
    printf("number of cells for each player:\n");
    scanf("%d",&number);
    system("cls");
    team1=createList(number,A,team1);
    team2=createList(number,A,team2);
    reset(team1);
    reset(team2);
    srand(time(NULL));
    jadval(n,team1,0);
    jadval(n,team2,1);
    show(n);
    struct Node *curNode;
    while(1)
    {
        if(counter%2==0)
        {
up:
            printf("Please choose one of your cells (team x):\n");

            curNode = team1;
            u=0;
            while (curNode != NULL )
            {
                u++;
                printf("%d] %s (%d,%d)\n",u,curNode->name,curNode->x,curNode->y);
                curNode = curNode->next;
            }
            scanf("%d",&index);
            strcpy(select, searchIndex(index,team1));

            printf("1)Move\n2)split a cell\n3)boost energy\n4)save\n5)exit\n");
            scanf("%d",&choice);
            if(choice==1)
            {
                printf("MOVE BY (q,w,e,a,s,d)\n");
                ch=getch();
                if(change(select,ch,A,n,team1) == -1)
                {
                    goto up;
                }
                system("cls");
                jadval(n,team1,0);
                jadval(n,team2,1);
                show(n);
            }
            else if(choice==2)
            {
                printf("search %d\n",searchBlocks(select,n,team1));
                if(searchBlocks(select,n,team1)==2)
                {
                    if( energyCheck(select,team1)==1)
                    {
                        Mitos(select,A,n,team1);
                        jadval(n,team1,0);
                        jadval(n,team2,1);
                        show(n);
                    }
                    else
                    {
                        printf("your energy is not enogh\n");
                    }

                }
                else
                {
                    printf("MITOSES in this block is impossible\n");
                }

            }
            else if(choice==3)
            {
                printf("search %d\n",searchBlocks(select,n,team1));
                if(searchBlocks(select,n,team1)==1 )
                {
                    gainEnergy(select,n,team1);
                    jadval(n,team1,0);
                    jadval(n,team2,1);
                    show(n);
                }
                else
                {
                    printf("you cannot gain energy from this block\n");
                }
            }
            else if(choice==4)
            {
                SAVE(fpout,A,n,NOP,head,team1,team2);
            }
            else if(choice==5)
            {
                printf("i hope you enjoy the game\n");
                //condition=false;
                fclose(fp);
                return 0;
            }
        }
        else
        {
            here:
            printf("Please choose one of your cells (team o):\n");

            curNode = team2;
            u=0;
            while (curNode != NULL )
            {
                u++;
                printf("%d] %s (%d,%d)\n",u,curNode->name,curNode->x,curNode->y);
                curNode = curNode->next;
            }
            scanf("%d",&index);
            strcpy(select, searchIndex(index,team2));

            printf("1)Move\n2)split a cell\n3)boost energy\n4)save\n5)exit\n");
            scanf("%d",&choice);
            if(choice==1)
            {
                printf("MOVE BY (q,w,e,a,s,d)\n");
                ch=getch();
                if(change(select,ch,A,n,team2) == -1)
                {
                    goto here;
                }
                system("cls");
                jadval(n,team1,0);
                jadval(n,team2,1);
                show(n);
            }
            else if(choice==2)
            {
                printf("search %d\n",searchBlocks(select,n,team2));
                if(searchBlocks(select,n,team2)==2)
                {
                    if( energyCheck(select,team2)==1)
                    {
                        Mitos(select,A,n,team2);
                        jadval(n,team1,0);
                        jadval(n,team2,1);
                        show(n);
                    }
                    else
                    {
                        printf("your energy is not enogh\n");
                    }

                }
                else
                {
                    printf("MITOSES in this block is impossible\n");
                }

            }
            else if(choice==3)
            {
                printf("search %d\n",searchBlocks(select,n,team2));
                if(searchBlocks(select,n,team2)==1 )
                {
                    gainEnergy(select,n,team2);
                    jadval(n,team1,0);
                    jadval(n,team2,1);
                    show(n);
                }
                else
                {
                    printf("you cannot gain energy from this block\n");
                }
            }
            else if(choice==4)
            {
                SAVE(fpout,A,n,NOP,head,team1,team2);
            }
            else if(choice==5)
            {
                printf("i hope you enjoy the game\n");
                //condition=false;
                fclose(fp);
                return 0;
            }
        }

    }
}


void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}


int main()
{
    int n,i,j,u=0,o=0,number,choice,ch,start,test,index,NOP;
    char select[10];
    struct Node *head=NULL,*team1=NULL,*team2=NULL;
    struct Node *curNode;
    FILE *fp,*fpout;
    SetColor(10);
    printf(" 1)Load\n2)New single player game\n3)New Multiplayer game\n4)Exit\n");
    scanf("%d",&start);
    if(start==2)
    {
        //single player
        singleplayer(fp,fpout,A,head,team1,team2);
    }
    else if(start==1)
    {
        //load
        fp = fopen("map2.bin","rb");
        if(fp==NULL)
            return 1;
        fread(&n,sizeof(int),1,fp);
        fclose(fp);
        head=Load(fp,fpout,A,head,team1,team2);
        //n=6;
        srand(time(NULL));
        jadval(n,head,0);
        show(n);
        bool condition=true;
        while(condition)
        {
there:
            printf("Please choose one of your cells:\n");
            //struct Node *curNode;
            curNode = head;
            u=0;
            while (curNode != NULL )
            {
                u++;
                printf("%d] %s (%d,%d)\n",u,curNode->name,curNode->x,curNode->y);
                curNode = curNode->next;
            }
            scanf("%d",&index);
            strcpy(select, searchIndex(index,head));

            printf("1)Move\n2)split a cell\n3)boost energy\n4)save\n5)exit\n");
            scanf("%d",&choice);
            if(choice==1)
            {
                printf("MOVE BY (q,w,e,a,s,d)\n");
                ch=getch();
                if(change(select,ch,A,n,head) == -1)
                {
                    goto there;
                }
                system("cls");
                jadval(n,head,0);
                show(n);
            }
            else if(choice==2)
            {
                printf("search %d\n",searchBlocks(select,n,head));
                if(searchBlocks(select,n,head)==2)
                {
                    if( energyCheck(select,head)==1)
                    {
                        Mitos(select,A,n,head);
                        jadval(n,head,0);
                        show(n);
                    }
                    else
                    {
                        printf("your energy is not enogh\n");
                    }

                }
                else
                {
                    printf("MITOSES in this block is impossible\n");
                }

            }
            else if(choice==3)
            {
                printf("search %d\n",searchBlocks(select,n,head));
                if(searchBlocks(select,n,head)==1 )
                {
                    gainEnergy(select,n,head);
                    jadval(n,head,0);
                    show(n);
                }
                else
                {
                    printf("you cannot gain energy from this block\n");
                }
            }
            else if(choice==4)
            {
                SAVE(fpout,A,n,NOP,head,team1,team2);
            }
            else if(choice==5)
            {
                printf("i hope you enjoy the game\n");
                condition=false;
                fclose(fp);
                return 0;
            }
        }
    }
    else if(start==3)
    {
        NOP=2;
        multiplayer(fp,fpout,A,head,team1,team2);
    }
    else if(start==4)
    {
        return -1;
    }


    printNodes(head);
    return 0;
}
