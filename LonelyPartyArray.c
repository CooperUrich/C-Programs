#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"


// Function 1
LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
    int i, size;
    
    LonelyPartyArray *party;
    
    if (num_fragments > 0 && fragment_length > 0)
    {
        party = malloc(sizeof(LonelyPartyArray));
        
        if (party == NULL)
            return NULL;
        
        // Set to 0 because no cells have been used yet
        party->size = 0;
        
        party->num_fragments = num_fragments;
        party->fragment_length = fragment_length;
        
        // No active fragments yet
        party->num_active_fragments = 0;
        party->fragments = malloc(sizeof(int*) * num_fragments);
        
        // if the pointers to the fragments have no value, it frees the memory and returns NULL
        if (party->fragments == NULL)
        {
            free(party->fragments);
            return NULL;
        }
        
        // Setting up the individual fragments to NULL
        for (i = 0; i < num_fragments; i++)
            party->fragments[i] = NULL;
        
        // Allocating the number of fragments
        party->fragment_sizes = malloc(sizeof(int) * num_fragments);
        
        // if the fragment size has no value, it frees the memory and returns NULL
        if (party->fragment_sizes == NULL)
        {
            free(party->fragments);
            free(party->fragment_sizes);
            return NULL;
        }
        // Setting the sizes to 0 since there are no initialized cells
        for (i = 0; i < num_fragments; i++)
            party->fragment_sizes[i] = 0;
        
        printf("-> A new LonelyPartyArray has emerged from the void." );
        printf(" (capacity: %d, fragments: %d)\n",(party->fragment_length * party->num_fragments), party->num_fragments);
    }
    else
        return NULL;
    
    return party;
}

// Function 2
LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
    int i;
    
    if (party == NULL)
        return NULL;
    
    // Destroying each fragments
    if (party->fragments != NULL)
    {
        for (i = 0; i < party->num_fragments;i++)
        {
            if (party->fragments[i] != NULL)
                free(party->fragments[i]);
        }
    }
    // Freeing the memory in the array
    if (party->fragment_sizes != NULL)
    {
        free(party->fragment_sizes);
        free(party->fragments);
        free(party);
    }
    
    printf("-> The LonelyPartyArray has returned to the void.\n");
    return NULL;
    
}


// Function 3
int set(LonelyPartyArray *party, int index, int key)
{
    int i, fragment_number, new_fragment_location, length, index_bound, first_index, fin_index;
    
    if (party == NULL)
    {
        printf("-> Bloop! NULL pointer detected in set().\n");
        return LPA_FAILURE;
    }
    // Initializing the integers
    fragment_number = index / party->fragment_length;
    new_fragment_location = index % party->fragment_length;
    length = party->fragment_length;
    index_bound = party->num_fragments * party->fragment_length - 1;
    first_index = length * fragment_number;
    fin_index = (fragment_number + 1) * length - 1;
    
    if (index >= 0 && index <= index_bound)
    {
        // if the frag where the key is null, dynamically allocate space
        if (party->fragments[fragment_number] == NULL)
        {
            party->fragments[fragment_number] = malloc(sizeof(int) * length);
            
            for (i = 0; i < length; i++)
                party->fragments[fragment_number][i] = UNUSED;
            
            party->num_active_fragments += 1;
            
            printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n",fragment_number, length, first_index, fin_index);
        }
        // Putting the key in the specified fragment
        if (party->fragments[fragment_number][new_fragment_location] == UNUSED)
        {
            party->fragments[fragment_number][new_fragment_location] = key;
            party->size++;
            party->fragment_sizes[fragment_number]++;
            return LPA_SUCCESS;
        }
        // Putting the key into the index but it was already being used
        if (party->fragments[fragment_number][new_fragment_location] != UNUSED)
        {
            party->fragments[fragment_number][new_fragment_location] = key;
            return LPA_SUCCESS;
        }
    }
    else
    {
        printf("-> Bloop! Invalid access in set().");
        printf(" (index: %d, fragment: %d, offset: %d)\n", index, fragment_number, new_fragment_location);
        return LPA_FAILURE;
    }
}


// Function 4
int get(LonelyPartyArray *party, int index)
{
    int i, fragment_number, new_fragment_location, length, index_bound;
    
    if (party == NULL)
    {
        printf("-> Bloop! NULL pointer detected in get().\n");
        return LPA_FAILURE;
    }
    
    fragment_number = index / party->fragment_length;
    new_fragment_location = index % party->fragment_length;
    index_bound = party->num_fragments * party->fragment_length;
    
    if (index < 0 || index >= index_bound)
    {
        printf("-> Bloop! Invalid access in get().");
        printf(" (index: %d, fragment: %d, offset: %d)\n", index, fragment_number, new_fragment_location);
        return LPA_FAILURE;
    }
    
    if (party != NULL)
    {
        if (index >= 0 && index < index_bound)
        {
            if (party->fragments[fragment_number] == NULL)
                return UNUSED;
            // Returning the key
            else
                return party->fragments[fragment_number][new_fragment_location];
        }
        
    }
}




