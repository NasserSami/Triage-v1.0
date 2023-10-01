#pragma once


/*
 * This file controls the tests to be run. Just set
 * the tests you want to run to true 
 */

/*
 * 1. Test for the Ailment class
 */
#define TEST_AILMENT_CONSTRUCTOR false

/*
 * 2. Tests for the Patient class
 */
#define TEST_PATIENT_CONSTRUCTOR false
#define TEST_PATIENT_ADD_AILMENT false
#define TEST_PATIENT_CALCULATES_CORRECT_SCORES false

/*
 * 3. Tests for the PriorityQueue class
 */
#define TEST_PRIORITY_QUEUE_CONSTRUCTOR false
#define TEST_PRIORITY_QUEUE_SINGLE_PATIENT false
#define TEST_PRIORITY_QUEUE_MULTI_PATIENT_ORDERED false
#define TEST_PRIORITY_QUEUE_MULTI_PATIENT_UNORDERED false