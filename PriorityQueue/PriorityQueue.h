/*
Author: Sam Nasser
Student #: 1139908
Date: Nov 1, 2023

*/

#pragma once
#include "Patient.h"



/**
 * @brief A priority queue template class specialized to handle patients.
 *
 * This template class implements a priority queue specifically designed for patient objects.
 * Patients are enqueued based on a priority score, and dequeued from the highest to the
 * lowest score. The queue also maintains a history of all processed (dequeued) patients.
 * It allows peeking at the highest priority patient without removing it, checking if the
 * queue is empty, and counting the number of patients in the queue.
 */
template <typename T>
class PriorityQueue
{
    LinkedList<Patient> historyPatients_;

public:

	struct Node
	{
        Node* previous;
        Node* next;

		T data;
	};

protected:
	Node* begin_;
	Node* end_;

public:
	PriorityQueue() : begin_(nullptr), end_(nullptr){}

	Node* begin() { return begin_; }
    Node* end() { return end_; }
    LinkedList<Patient> historyList() { return historyPatients_; }

    void enqueue(const Patient& patient);


    T dequeue()
    {
        if (begin_ == nullptr)
        {
            throw "Queue is empty";
        }

        // The highest priority patient is at the beginning of the queue
        Node* node_to_remove = begin_;

        // Save the data to return
        T highest_priority_data = node_to_remove->data;

        
        //save to history
       historyPatients_.push_front(highest_priority_data);

        // Update the beginning to point to the next element
        begin_ = begin_->next;

        // If the queue is not empty after removal, update the previous pointer
        if (begin_ != nullptr)
        {
            begin_->previous = nullptr;
        }
        else
        {
            // If the queue is empty after removal, also update the end pointer
            end_ = nullptr;
        }

        // Free the memory allocated for the highest priority node
        delete node_to_remove;

        // Return the data from the removed node
        return highest_priority_data;
    }

    T peek()
    {
        if (!this->empty())
            return begin_->data;
        else
            throw "Queue is empty";
    }


    constexpr bool empty() const
	{
		return begin_ == nullptr;
	}

    /**
    * @brief Checks if the priority queue is empty before proceeding with a selection action.
    *
    * This function is designed to check the state of the queue before performing an action
    * that requires the queue to have elements. If the queue is empty and the action is not
    * to view the processed patients history (selection '4'), it informs the user that they
    * need to add patients first. If the selection is '4' and there are no processed patients
    * in the history, it informs the user accordingly. In either case of the queue being empty,
    * the function returns true to indicate that the intended action cannot proceed. If the
    * queue is not empty, the function returns false, allowing the action to continue.
    *
    * @param selection The user's menu selection input, which determines the action to be taken.
    * @return bool Returns true if the queue is empty and the action cannot proceed, false otherwise.
    */
    bool emptyQueueExit(char selection)
    {
        if (this->empty() && selection != '4' )
        {
            std::cout << "Queue is empty, please add patient first!\n" << std::endl;
            return true;
        
        }
        else if (selection == '4' && historyPatients_.empty())
        {
            std::cout << "No patients processed!\n" << std::endl;
            return true;
        }

        return false;

    }


	size_t size() const
	{
		size_t counter = 0;

		Node* node = begin_;
		while (node != nullptr)
		{
			++counter;
			node = node->next;
		}

		return counter;
	}


	
};


void printHeader();

void printQueue(PriorityQueue<Patient>& list);

void readFile(const std::string& filename, PriorityQueue<Patient>& queue);




