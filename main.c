#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//menu
//node of linked list
//status
int orderInprogress=1;
int orderAssigned=2;
int currentOrderId=0;
struct menu* menuIndex;
struct deliqueue*Deliqueue;
//STRUCTs----------------------------------------------------------------------------------------------------------------------
struct item
{
    int itemid;
    char name[50];
    float price;
    struct item*next;

};
//linked list
struct menu
{
    struct item*front;

};

//node of delivery person
struct deliveryper
{
    char name[50];
    int id;
    struct deliveryper*next;
};
//queue of delivery person
struct deliqueue
{
    struct deliveryper*front;
};
//MENU-------------------------------------------------------------------------------------------------------------------------

void insertMenu()
{
    while(1)
    {
        char choice;
        fflush(stdin);
        printf("\n Do you want to enter items in the menu(y/n):");
        scanf("%c",&choice);
        if(choice=='Y'||choice=='y')
        {

            int itemid = 0;
            char name[50];
            float price = 0.0;


            struct item* Newnode=(struct item*)(malloc(sizeof(struct item)));
            printf("\nEnter item id: ");
            scanf("%d",&itemid);
            fflush(stdin);
            printf("\nEnter name of the item: ");
            fgets(name,sizeof name,stdin);
            //printf("string is: %s\n", name);
            printf("\nEnter price: ");
            scanf("%f",&price);
            strcpy(Newnode->name,name);
            Newnode->itemid=itemid;
            Newnode->price=price;
            Newnode->next=NULL;


            if(menuIndex->front==NULL)
            {
                menuIndex->front=Newnode;
                struct item* temp;
                temp=menuIndex->front;

                printf("\nMenu item added successfully");
            }
            else
            {

                struct item* temp = menuIndex->front;
                while(temp->next!=NULL)
                {

                    temp=temp->next;
                }
                temp->next=Newnode;

                printf("\nMenu item added successfully");
            }

        }
        else
        {
            break;
        }
    }


}
//display menu
void displayMenu()
{
    if(menuIndex == NULL || menuIndex->front == NULL)
    {
        printf("\nNo menu to display");
    }
    struct item*temp=menuIndex->front;
    printf("\n====================MENU====================\n");
    while(temp!=NULL)
    {

        printf("\n%d %s %f ",temp->itemid,temp->name,temp->price );
        printf("\n");
        temp=temp->next;
    }
    printf("============================================");
}

//ORDER--------------------------------------------------------------------------------------------------------------------------
//node of the queue
struct orderitem
{
    int itemid;
    char name[50];
    int quantity;
    struct orderitem*next;
};
//queue
struct orderqueueItem
{
    char custname[100];
    char address[100];
    int orderid;
    int orderStatus;
    struct deliveryper*dp;
    struct orderitem*front;
    struct orderqueueItem*next;


};

struct orderList
{
    struct orderqueueItem*front;

};
struct orderList*OrderList;//---memory declared in main

struct pastOrderList
{
    struct orderqueueItem*front;

};
struct pastOrderList* PastOrderList;//---memory declared in main