// Function 5
int delete(LonelyPartyArray *party, int index)
{
    int fragment_number, new_fragment_location, length, index_bound,first_index, fin_index;
    
    if (party == NULL)
    {
        printf("-> Bloop! NULL pointer detected in delete().\n");
        return LPA_FAILURE;
    }
    
    
    if (party != NULL)
    {
        // Initializing the variables
        fragment_number = index / party->fragment_length;
        new_fragment_location = index % party->fragment_length;
        length = party->fragment_length;
        index_bound = party->num_fragments * party->fragment_length;
        first_index = length * fragment_number;
        fin_index = (fragment_number + 1) * length - 1;
        
        if (index < 0 || index >= index_bound)
        {
            printf("-> Bloop! Invalid access in delete().");
            printf(" (index: %d, fragment: %d, offset: %d)\n", index, fragment_number, new_fragment_location);
            return LPA_FAILURE;
        }
        
        if (party->fragments[fragment_number] == NULL)
            return LPA_FAILURE;
        
        
        if (index >= 0 && index < index_bound)
        {
            if (party->fragments[fragment_number][new_fragment_location] == UNUSED)
                return LPA_FAILURE;
            // Decrementing the the sizes and fragment numbers
            if (party->fragments[fragment_number][new_fragment_location] != UNUSED)
            {
                party->fragments[fragment_number][new_fragment_location] = UNUSED;
                party->size--;
                party->fragment_sizes[fragment_number]--;
            }
            // Freeing the fragment
            if (party->fragment_sizes[fragment_number] == 0)
            {
                free(party->fragments[fragment_number]);
                party->num_active_fragments--;
                party->fragments[fragment_number] = NULL;
                printf("-> Deallocated fragment %d.", fragment_number);
                printf(" (capacity: %d, indices: %d..%d)\n", length, first_index, fin_index);
            }
            return LPA_SUCCESS;
        }
    }
}

// function 6
int containsKey(LonelyPartyArray *party, int key)
{
    int i, j;
    // cycling throug the LPA to find the key
    for (i = 0; i < party->num_fragments; i++)
    {
        for (j = 0; j < party->fragment_length; j++)
        {
            if (party->fragments[i][j] == key)
                return 1;
        }
    }
    return 0;
}

// Function 7
int isSet(LonelyPartyArray *party, int index)
{
    int i, fragment_number, new_fragment_location, length, index_bound;
    
    if (party == NULL)
        return 0;
    
    fragment_number = index / party->fragment_length;
    new_fragment_location = index % party->fragment_length;
    index_bound = (party->num_fragments * party->fragment_length);
    
    if (party != NULL)
    {
        if (index >= 0 && index < index_bound)
        {
            // Checks to see if the key is an integer
            if (party->fragments[fragment_number][new_fragment_location] == UNUSED)
                return 0;
            
            else
                return 1;
            
            if (party->fragments[fragment_number] == NULL)
                return 0;
        }
        if (index < 0 || index > index_bound)
        {
            return 0;
        }
    }
}

// Function 8
int printIfValid(LonelyPartyArray *party, int index)
{
    int i, fragment_number, new_fragment_location, index_bound;
    
    if (party == NULL)
        return LPA_FAILURE;
    
    fragment_number = index / party->fragment_length;
    new_fragment_location = index % party->fragment_length;
    index_bound = (party->num_fragments * party->fragment_length);
    
    if (index < 0 || index >= index_bound)
        return LPA_FAILURE;
    
    if (index >= 0 && index < index_bound)
    {
        if (party->fragments[fragment_number] == NULL || party->fragments[fragment_number][new_fragment_location] == UNUSED)
            return LPA_FAILURE;
        // Prints the key if the index is valid
        if (party->fragments[fragment_number] != NULL && party->fragments[fragment_number][new_fragment_location] != UNUSED)
        {
            printf("%d\n", party->fragments[fragment_number][new_fragment_location]);
            return LPA_SUCCESS;
        }
    }
}

// Function 9
LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
    int i, j;
    
    if (party == NULL)
    {
        printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
        return party;
    }
    // Freeing all of the memory (kind of like delete) and reseting the values
    if (party != NULL)
    {
        for (i = 0; i < party->num_fragments; i++)
        {
            if (party->fragments[i] != NULL)
            {
                free(party->fragments[i]);
                party->fragments[i] = NULL;
                party->fragment_sizes[i] = 0;
            }
        }
        
        party->num_active_fragments = 0;
        party->size = 0;
        printf("-> The LonelyPartyArray has returned to its nascent state.");
        printf(" (capacity: %d, fragments: %d)\n", party->fragment_length * party->num_fragments, party->num_fragments);
        return party;
    }
}
// Double check Function 9 in the cave

// Function 10
int getSize(LonelyPartyArray *party)
{
    if (party == NULL)
        return -1;
    // Return size
    if (party != NULL)
        return party->size;
}

// Function 11
int getCapacity(LonelyPartyArray *party)
{
    int prod;
    
    if (party == NULL)
        return -1;
    
    prod = (party->num_fragments*party->fragment_length);
    // prod returns capacity
    if (party != NULL)
        return prod;
}

// Function 12
int getAllocatedCellCount(LonelyPartyArray *party)
{
    int i;
    int k = 0;
    // Returns the active fragments
    if (party != NULL)
    {
        return party->num_active_fragments * party->fragment_length;
    }
    if (party == NULL)
        return -1;
}

// Function 13
long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
    int array_size;
    
    if (party == NULL)
        return 0;
    // How much memory the program would take up if an array was used
    array_size = party->num_fragments * party->fragment_length;
    return (array_size * (long long unsigned int) sizeof(int));
}
// Function 14
long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
    long long unsigned int size = 0;
    
    if (party == NULL)
        return -1;
    // How much memory the LPA takes up
    size += sizeof(LonelyPartyArray*);
    size += sizeof(LonelyPartyArray);
    size += (long long unsigned int)sizeof(int*) * party->num_fragments;
    size += (long long unsigned int)sizeof(int) * party->num_fragments;
    size += (long long unsigned int)sizeof(int) * party->num_active_fragments * party->fragment_length;
    
    return size;
}

// LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party)
// {
//
// }


