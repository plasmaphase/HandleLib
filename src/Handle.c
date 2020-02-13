
#include "Handle.h"

//Primary handle for this library, hidden in the C
//file so the user isn't aware of its contents
typedef struct {
    bool initialized;
    uint32_t numEntries;  //number of entries available in the array
    void *data;           //pointer to array of data
    uint32_t upperbound;  //maximum value of any given random number
    uint32_t lowerbound;  //minimum value of any given random number
} h_HandleParams_t;

M_CompileTimeAssert(HANDLE_SIZE==sizeof(h_HandleParams_t));

uint32_t randRange( uint32_t lower, uint32_t upper )
{
   return ( rand( ) % ( upper - lower + 1 ) ) + lower;
}

bool h_HandleInit(void *_pHandle, h_HandleInitParams_t *pInitParams)
{
    if(_pHandle == NULL || pInitParams == NULL)
        return false;

    h_HandleParams_t* pHandle = (h_HandleParams_t*)_pHandle;
    pHandle->data = pInitParams->data;
    pHandle->numEntries = pInitParams->numEntries;
    pHandle->lowerbound = pInitParams->lowerbound;
    pHandle->upperbound = pInitParams->upperbound;
    
    return true;
}

bool h_HandleGenerate(void *_pHandle, uint32_t numRandoms)
{
    if(_pHandle == NULL)
        return false;

    h_HandleParams_t* pHandle = (h_HandleParams_t*)_pHandle;
    uint32_t *Data = (uint32_t*)pHandle->data;
    
    if(pHandle->numEntries < numRandoms)
        return false;

    for(uint32_t i = 0;i < pHandle->numEntries;i++)
    {
        *Data = randRange(pHandle->lowerbound, pHandle->upperbound);
        Data++;
    }

    return true;
}

uint32_t h_GetNumEntries(void *_pHandle)
{
    h_HandleParams_t* pHandle = (h_HandleParams_t*)_pHandle;
    if(pHandle != NULL)
    {
        return pHandle->numEntries;
    }
    return -1;
}