void insertOrder()
{

    //per order
    struct orderqueueItem*OrderqueueItem=(struct orderqueueItem*)(malloc(sizeof(struct orderqueueItem)));
    char custname[100];
    char address[100];
    printf("Enter your name: ");
    fflush(stdin);
    fgets(custname,sizeof custname,stdin);
    printf("Enter customer address: ");
    fgets(address,sizeof address,stdin);
    strcpy(OrderqueueItem->custname,custname);
    strcpy(OrderqueueItem->address,address);
    OrderqueueItem->front = NULL;
    OrderqueueItem->next = NULL;
    //inputting food in first order
    int itemid;
    char name[50];
    int quantity;
    displayMenu();
    while(1)
    {
        char choice;
        fflush(stdin);
        printf("\ndo you want to enter items?(y/n): ");
        scanf("%c",&choice);
        //loop to enter food choices per order
        if(choice=='Y'||choice=='y')
        {
            struct orderitem*Newnode=(struct orderitem*)(malloc(sizeof(struct orderitem)));

            printf("\nenter the item id from the menu: ");
            scanf("%d",&itemid);
            fflush(stdin);
            printf("\nenter the name of the dish: ");
            fgets(name,sizeof name,stdin);
            printf("\nenter quantity of the dish: ");
            scanf("%d",&quantity);
            Newnode->itemid=itemid;
            strcpy(Newnode->name,name);
            Newnode->quantity=quantity;
            Newnode->next=NULL;





            //first food item
            if(OrderqueueItem->front==NULL)
            {
                OrderqueueItem->front=Newnode;
            }
            else  //other food items
            {


                struct orderitem*temp=OrderqueueItem->front;
                while(temp->next!=NULL)
                {
                    temp=temp->next;

                }
                temp->next=Newnode;

            }
        }
        else
        {
            break;
        }



    }

    printf("Adding Order to Order List");
    currentOrderId++;
    OrderqueueItem->orderid = currentOrderId;
    OrderqueueItem->orderStatus = orderInprogress;


    if(OrderList->front==NULL)
    {

        OrderList->front=OrderqueueItem;
        //OrderList->front=OrderqueueItem;
    }
    else  //other nodes
    {

        struct orderqueueItem*temp=OrderList->front;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=OrderqueueItem;
    }


}
void displayOrderList(int current)
{

    struct orderqueueItem* orderqueueItem = NULL;
    if(current == 0)
    {
        if(PastOrderList == NULL || PastOrderList->front == NULL)
        {
            printf("\n There is no Past Order to display");
            return;
        }
        orderqueueItem=PastOrderList->front;
        printf("\n ======== PRINTING PAST ORDERS ======================= \n");

    }
    else
    {
        if(OrderList == NULL || OrderList->front == NULL)
        {
            printf("\n There is no Order to display");
            return;
        }
        printf("\n ======== PRINTING CURRENT ORDERS ======================= \n");
        orderqueueItem=OrderList->front;

    }




    if(orderqueueItem == NULL || orderqueueItem->front == NULL)
    {
        printf("There is no Orderqueue to display");
        return;
    }


    while(orderqueueItem!=NULL)
    {
        printf("\n ======== PRINTING ORDER ======================= \n");
        printf("Order ID is : %d", orderqueueItem->orderid);
        if(orderqueueItem->orderStatus==1)
        {
            printf("Order Status is : In progress");

        }
        else if(orderqueueItem->orderStatus==2)
        {
            printf("Order Status is : Assigned to delivery person");
        }
        printf("\n Customer Name : %s",orderqueueItem->custname);
        printf("\n customer Address : %s",orderqueueItem->address);
        struct orderitem*orderitem=orderqueueItem->front;
        while(orderitem!=NULL)
        {
            printf("\n--------- PRINTING ITEMLIST------------  \n");

            printf("item id:%d \n",orderitem->itemid);
            printf("item name:%s \n",orderitem->name);
            printf("Quantity:%d \n",orderitem->quantity);
            orderitem=orderitem->next;

        }
        orderqueueItem=orderqueueItem->next;
    }

}

void insertDelivery()
{
    char name[50];
    int id;


    while(1)
    {
        char choice;
        fflush(stdin);
        printf("do you want to enter delivery profiles?(y/n): ");
        scanf("%c",&choice);

        if(choice=='Y'||choice=='y')
        {
            struct deliveryper*Newnode=(struct deliveryper*)(malloc(sizeof(struct deliveryper)));

            fflush(stdin);
            printf("enter name of the delivery person: ");
            fgets(name,sizeof name,stdin);
            printf("enter id of the delivery person : ");
            scanf("%d",&id);
            Newnode->id=id;
            strcpy(Newnode->name,name);
            Newnode->next=NULL;
            //first node
            if(Deliqueue->front==NULL)
            {
                Deliqueue->front=Newnode;
            }
            else  //other nodes
            {
                struct deliveryper*temp=Deliqueue->front;
                while(temp->next!=NULL)
                {
                    temp=temp->next;
                }
                temp->next=Newnode;
            }
        }
        else
        {
            break;
        }



    }
}

