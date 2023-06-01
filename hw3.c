#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct node
{
    struct node *r_node;
    unsigned value;
} node;

typedef struct hash_table
{
    node **list;
    unsigned nof_element;
} hash_table;

typedef struct parameterPass
{
    unsigned *numbers;
    hash_table *ht;
    unsigned tid;
    unsigned interval;
    unsigned last_ele;
    pthread_mutex_t *lock;
} parameterPass;

unsigned countNumOfElements(char *filename);
unsigned *readNumbers(char *filename, unsigned num_element);
hash_table *initializeHashTable(unsigned numOfThread, unsigned numOfElements);
void *insertionFunction(void *parameters);
void swap(node *a, node *b);
void bubbleSort(node *start);
void *sort(void *param);

unsigned countNumOfElements(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    unsigned count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        count++;
    }

    fclose(file);
    return count;
}

unsigned *readNumbers(char *filename, unsigned num_element)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return NULL;
    }

    unsigned *numbers = (unsigned *)malloc(num_element * sizeof(unsigned));
    if (numbers == NULL)
    {
        printf("Error allocating memory.\n");
        fclose(file);
        return NULL;
    }

    unsigned i = 0;
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        sscanf(line, "%u", &numbers[i]);
        i++;
    }

    fclose(file);
    return numbers;
}

hash_table *initializeHashTable(unsigned numOfThread, unsigned numOfElements)
{
    hash_table *ht = (hash_table *)malloc(sizeof(hash_table));
    if (ht == NULL)
    {
        printf("Error allocating memory for hash table.\n");
        return NULL;
    }

    ht->list = (node **)calloc(numOfThread * (numOfThread + 1) / 2, sizeof(node *));
    if (ht->list == NULL)
    {
        printf("Error allocating memory for hash table list.\n");
        free(ht);
        return NULL;
    }

    ht->nof_element = numOfElements;
    return ht;
}

void *insertionFunction(void *parameters)
{
    parameterPass *params = (parameterPass *)parameters;

    for (unsigned i = params->tid * params->interval; i < params->last_ele; i++)
    {
        unsigned index = (params->tid * (params->tid + 1)) / 2;
        index += params->numbers[i] % (params->tid + 1);

        node *new_node = (node *)malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Error allocating memory for node.\n");
            return NULL;
        }
        new_node->value = params->numbers[i];
        new_node->r_node = NULL;

        // Lock the thread to safely insert new_node into the linked list
        pthread_mutex_lock(&params->lock[index]);

        if (params->ht->list[index] == NULL)
        {
            params->ht->list[index] = new_node;
        }
        else
        {
            node *curr = params->ht->list[index];
            while (curr->r_node != NULL)
            {
                curr = curr->r_node;
            }
            curr->r_node = new_node;
        }

        // Unlock the thread after insertion
        pthread_mutex_unlock(&params->lock[index]);
    }

    return NULL;
}

void swap(node *a, node *b)
{
    unsigned temp = a->value;
    a->value = b->value;
    b->value = temp;
}

void bubbleSort(node *start)
{
    int swapped;
    node *ptr1;
    node *lptr = NULL;

    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->r_node != lptr)
        {
            if (ptr1->value > ptr1->r_node->value)
            {
                swap(ptr1, ptr1->r_node);
                swapped = 1;
            }
            ptr1 = ptr1->r_node;
        }
        lptr = ptr1;
    } while (swapped);
}

