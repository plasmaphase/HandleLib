

#ifndef HANDLE_H
#define HANDLE_H

#if 0
#define UTPrint( ... ) printf(__VA_ARGS__)
#else
#define UTPrint( ... )
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "m_Assert.h"

#define MAX_SIZE 64
#define HANDLE_SIZE 40

typedef struct {
    uint32_t numEntries;  //number of entries available in the array
    void *data;           //pointer to array of data
    int32_t upperbound;  //maximum value of any given random number
    int32_t lowerbound;  //minimum value of any given random number
    bool zeroInitialize;  //indicates whether user wants array cleared out first
} h_HandleInitParams_t;

bool h_HandleInit(void *_pHandle, h_HandleInitParams_t *pInitParams);

bool h_HandleGenerate(void *_pHandle, uint32_t numRandoms);

uint32_t h_GetNumEntries(void *_pHandle);

int32_t h_GetMinEntry(void *_pHandle);

int32_t h_GetMaxEntry(void *_pHandle);

int32_t h_GetAvg(void *_pHandle);

#endif //HANDLE_H