void displayDelivery()
{
    if(Deliqueue->front == NULL)
    {
        printf("\n No delivery people to display");
    }
    printf("\n the delivery people queue is:");
    struct deliveryper*temp=Deliqueue->front;
    while(temp!=NULL)
    {
        printf("\n Delivery person Name is : %s ",temp->name);
        printf("\n Delivery person id is : %d ",temp->id);
        temp=temp->next;
    }
}
void deleteDelivery()
{
    if(Deliqueue != NULL && Deliqueue->front != NULL)
    {
        struct deliveryper*temp=Deliqueue->front;
        Deliqueue->front=temp->next;
        free(temp);
    }

}
void AssignOrder()
{
    //Get the first In progress order
    struct orderqueueItem* orderQueueItem=OrderList->front;
    struct deliveryper*deliveryper=Deliqueue->front;
    while(orderQueueItem != NULL )
    {
        if(orderQueueItem->orderStatus!=orderAssigned)
        {
            deliveryper = Deliqueue->front;
            printf("\n Order Status is : %d ", orderQueueItem->orderStatus );
            if(deliveryper != NULL)
            {
                printf("\n Assigning Delivery Person : %s to Order no : %d ", deliveryper->name,orderQueueItem->orderid );

                orderQueueItem->dp=deliveryper;
                orderQueueItem->orderStatus = orderAssigned;
                Deliqueue->front=deliveryper->next;
                deliveryper->next = NULL;
            }
            else
            {
                printf("\n Delivery person Not available" );
                return;
            }

            orderQueueItem=orderQueueItem->next;
        }
        else
        {
            printf("\n Order Status already assigned So moving on...");
            orderQueueItem=orderQueueItem->next;
        }

        /*if(orderQueueItem != NULL)
        {
            printf("\n next order item status is : %d ",orderQueueItem->orderStatus  );
        }
        else
        {
            printf("\n next order item  is NULL " );
        }*/



    }
    printf("\n  Order Assignment Done !!!!!!!!!!!!!!!!!!!!!" );
    //Get the first avaiable delivery person
    //Assign the order to delivery person
    //Update status as in progress delivery
}
void CompleteOrder(int orderId)
{
    //search for order with order id

    struct orderqueueItem* tempOrderqueueItem=OrderList->front;
    struct orderqueueItem* prev = OrderList->front;
    printf("\n Entered Completing Order Number : %d ",orderId);
    while(tempOrderqueueItem != NULL )
    {
        //prev = orderqueueItem;

        if(tempOrderqueueItem->orderid == orderId)
        {
            printf("\n Completing Order Number : %d", orderId );
            if(Deliqueue->front==NULL)
            {
                if(tempOrderqueueItem->dp != NULL)
                {

                    tempOrderqueueItem->dp->next = NULL;
                    Deliqueue->front=tempOrderqueueItem->dp;
                }
                else
                {
                    printf("\n No delivery person exist in order");
                }

            }
            else  //other nodes
            {
                struct deliveryper*deliveryper=Deliqueue->front;
                while(deliveryper->next!=NULL)
                {
                    deliveryper=deliveryper->next;
                }
                deliveryper->next=tempOrderqueueItem->dp;
                printf("\n Added Delivery person to end of queue");
            }

            //delete order from order list
            if(OrderList->front->orderid == tempOrderqueueItem->orderid)
            {

                OrderList->front = tempOrderqueueItem->next;
            }
            else
            {

                prev->next = tempOrderqueueItem->next;
            }
            tempOrderqueueItem->next = NULL;
            if(PastOrderList->front==NULL)
            {
                printf("\n Inserting Past First Order");
                PastOrderList->front=tempOrderqueueItem;
            }
            else  //other nodes
            {
                printf("\n Inserting Past next order");
                struct orderqueueItem* pastOrderList=PastOrderList->front;
                while(pastOrderList->next!=NULL)
                {
                    pastOrderList=pastOrderList->next;
                }
                pastOrderList->next=tempOrderqueueItem;
            }



        }
        else
        {
            printf("\n Not matching id so traversing to next order");


        }
        prev = tempOrderqueueItem;
        tempOrderqueueItem=tempOrderqueueItem->next;


    }
}

