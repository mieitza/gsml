// *******************************************************************
//
// (c) Copyright Cisco 2000
// All Rights Reserved
//
// *******************************************************************

// *******************************************************************
//
// File        : MultislotConfigurationGenerator.cpp
// Author(s)   : Daryl Kaiser
// Create Date : 1/29/2001
// Description : 
//
// *******************************************************************

#include "ScheduleAllocationInfo.h"

/*----------------------------------------------------------------------------**
**    Multislot Pattern Tables
**----------------------------------------------------------------------------*/
const int ScheduleAllocationInfo::nbrTsPatterns[PAT_ORDER] = {1,7,21,35,35,21,7,1};

const char ScheduleAllocationInfo::tsPattern[PAT_ORDER][PAT_INDEX][PAT_SLOTS] = {

// -------------------------- Pattern Order 1 -----------------------------------
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

// -------------------------- Pattern Order 2 -----------------------------------
0,1,0,0,0,0,0,0, 0,2,0,0,0,0,0,0, 0,3,0,0,0,0,0,0, 0,4,0,0,0,0,0,0, 0,5,0,0,0,0,0,0,
0,6,0,0,0,0,0,0, 0,7,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

// -------------------------- Pattern Order 3 -----------------------------------
0,1,2,0,0,0,0,0, 0,1,3,0,0,0,0,0, 0,1,4,0,0,0,0,0, 0,1,5,0,0,0,0,0, 0,1,6,0,0,0,0,0,
0,1,7,0,0,0,0,0, 0,2,3,0,0,0,0,0, 0,2,4,0,0,0,0,0, 0,2,5,0,0,0,0,0, 0,2,6,0,0,0,0,0,
0,2,7,0,0,0,0,0, 0,3,4,0,0,0,0,0, 0,3,5,0,0,0,0,0, 0,3,6,0,0,0,0,0, 0,3,7,0,0,0,0,0,
0,4,5,0,0,0,0,0, 0,4,6,0,0,0,0,0, 0,4,7,0,0,0,0,0, 0,5,6,0,0,0,0,0, 0,5,7,0,0,0,0,0,
0,6,7,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

// -------------------------- Pattern Order 4 -----------------------------------
0,1,2,3,0,0,0,0, 0,1,2,4,0,0,0,0, 0,1,2,5,0,0,0,0, 0,1,2,6,0,0,0,0, 0,1,2,7,0,0,0,0,
0,1,3,4,0,0,0,0, 0,1,3,5,0,0,0,0, 0,1,3,6,0,0,0,0, 0,1,3,7,0,0,0,0, 0,1,4,5,0,0,0,0,
0,1,4,6,0,0,0,0, 0,1,4,7,0,0,0,0, 0,1,5,6,0,0,0,0, 0,1,5,7,0,0,0,0, 0,1,6,7,0,0,0,0,
0,2,3,4,0,0,0,0, 0,2,3,5,0,0,0,0, 0,2,3,6,0,0,0,0, 0,2,3,7,0,0,0,0, 0,2,4,5,0,0,0,0,
0,2,4,6,0,0,0,0, 0,2,4,7,0,0,0,0, 0,2,5,6,0,0,0,0, 0,2,5,7,0,0,0,0, 0,2,6,7,0,0,0,0,
0,3,4,5,0,0,0,0, 0,3,4,6,0,0,0,0, 0,3,4,7,0,0,0,0, 0,3,5,6,0,0,0,0, 0,3,5,7,0,0,0,0,
0,3,6,7,0,0,0,0, 0,4,5,6,0,0,0,0, 0,4,5,7,0,0,0,0, 0,4,6,7,0,0,0,0, 0,5,6,7,0,0,0,0,

// -------------------------- Pattern Order 5 -----------------------------------
0,1,2,3,4,0,0,0, 0,1,2,3,5,0,0,0, 0,1,2,3,6,0,0,0, 0,1,2,3,7,0,0,0, 0,1,2,4,5,0,0,0,
0,1,2,4,6,0,0,0, 0,1,2,4,7,0,0,0, 0,1,2,5,6,0,0,0, 0,1,2,5,7,0,0,0, 0,2,3,6,7,0,0,0,
0,1,3,4,5,0,0,0, 0,1,3,4,6,0,0,0, 0,1,3,4,7,0,0,0, 0,1,3,5,6,0,0,0, 0,1,3,5,7,0,0,0,
0,1,3,6,7,0,0,0, 0,1,4,5,6,0,0,0, 0,1,4,5,7,0,0,0, 0,1,4,6,7,0,0,0, 0,1,5,6,7,0,0,0,
0,2,3,4,5,0,0,0, 0,2,3,4,6,0,0,0, 0,2,3,4,7,0,0,0, 0,2,3,5,6,0,0,0, 0,2,3,5,7,0,0,0,
0,2,3,6,7,0,0,0, 0,2,4,5,6,0,0,0, 0,2,4,5,7,0,0,0, 0,2,4,6,7,0,0,0, 0,2,5,6,7,0,0,0,
0,3,4,5,6,0,0,0, 0,3,4,5,7,0,0,0, 0,3,4,6,7,0,0,0, 0,3,5,6,7,0,0,0, 0,4,5,6,7,0,0,0,

// -------------------------- Pattern Order 6 -----------------------------------
0,1,2,3,4,5,0,0, 0,1,2,3,4,6,0,0, 0,1,2,3,4,7,0,0, 0,1,2,3,5,6,0,0, 0,1,2,3,5,7,0,0,
0,1,2,3,6,7,0,0, 0,1,2,4,5,6,0,0, 0,1,2,4,5,7,0,0, 0,1,2,4,6,7,0,0, 0,1,2,5,6,7,0,0,
0,1,3,4,5,6,0,0, 0,1,3,4,5,7,0,0, 0,1,3,4,6,7,0,0, 0,1,3,5,6,7,0,0, 0,1,4,5,6,7,0,0,
0,2,3,4,5,6,0,0, 0,2,3,4,5,7,0,0, 0,2,3,4,6,7,0,0, 0,2,3,5,6,7,0,0, 0,2,4,5,6,7,0,0,
0,3,4,5,6,7,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

// -------------------------- Pattern Order 7 -----------------------------------
0,1,2,3,4,5,6,0, 0,1,2,3,4,5,7,0, 0,1,2,3,4,6,7,0, 0,1,2,3,5,6,7,0, 0,1,2,4,5,6,7,0,
0,1,3,4,5,6,7,0, 0,2,3,4,5,6,7,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

// -------------------------- Pattern Order 8 -----------------------------------
0,1,2,3,4,5,6,7, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0};

