#include <stdio.h>
#include <stdlib.h>

#define heapSize 2000

typedef struct datablock
{
	int size;           
	struct datablock * next;
}block;

block* heapBlock;

void Initialize_HeapBlock()
{
	heapBlock=malloc(heapSize);
	heapBlock->size=heapSize-sizeof(block);
	heapBlock->next=NULL;
}

block* freeList;

void Initialize_FreeList()
{ 
	freeList=heapBlock;
	freeList->size=heapSize;
	freeList->next=NULL;
}

block* Allocate(int req_size)
{
    block *curr,*prev,*result;
	curr=freeList;
	result=prev=NULL;

	while(curr!=NULL && curr->size < req_size)
	{
		prev=curr;
		curr=curr->next;
	}

	if(curr!=NULL)
	{
		if(curr->size > (req_size+sizeof(block)))
		{
			block* new=(block*)((void*)curr+req_size+sizeof(block));

			if(curr==freeList)
			{
				new->next=freeList->next;
				freeList=new;
            }
			else
			{
				new->next=curr->next;
				prev->next=new;
			}
			new->size=curr->size-req_size-sizeof(block);
			curr->size=req_size;
		}
		else
		{
			if(curr==freeList)
			{
				freeList=freeList->next;
			}
			else
			{
				prev->next=curr->next;
			}
		}
		result=(void*)((char*)curr+sizeof(block));
	}
	else
	{
			printf("Memory is exhausted");
	}
	return result;
}

void Free(block* ptr)
{
    if (ptr!=NULL)
    {
        block *temp,*prev,*target;
        target=ptr;
        target=(block*)((char*)target-sizeof(block));
        temp=freeList;
        prev=NULL;

        while(temp!=NULL && temp<target)
        {
            prev=temp;
            temp=temp->next;
        }
        if(prev!=NULL && ((block*)((char*)prev+prev->size+sizeof(block)))==target)
        {
            prev->size=prev->size+target->size+sizeof(block);
            if (temp!=NULL && ((block*)((char*)target+target->size+sizeof(block)))==temp)
            {
                prev->size=prev->size+temp->size+sizeof(block);
                prev->next=temp->next;
            }
        }
        else
        {
            if (temp!=NULL && ((block*)((char*)target+target->size+sizeof(block)))==temp)
            {
                target->size+=temp->size+sizeof(block);
                target->next=temp->next;

                if(prev!=NULL)
                {
                    prev->next=target;
                }
                else
                {
                    freeList=target;
                }
            }
            else
            {
                target->next=temp;
				if (prev!=NULL)
                {
                    prev->next=target;
                }
                else
                {
                    freeList=target;
                }
            }
        }
    }
    else
    {
        printf("The given block does not exist");
    }
}

void print_freeList()
{
	printf("Free List:\n");
	block* curr=freeList;
	while(curr!=NULL)
	{
		printf("[%d]->",curr->size);
		curr=curr->next;
	}
	printf("NULL");
	printf("\n");
}

int main()
{
	Initialize_HeapBlock();
	Initialize_FreeList();

	int size,choice;
	block* ptr;

	printf("Below is the Implementation of Heap Management using First Fit Strategy\n");
	printf("You have 3 Choices:\n1.Allocate Memory\n2.Free Memory\n3.Print Freelist\n4.Exit Program");

	while(1)
	{
		printf("\nEnter your Choice:");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
			printf("Enter the size of memory you want to allocate");
			scanf("%d",&size);
			ptr=Allocate(size);
			if (ptr != NULL) 
			{
                printf("Allocated memory at address %p\n", ptr);
            }
            break;

			case 2:
			printf("Enter address of memory to deallocate:");
            scanf("%p", &ptr);
            Free(ptr);
            printf("Memory deallocated\n");
            break;

			case 3:
			print_freeList();
			break;

			case 4:
			printf("Exiting the program\n");
			exit(0);

			default:
			printf("Invalid Entry\n");
		}
	}
	free(heapBlock);
}