void *sort(void *param){
	
	node* first= (node*)param;
	bubbleSort(first);
	return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./executable_name <numbers.csv> <numOfThreads>\n");
        return 1;
    }

    char *filename = argv[1];
    unsigned numOfThreads = atoi(argv[2]);

    unsigned numOfElements = countNumOfElements(filename);
    unsigned *numbers = readNumbers(filename, numOfElements);

    if (numbers == NULL)
    {
        printf("Error reading numbers.\n");
        return 1;
    }

    hash_table *ht = initializeHashTable(numOfThreads, numOfElements);
    if (ht == NULL)
    {
        printf("Error initializing hash table.\n");
        free(numbers);
        return 1;
    }

    pthread_t *threads = (pthread_t *)malloc(numOfThreads * sizeof(pthread_t));
    if (threads == NULL)
    {
        printf("Error creating threads.\n");
        free(numbers);
        free(ht->list);
        free(ht);
        return 1;
    }

    unsigned interval = numOfElements / numOfThreads + 1;

    pthread_mutex_t *locks = malloc((numOfThreads * (numOfThreads + 1) / 2) * sizeof(pthread_mutex_t));
    for (unsigned i = 0; i < numOfThreads * (numOfThreads + 1) / 2; ++i)
    {
        pthread_mutex_init(&locks[i], NULL);
    }

    for (unsigned i = 0; i < numOfThreads; i++)
    {
        parameterPass *params = (parameterPass *)malloc(sizeof(parameterPass));
        if (params == NULL)
        {
            printf("Error allocating memory for thread parameters.\n");
            free(numbers);
            free(ht->list);
            free(ht);
            for (unsigned j = 0; j < i; j++)
            {
                free(params);
            }
            free(threads);
            return 1;
        }

        params->numbers = numbers;
        params->ht = ht;
        params->tid = i;
        params->interval = interval;
        params->last_ele = params->tid * interval + interval;
        if (params->last_ele > numOfElements)
        {
            params->last_ele = numOfElements;
        }
        params->lock = locks;

        if (pthread_create(&threads[i], NULL, insertionFunction, params) != 0)
        {
            printf("Error creating thread.\n");
            free(numbers);
            free(ht->list);
            free(ht);
            for (unsigned j = 0; j <= i; j++)
            {
                free(params);
            }
            free(threads);
            return 1;
        }
    }

    for (unsigned i = 0; i < numOfThreads; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            printf("Error joining thread.\n");
            free(numbers);
            free(ht->list);
            free(ht);
            free(threads);
            return 1;
        }
    }
	//create threads for sorting
    pthread_t *sortThreads = (pthread_t *)malloc((numOfThreads * (numOfThreads + 1)/ 2) * sizeof(pthread_t));
    if (sortThreads == NULL)
    {
        printf("Error creating threads.\n");
        free(numbers);
        free(ht->list);
        free(ht);
        return 1;
    }
	
	
    for (unsigned i = 0; i < numOfThreads * (numOfThreads + 1) / 2; i++)
    {
		if (pthread_create(&sortThreads[i], NULL, sort, ht->list[i]) != 0)
        {
            printf("Error creating thread.\n");
            free(numbers);
            free(ht->list);
            free(ht);
            free(sortThreads);
            return 1;
        }
    }
	
	for (unsigned i = 0; i < numOfThreads * (numOfThreads + 1) / 2; i++)
    {
        if (pthread_join(sortThreads[i], NULL) != 0)
        {
            printf("Error joining thread.\n");
            free(numbers);
            free(ht->list);
            free(ht);
            free(sortThreads);
            return 1;
        }
    }

    // Print the sorted hash table
    for (unsigned i = 0; i < numOfThreads * (numOfThreads + 1) / 2; i++)
    {
        node *curr = ht->list[i];
        while (curr != NULL)
        {
            printf("%u ", curr->value);
            curr = curr->r_node;
        }
        printf("\n");
    }

    // Free allocated memory
    free(numbers);
    for (unsigned i = 0; i < numOfThreads * (numOfThreads + 1) / 2; i++)
    {
        node *curr = ht->list[i];
        while (curr != NULL)
        {
            node *temp = curr;
            curr = curr->r_node;
            free(temp);
        }
    }
    free(ht->list);
    free(ht);
    free(threads);
	free(sortThreads);
    for (unsigned i = 0; i < numOfThreads * (numOfThreads + 1) / 2; i++)
    {
        pthread_mutex_destroy(&locks[i]);
    }
    free(locks);

    return 0;
}
