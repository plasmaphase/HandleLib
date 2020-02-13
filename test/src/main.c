
#include <assert.h>
#include <stdio.h>
#include "Handle.h"

#define MAX_NUM_HANDLES 10

uint32_t Rvals[MAX_NUM_HANDLES][MAX_SIZE];
uint8_t HandleMem[MAX_NUM_HANDLES][HANDLE_SIZE];

//helper function
uint32_t Range( uint32_t lower, uint32_t upper )
{
   return ( rand( ) % ( upper - lower + 1 ) ) + lower;
}

int main () 
{

    //initialize all the handles first
    for(uint32_t h = 0; h < MAX_NUM_HANDLES; h++)
    {
        printf("Handle Library Test\n");
        h_HandleInitParams_t initParams;
        void *pHandle = HandleMem[h];
        initParams.data = Rvals[h];
        initParams.numEntries = Range(1, MAX_SIZE);
        initParams.zeroInitialize = true;
        initParams.lowerbound = 12345;
        initParams.upperbound = 235643;

        h_HandleInit(pHandle, &initParams);
    }

    //run libraries
    for(uint32_t h = 0; h < MAX_NUM_HANDLES; h++)
    {
        printf("Running Handle %d\n", h);
        void *pHandle = HandleMem[h];
        //validate that the library zeroed out the array entries
        for (uint32_t i = 0; i < h_GetNumEntries(pHandle); i++)
        {
            assert(Rvals[h][i] == 0);
        }
        
        h_HandleGenerate(pHandle, h_GetNumEntries(pHandle));

        for (uint32_t i = 0; i < h_GetNumEntries(pHandle); i++)
        {
            printf("Rval %d: is %d\n", i, Rvals[h][i]);
        }
    }

}