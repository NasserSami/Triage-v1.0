/*
Author: Sam Nasser
Student #: 1139908
Date: Nov 1, 2023

*/


#include "PriorityQueue.h"


/**
 * @brief Enqueues a new patient into the priority queue.
 *
 * This method takes a patient object and inserts it into the priority queue according
 * to its priority score. The queue is ordered from highest to lowest score, meaning
 * patients with more urgent needs are positioned first. If the queue is empty, the
 * patient is placed at the front. Otherwise, the method finds the appropriate position
 * for the patient based on their score.
 *
 * @param patient The patient object to be enqueued.
 */
void PriorityQueue<Patient>::enqueue(const Patient& patient)
{
    Node* node = new Node();
    node->data = patient;
    node->previous = nullptr;
    node->next = nullptr;

    // If the queue is empty, simply place the new node at the beginning.
    if (begin_ == nullptr)
    {
        begin_ = node;
        end_ = node;
    }
    else
    {
        // Start at the beginning of the list and find the correct spot
        Node* current = begin_;
        Node* previous = nullptr;

        // Iterate to find the insertion point based on the patient's score
        while (current != nullptr && current->data.get_score() >= patient.get_score())
        {
            previous = current;
            current = current->next;
        }

        // If we're still at the beginning, insert the node at the start
        if (previous == nullptr)
        {
            node->next = begin_;
            begin_->previous = node;
            begin_ = node;
        }
        else
        {
            // Insert the node in the middle or at the end
            node->next = previous->next;
            node->previous = previous;
            previous->next = node;

            // If the node is the new end, update the end pointer
            if (node->next == nullptr)
            {
                end_ = node;
            }
            else
            {
                node->next->previous = node;
            }
        }
    }
}


/**
 * @brief Prints a decorative program header and the main menu options.
 *
 * This function displays a program header including the author's name and the associated
 * institution, followed by a series of asterisks to create a border around the header. It then
 * prints out the main menu options for the user to select from. The menu includes options
 * to add a patient, process the next patient in the queue, display the current queue,
 * view the history of processed patients, load a queue from a file, and exit the program.
 */
void printHeader()
{

    std::string name = "Sam Nasser";
    std::string college = "Fanshawe College Medical Center F2023";
    std::string border(60, '*');  // Creates a string of 60 asterisks

    // Calculate padding for the name to be centered
    size_t padding = (border.length() - name.length() - 2) / 2;
    std::string paddedName(padding, ' ');
    paddedName += name;
    paddedName += std::string(padding, ' ');

    // If the length is odd, add one more space to make it even
    if (paddedName.length() % 2 != border.length() % 2) {
        paddedName += " ";
    }

    // Print the header
    std::cout << border << std::endl;
    std::cout << "* " << college << " *" << std::endl;
    std::cout << "*" << paddedName << "*" << std::endl;
    std::cout << border << std::endl << "\n";

    std::cout << "Please Make A Selection:\n";
    std::cout << "\n";
    std::cout << "    1 - Add Patient\n";
    std::cout << "    2 - Process Next Patient In Queue\n";
    std::cout << "    3 - Display Queue\n";
    std::cout << "    4 - View Processed Patients History\n";
    std::cout << "    5 - Load Queue\n";
    //std::cout << "    6 - Save Queue\n";
    std::cout << "    0 - Exit\n";
    std::cout << std::endl;
}




/**
 * @brief Prints the details of each patient in a priority queue.
 *
 * This function iterates through a PriorityQueue of Patient objects and prints the details
 * of each patient in the order they appear in the queue. For each patient, it prints the
 * position in the queue, the patient's name, the total score, and a list of ailment names.
 * The total score is assumed to be calculated and stored within the Patient object.
 *
 * @param list A reference to the priority queue holding Patient objects to be printed.
 *
 * @note This function assumes that the priority queue is implemented with linked nodes,
 *       where each node has a `data` member (the Patient object) and a `next` pointer
 *       to the subsequent node. The `get_ailments` method of a Patient object is expected
 *       to return a linked list of Ailments, which is similarly traversed.
 */
void printQueue(PriorityQueue<Patient>& list)
{
    size_t counter = 0;

    auto i = list.begin();
    while (i != nullptr)
    {
        ++counter;
        std::cout << counter << " : " << i->data.get_name() << " - " << i->data.get_score()
            << " - ";

        auto j = i->data.get_ailments().begin();
        while (j != nullptr)
        {
            std::cout << j->data.get_name() << ", ";
            j = j->next;
        }

        std::cout << "\n";
        i = i->next;

    }

    std::cout << std::endl << std::endl;


}



/**
 * @brief Reads patient data from a CSV file and enqueues them into a priority queue.
 *
 * This function opens a CSV file specified by the filename and reads each line to
 * construct Patient objects with their associated Ailments. Each Patient object is then
 * enqueued in the provided priority queue. The CSV file is expected to have a specific
 * format, with the patient name as the first token, the number of ailments as the
 * second token, followed by groups of four tokens representing each ailment with its
 * details.
 *
 * @param filename The path to the CSV file containing patient data.
 * @param queue A reference to a PriorityQueue of Patient objects to which the read patients will be enqueued.
 *
 * @note The function will output an error message to the standard error if the file
 *       cannot be opened, or if there are not enough data tokens for a patient's ailments.
 *       In case of malformed or incomplete data, the patient will not be enqueued in the priority queue.
 */
void readFile(const std::string& filename,PriorityQueue<Patient>& queue)
{
    std::ifstream infile(filename);
    std::string line;


    if (!infile)
    {
        std::cout << "\nError: text filename " << "\"" + filename + "\"" <<
            " --> No such file or directory\n";
    }
    else if (infile.is_open())
    {
        std::string line;
        //std::getline(infile, line);

        // Read lines until EOF
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> tokens;
            // Read values separated by commas
            while (std::getline(iss, token, ',')) {
                tokens.push_back(token);

            }

            //removes whitesapce from vector 
            tokens.erase(std::remove_if(tokens.begin(), tokens.end(),
                [](const std::string& s) { return s.empty(); }),
                tokens.end());
            Patient patient(tokens[0]);
            int numOfAilments = std::stoi(tokens[1]);

            int dataIndex = 2; // Start index for ailment data
            for (int ailment = 0; ailment < numOfAilments; ++ailment) {
                // Create an Ailment object from each set of 4 tokens
                if (dataIndex + 3 < tokens.size()) {
                    Ailment ailments(tokens[dataIndex], std::stoi(tokens[dataIndex + 1]),
                        std::stoi(tokens[dataIndex + 2]), std::stoi(tokens[dataIndex + 3]));
                    patient.add_ailment(ailments);
                    queue.enqueue(patient);

                    dataIndex += 4; // Move to the next set of ailment data
                }
                else
                {
                    std::cerr << "Not enough data for ailment " << ailment + 1 << " for patient " << tokens[0] << std::endl;
                    // Handle the error appropriately
                    break; // Exit the loop to avoid processing incomplete data
                }
            }

        }

        std::cout << "File read sucessfully! Patients have been loaded in.....\n";
        infile.close();
    }


}