void checkStatus(int orderId)
{
    struct orderqueueItem*temp=OrderList->front;
    if(temp != NULL)
    {
        while(temp!=NULL)
        {
            if(temp->orderid==orderId)
            {
                if(temp->orderStatus==1)
                {
                    printf("Order is in progress");

                }
                else if(temp->orderStatus==2)
                {
                    printf("Order is out for delivery");

                }
                return;
            }
            temp=temp->next;
        }
    }


    temp=PastOrderList->front;
    while(temp!=NULL)
    {
        if(temp->orderid==orderId)
        {
            if(temp->orderStatus==2)
            {
                printf("Order is complete and delivered");

            }
            else
            {
                printf("order is invalid,enter a valid order");

            }
            return;
        }
        temp=temp->next;
    }

    if(temp == NULL)
    {
        printf("Order doen't exist");
    }
}
int main()
{
    if(menuIndex == NULL)
    {
        menuIndex = (struct menu*)(malloc(sizeof(struct menu)));
        menuIndex->front = NULL;
    }

    if(OrderList == NULL)
    {
        OrderList= (struct orderList*)(malloc(sizeof(struct orderList)));
        OrderList->front = NULL;
    }
    if(PastOrderList == NULL)
    {
        PastOrderList= (struct orderList*)(malloc(sizeof(struct pastOrderList)));
        PastOrderList->front = NULL;
    }

    if(Deliqueue == NULL)
    {
        Deliqueue = (struct deliqueue*)(malloc(sizeof(struct deliveryper)));
        Deliqueue->front = NULL;
    }


    while(1)
    {
        int choice;
        int choice2;
        printf("\nAre you:\n1.Hotel management\n2.Customer\n3.Delivery agent\n4.exit:: \n Option chosen is : ");
        scanf("%d",&choice);
        switch(choice)
        {
        //Hotel

        case 1:

            printf("\nEnter:\n1.Menu management\n2.Delivery Agent Management\n3.view orders.\n4.Assign Orders:: \n Option chosen is : ");

            scanf("%d",&choice2);


            if(choice2==1)
            {
                int menuchoice;
                printf("\n1.Enter menu\n2.Display menu :: \n Option chosen is :");
                scanf("%d",&menuchoice);
                if(menuchoice==1)
                {
                    printf("\nInserting Menu");
                    insertMenu();
                    printf("\nMenu has been successfully created");
                }
                else if(menuchoice==2)
                {
                    displayMenu();
                }

                else
                {
                    printf("\nenter valid input");
                }
            }
            else if(choice2==2)
            {
                insertDelivery();
            }
            else if(choice2==3)
            {
                int orderview;
                printf("\n1.for current orders,2.past orders::");
                scanf("%d",&orderview);
                if(orderview==1)
                {
                    displayOrderList(1);
                }
                else if(orderview==2)
                {
                    displayOrderList(0);
                }
                else
                {
                    printf("\nenter valid input");
                }
            }

            else if(choice2 == 4)
            {
                AssignOrder();
            }
            else
            {
                printf("\nenter valid input!");
            }

            break;;
        //customer

        case 2:

            printf("\nEnter:\n1.Place a new order\n2.Check status of placed order:: \n Option chosen is :");
            scanf("%d",&choice2);
            if(choice2==1)
            {
                insertOrder();
            }
            else if(choice2==2)
            {
                int Orderidtocheck;
                printf("\nEnter order id to check:");
                scanf("%d",&Orderidtocheck);
                checkStatus(Orderidtocheck);
            }
            else
            {
                printf("\nenter valid input");
            }
            break;
        //delivery person

        case 3:
            printf("\nEnter order id to complete: \n Option chosen is :  ");
            scanf("%d",&choice2);
            CompleteOrder(choice2);

            break;
        case 4:
            printf("\nBye-bye");
            exit(0);
            break;
        default:
            printf("\nenter valid input");
        }
    }


    return 0;
}