/*----------------------------------------------------------------------------**
**    Multislot Configuration Tables
**----------------------------------------------------------------------------*/
const int ScheduleAllocationInfo::nbrMultiConfig[MULTI_CLASS] =
{1,3,4,7,10,11,12,14,23,24,27,28};

const char ScheduleAllocationInfo::multiMaxDlSlots[MULTI_CLASS] =
{1,2,2,3,2,3,3,4,3,4,4,4};

const char ScheduleAllocationInfo::multiMaxUlSlots[MULTI_CLASS] =
{1,1,2,1,2,2,3,1,2,2,3,4};

#define M char(-1)
const char ScheduleAllocationInfo::ms[MULTI_SETS][MULTI_PARMS] = {
1,7,1,1, M,1,1,  0,7,1,1, 0,1,1,  0,6,1,1, 1,1,1,  0,5,1,1, 2,1,1,
0,6,2,1, 0,1,1,  0,6,2,1, 1,1,1,  0,5,2,1, 2,1,1,  0,5,2,2, 1,1,1,
0,5,2,2, 2,1,1,  0,5,3,1, 1,1,1,  0,5,3,1, 2,1,1,  0,4,3,2, 2,1,1,  
0,4,3,7, 2,1,1,  0,4,4,1, 2,1,1,  1,7,1,1, M,2,1,  0,6,1,1, 0,2,1,  
0,5,1,1, 1,2,1,  1,6,1,1, M,2,2,  0,5,1,1, 0,2,2,  0,6,2,1, 0,2,1,
0,5,2,1, 1,2,1,  0,5,2,1, 0,2,2,  0,5,2,2, 1,2,1,  0,5,3,1, 1,2,1,
1,6,1,1, M,3,1,  0,5,1,1, 0,3,1,  0,5,2,1, 0,3,1,  1,5,1,1, M,4,1 };

