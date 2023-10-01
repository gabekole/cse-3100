#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum TYPE {S, I, R};

//idx returns an integer to be used for hashing
//this integer should be unique for every x, y pair in your grid
int idx(int x, int y, int k)
{
	// Side length is 2*k + 1 since distance from center to edge is k
	return y*(2*k+1) + x;
}

typedef struct Host
{
	int id;
	int x, y;
	int t;
	enum TYPE type;
} THost;


typedef struct node_tag {
   THost host;				
   struct node_tag * next;
} node;

//create a node whose value is a specific host
//return a pointer to the created node
node *create_node(THost host) // Switched to use stack instead of heap 
{
	node *temp = malloc(sizeof(node));
	temp->host = host;
	temp->next = NULL; 
	return temp;
}

//add_first() should add to the beginning of a linked list
//note the type: 'node **head'
//note that it does not return a value 
void add_first(node **head, node *newnode)
{
	if(head == NULL)// There is an error (list not initialized properly)
	{
		return;
	}
	else
	{
		node *temp = *head;
		*head = newnode;
		(*head)->next = temp;
	}
}


//remove the first node from the list
//note the type: 'node **head'
//return a pointer to the removed content
// MUST BE FREED BY USER
node * remove_first(node **head) 
{
	node * first = *head;

	*head = (*head)->next;

	return first;
}

//remove all the nodes in the list
//and free all the allocated memory
void remove_recursive(node *head)
{
	if(head == NULL)
		return;

	remove_recursive(head->next);
	free(head);
}

void remove_all(node **head)
{
	// remove_recursive(*head);
	*head = NULL;
}

//location_match checks whether a linked list contains
//one or more hosts in the same location as 'host'
//return 1 if there is a match, 0 if not
int location_match(node *head, THost host)
{
	
	node *current = head;
	while(current != NULL)
	{
		THost currentHost = current->host;

		if (currentHost.x == host.x && currentHost.y == host.y)
			return 1;
	}
	return 0;
}


//hash function included for your convenience :)
unsigned hash(unsigned a)
{
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}
//summary prints out the proportions of different host types.
//It returns 1 if the number of infected hosts is not 0. 
int summary(THost hosts[], int m)
{   
    int S_n, I_n, R_n;
    
    S_n = I_n = R_n = 0;
    for(int i = 0; i < m; i++)
    {   
        S_n += (hosts[i].type == S);
        I_n += (hosts[i].type == I);
        R_n += (hosts[i].type == R);
    }
	if(I_n == 0)
	{
		printf("    S        I        R\n");
    	printf("%lf %lf %lf\n", (double)S_n/(S_n + I_n + R_n), 
		(double)I_n/(S_n + I_n + R_n), (double)R_n/(S_n + I_n + R_n));
	}
	return I_n > 0;
}

// one_round 
int one_round(THost *hosts, int m, node *p_arr[], int n_arr, int k, int T)
{
	// Colision and time update
	for(int i = 0; i < m; i++)
	{
		if(hosts[i].type == I)
		{
			if(hosts[i].t == T)
			{	
				hosts[i].type = R;
			}
			hosts[i].t += 1;
		}
		else if(hosts[i].type == S)
		{
			unsigned int hash_index = hash(idx(hosts[i].x, hosts[i].y, k)) % n_arr;

			node *hosts_in_location = p_arr[hash_index];

			if(location_match(hosts_in_location, hosts[i]))
			{
				hosts[i].type = I;
				hosts[i].t = 0;
			} 
		}
	}
	

	// Update location
	for(int i = 0; i < m; i++)
	{
		int dir = rand() % 4;

		int x = hosts[i].x;
		int y = hosts[i].y;
		switch(dir)
		{
			case 0: hosts[i].y = ((y + k + 1) % (2*k+1)) - k; break;
			case 1: hosts[i].x = ((x + k + 1) % (2*k+1)) - k; break;
			case 2: hosts[i].y = ((y + k - 1) % (2*k+1)) - k; break;
			case 3: hosts[i].x = ((x + k - 1) % (2*k+1)) - k; break;
		}
	}


	// Update Hashmap
	for(int i = 0; i < m; i++)
	{
		remove_all(&p_arr[i]);
	}
	for(int i = 0; i < m; i++)
	{
		if(hosts[i].type == I)
		{
			node *r = create_node(hosts[i]);
			int index = hash(idx(hosts[i].x, hosts[i].y, k)) % n_arr;
			add_first(&(p_arr[index]), r);
		}
	}

	return summary(hosts, m);
}

int main(int argc, char *argv[])
{

	if(argc != 5)
	{
		printf("Usage: %s k m T N\n", argv[0]);
		return 0;
	}

	int k = atoi(argv[1]);
	int m = atoi(argv[2]);
	int T = atoi(argv[3]);
	int N = atoi(argv[4]);

	assert(k >= 0 && k <= 1000);
	assert(m >= 1 && m <= 100000);
	assert(T >= 1);
	assert(N > 0 && N <= 100000);
	srand(12345);

	//initialize hosts
	THost hosts[m];

	hosts[0].id = 0;
	hosts[0].x = 0;
	hosts[0].y = 0;
	hosts[0].t = 0;
	hosts[0].type = I;

	for(int i = 1; i < m; i ++)
	{
		hosts[i].id = i;
		hosts[i].x = rand() % (2*k + 1) - k;
		hosts[i].y = rand() % (2*k + 1) - k;
		hosts[i].t = 0;
		hosts[i].type = S;		
	}

	//initialize linked lists
	node *p_arr[N];

	for(int i = 0; i < N; i++)
	{
		p_arr[i] = NULL;
	}
	node *r = create_node(hosts[0]);
	int index = hash(idx(hosts[0].x, hosts[0].y, k)) % N;
	add_first(&(p_arr[index]), r);

	//simulation
	one_round(hosts, m, p_arr, N, k, T);
	// fails with 2 2 2 4
	one_round(hosts, m, p_arr, N, k, T);

	return 0;
}
