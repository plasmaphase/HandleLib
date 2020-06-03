
#include "Handle.h"

//Primary handle for this library, hidden in the C
//file so the user isn't aware of its contents
typedef struct {
    bool initialized;
    uint32_t numEntries;  //number of entries available in the array
    void *data;           //pointer to array of data
    int32_t upperbound;  //maximum value of any given random number
    int32_t lowerbound;  //minimum value of any given random number
    int32_t min;         //minimum generated value in the list
    int32_t max;         //maximum generated value in the list
    int32_t avg;         //average across all the values in the list
} h_HandleParams_t;

M_CompileTimeAssert(HANDLE_SIZE==sizeof(h_HandleParams_t));

int32_t randRange( int32_t lower, int32_t upper )
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
    pHandle->min = INT32_MAX; //start off at the highest possible value to avoid false data
    pHandle->max = INT32_MIN; //start off at the lowest possible value to avoid false data
    pHandle->avg = 0;
    
    return true;
}

bool h_HandleGenerate(void *_pHandle, uint32_t numRandoms)
{
    int64_t sum = 0; 
    if(_pHandle == NULL)
        return false;

    h_HandleParams_t* pHandle = (h_HandleParams_t*)_pHandle;
    int32_t *Data = (int32_t*)pHandle->data;
    
    if(pHandle->numEntries < numRandoms)
        return false;

    for(uint32_t i = 0;i < pHandle->numEntries;i++)
    {
        int32_t tmpData = randRange(pHandle->lowerbound, pHandle->upperbound);
        if(pHandle->max < tmpData)
            pHandle->max = tmpData;
        if(pHandle->min > tmpData)
            pHandle->min = tmpData;
        sum += tmpData; //collect sum for average later
        *Data = tmpData;
        Data++;
    }
    //now we can calculate average
    pHandle->avg = (sum / pHandle->numEntries);

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

int32_t h_GetMinEntry(void *_pHandle)
{
    h_HandleParams_t* pHandle = (h_HandleParams_t*)_pHandle;
    return pHandle->min;
}

int32_t h_GetMaxEntry(void *_pHandle)
{
    h_HandleParams_t* pHandle = (h_HandleParams_t*)_pHandle;
    return pHandle->max;
}

int32_t h_GetAvg(void *_pHandle)
{
    h_HandleParams_t* pHandle = (h_HandleParams_t*)_pHandle;
    return pHandle->avg;
}