const char* ScheduleAllocationInfo::multiConfig[MULTI_CLASS][MULTI_INDEX] = {

// ---------------------- Multislot Class 1 ------------------------------
&ms[1][0],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

// ---------------------- Multislot Class 2 ------------------------------
&ms[1][0],&ms[2][0],&ms[5][0],
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

// ---------------------- Multislot Class 3 ------------------------------
&ms[1][0],&ms[2][0],&ms[5][0],&ms[15][0], 
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

// ---------------------- Multislot Class 4 ------------------------------
&ms[0][0],&ms[1][0],&ms[2][0],&ms[4][0],&ms[5][0],&ms[7][0],&ms[9][0], 
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

// ---------------------- Multislot Class 5 ------------------------------
&ms[0][0], &ms[1][0],&ms[2][0],&ms[4][0],&ms[5][0],&ms[7][0],&ms[14][0], 
&ms[15][0],&ms[17][0],&ms[19][0],0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

// ---------------------- Multislot Class 6 ------------------------------
&ms[0][0], &ms[1][0], &ms[2][0], &ms[4][0],&ms[5][0],&ms[7][0],&ms[9][0],
&ms[14][0],&ms[15][0],&ms[17][0],&ms[19][0],
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

// ---------------------- Multislot Class 7 ------------------------------
&ms[0][0], &ms[1][0], &ms[2][0], &ms[4][0], &ms[5][0],&ms[7][0],&ms[9][0],
&ms[14][0],&ms[15][0],&ms[17][0],&ms[19][0],&ms[24][0],
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

// ---------------------- Multislot Class 8 ------------------------------
&ms[0][0],&ms[1][0],&ms[2][0],&ms[3][0], &ms[4][0], &ms[5][0], &ms[6][0],
&ms[7][0],&ms[8][0],&ms[9][0],&ms[10][0],&ms[11][0],&ms[12][0],
&ms[13][0],0,0,0,0,0,0,0,0,0,0,0,0,0,0,

// ---------------------- Multislot Class 9 ------------------------------
&ms[0][0], &ms[1][0], &ms[2][0], &ms[3][0], &ms[4][0], &ms[5][0], &ms[6][0],
&ms[7][0], &ms[8][0], &ms[9][0], &ms[10][0],&ms[11][0],&ms[12][0],
&ms[14][0],&ms[15][0],&ms[16][0],&ms[17][0],&ms[18][0],&ms[19][0],
&ms[20][0],&ms[21][0],&ms[22][0],&ms[23][0],0,0,0,0,0,

// ---------------------- Multislot Class 10 ------------------------------
&ms[0][0], &ms[1][0], &ms[2][0], &ms[3][0], &ms[4][0], &ms[5][0], &ms[6][0],
&ms[7][0], &ms[8][0], &ms[9][0], &ms[10][0],&ms[11][0],&ms[12][0],
&ms[13][0],&ms[14][0],&ms[15][0],&ms[16][0],&ms[17][0],&ms[18][0],&ms[19][0],
&ms[20][0],&ms[21][0],&ms[22][0],&ms[23][0],0,0,0,0,

// ---------------------- Multislot Class 11 ------------------------------
&ms[0][0], &ms[1][0], &ms[2][0], &ms[3][0], &ms[4][0], &ms[5][0], &ms[6][0],
&ms[7][0], &ms[8][0], &ms[9][0], &ms[10][0],&ms[11][0],&ms[12][0],
&ms[13][0],&ms[14][0],&ms[15][0],&ms[16][0],&ms[17][0],&ms[18][0],&ms[19][0],
&ms[20][0],&ms[21][0],&ms[22][0],&ms[23][0],
&ms[24][0],&ms[25][0],&ms[26][0],0,

// ---------------------- Multislot Class 12 ------------------------------
&ms[0][0], &ms[1][0], &ms[2][0], &ms[3][0], &ms[4][0], &ms[5][0], &ms[6][0],
&ms[7][0], &ms[8][0], &ms[9][0], &ms[10][0],&ms[11][0],&ms[12][0],
&ms[13][0],&ms[14][0],&ms[15][0],&ms[16][0],&ms[17][0],&ms[18][0],&ms[19][0],
&ms[20][0],&ms[21][0],&ms[22][0],&ms[23][0],
&ms[24][0],&ms[25][0],&ms[26][0],&ms[27][0] };