/*
Author: Sam Nasser
Student #: 1139908
Date: Nov 1, 2023
*/

#include "Patient.h"
#include "PriorityQueue.h"
#include "Ailment.h"

#include <iomanip>
#include <vector>
#include <algorithm>
#include <istream>

using namespace std;
using namespace filesystem;

PriorityQueue<Patient> queue;

int main(int argc, char* argv[])
{
    char selection;

    do {

        printHeader();
      
        while (!(cin >> selection) || selection < '0' || selection > '5') {
            cout << "Invalid input. Please enter a number between 0 and 5 : ";
            cin.clear(); // clear input buffer to restore cin to a usable state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard the input

        }

        cout << endl;

        switch (selection) {
            case '1': {

                // Clear the input buffer
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                cout << "Adding a patient...\n" << endl;

                cout << "Please enter patient name: ";
                string name;
                getline(cin, name);
                Patient patient(name);

                string ailment;
                do
                {
                    int_type severity;
                    int_type timeCrit;
                    int_type contag;

                    cout << "\nEnter ailment (leave blank when done): ";
                    getline(cin, ailment);

                    if (ailment == "")
                        break;

              
                    // Input validation for severity
                    cout << "\nEnter severity (0-10): ";
                    while (!(cin >> severity) || severity < 0 || severity > 10) {
                        cout << "Invalid input. Please enter a number between 0 and 10 for severity: ";
                        cin.clear(); // clear input buffer to restore cin to a usable state
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard the input
                    }


                    // Input validation for time criticality
                    cout << "\nEnter time criticality (0-10): ";
                    while (!(cin >> timeCrit) || timeCrit < 0 || timeCrit > 10) {
                        cout << "Invalid input. Please enter a number between 0 and 10 for time criticality: ";
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }


                    // Input validation for contagiousness
                    cout << "\nEnter contagiousness (0-10): ";
                    while (!(cin >> contag) || contag < 0 || contag > 10) {
                        cout << "Invalid input. Please enter a number between 0 and 10 for contagiousness: ";
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }


                    Ailment ailments(ailment, severity, timeCrit, contag);
                    patient.add_ailment(ailments);

                    // Clear the input buffer
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                } while (true);

                queue.enqueue(patient);

                break;
            }
            case '2': {
        
                if (queue.emptyQueueExit(selection))
                {
                    break;
                }

                cout << queue.dequeue().get_name() << " moved to patient room!\n";
            
                if (queue.size() > 0)
                    cout << "Next in queue: " << queue.peek().get_name() << " with priority score " <<
                    queue.peek().get_score() << endl << "\n";
                else
                    cout << "End of queue" << endl << "\n";

                break;
            }
            case '3':{

                if (queue.emptyQueueExit(selection))
                {
                    break;
                }

                cout << "Patients In Queue:" << endl << endl;

                printQueue(queue);

                break;
            }
            case '4': {

                if (queue.emptyQueueExit(selection))
                {
                    break;
                }
                
                cout << "History:\n";

                auto i = queue.historyList().begin();

                while (i != nullptr)
                {
                    cout << i->data.get_name() << " - " << i->data.get_score() << " - ";

                    auto j = i->data.get_ailments().begin();
                    while (j != nullptr)
                    {
                        cout << j->data.get_name() << ", ";
                        j = j->next;

                    }
                    cout << "\n";
                    i = i->next;
                    
                }
              
                cout << endl << endl;

                break;

            }
            case '5': {

                // Clear the input buffer
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                cout << "Enter path to file: ";
                string filename;
                getline(cin, filename);
                readFile(filename, queue);

                break;
            }


        }

    } while (selection != '0');
 
  }
