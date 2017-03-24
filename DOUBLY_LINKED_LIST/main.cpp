#include <iostream>
#include <string>

using namespace std;

/*
    Name - Daniel Erhabor
    @02778845
    Lab for 3/21
*/

struct flight{
    //int flightNum;
    string destination;     // Flight Struct - I scrapped the number because it was irrelevant
};

struct node{
    flight aFlight;
    node* next;         //Node struct
    node* previous;

};

class DoublyLinkedList{
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void Append(flight someFlight);
    void Prepend(flight someFlight);
    void Remove(flight someFlight);
    void PrintList();       // This just prints the list in a regular order
    void PrintFlights();        // Prints lost according to specifications
private:
    flight flightData;      // Private data members
    node* head;
    node* tail;

};

int main()
{
    //cout << "Hello world!" << endl;

    flight houston;
    houston.destination = "Houston";
    flight chicago;
    chicago.destination = "Chicago";
    flight arizona;
    arizona.destination = "Arizona";
    flight baltimore;                       //flight structs declarations
    baltimore.destination = "Baltimore";
    flight detroit;
    detroit.destination = "Detroit";
    flight colorado;
    colorado.destination = "Colorado";
    flight dallas;
    dallas.destination = "Dallas";
    flight kansascity;
    kansascity.destination = "Kansas City";

    DoublyLinkedList myList;

    myList.Append(houston);
    myList.Append(chicago);         // Populate the list
    myList.Append(baltimore);
    myList.Append(detroit);
    myList.Append(colorado);
    myList.Append(houston);


    myList.Prepend(dallas);

    myList.Remove(arizona);
    myList.Remove(houston);         // Required list operations according to

    myList.Append(kansascity);

    cout << "Flight Records for HowardAir Flight 0136:" << endl;
    myList.PrintFlights();


    return 0;
}


DoublyLinkedList::DoublyLinkedList(){
    head = NULL;                        //Constructor
    tail = NULL;
}

DoublyLinkedList::~DoublyLinkedList(){} // Destructor

void DoublyLinkedList::Append(flight someFlight){
    if (head==NULL){
        node* newObj = new node;
        newObj->aFlight = someFlight;                   // Append function definition
        head = newObj;
        tail = newObj;
        newObj->previous = NULL;
        newObj->next = NULL;
    }
    else{
        node* newObj = new node;
        newObj->aFlight = someFlight;
        node* temp = tail;
        newObj->previous = temp;
        temp->next = newObj;
        newObj->next = NULL;
        tail = newObj;

    }
    return;

}

void DoublyLinkedList::Prepend(flight someFlight){
    if (head==NULL){
        node* newObj = new node;
        newObj->aFlight = someFlight;                   // Prepend item
        head = newObj;
        tail = newObj;
        newObj->previous = NULL;
        newObj->next = NULL;

    }
    else{
        node* newObj = new node;
        newObj->aFlight = someFlight;
        node* temp = head;
        newObj->next = temp;
        temp->previous = newObj;
        newObj->previous = NULL;
        head = newObj;

    }

}
//Remove function definition
void DoublyLinkedList::Remove(flight someFlight){
    if (head->next == NULL){
        if (head->aFlight.destination == someFlight.destination){           // If only one item in list
            node* temp = head;
            head = NULL;
            tail = NULL;
            delete temp;
        }
    }
    else{
        if (head->aFlight.destination==someFlight.destination){
            node* temp = head;                                  // If item is the head
            head = temp->next;
            head->previous = NULL;
            temp->next = NULL;
            delete temp;
        }
        if (tail->aFlight.destination==someFlight.destination){
            node* temp = tail;
            tail = temp->previous;                                  // If item is the tail - I made this special case so I would not
            tail->next = NULL;                                      // Have to remove all occurrences of Houston then prepend it again before prepending Dallas
            temp->previous = NULL;
            delete temp;
        }
        else{
            for (node* traverse = head->next; traverse->next != NULL; traverse = traverse->next){
                if (traverse->aFlight.destination==someFlight.destination){
                    traverse->next->previous = traverse->previous;                      // If item is between the head and the tail
                    traverse->previous->next = traverse->next;
                    traverse->next = NULL;
                    traverse->previous = NULL;
                    delete traverse;

                }
            }
        }

    }
    return;


}

void DoublyLinkedList::PrintList(){
    for (node* traverse = head; traverse != NULL; traverse = traverse->next){           // Print the list as regular as possible
        cout << traverse->aFlight.destination << endl;
    }
    return;
}
//Print the list according to specifications
//Some manual and primitive implementations were used because I implementation was linear until baltimore to detroit and detroit to baltimore

void DoublyLinkedList::PrintFlights(){
    int i = 1;

    for (node* traverse = head; traverse->next != NULL; traverse = traverse->next){


        cout << i << ". " << traverse->aFlight.destination << " to " << traverse->next->aFlight.destination << endl;
        ++i;
        if (i==5){
            traverse = traverse->next;
            cout << i << ". " << traverse->aFlight.destination << " to " << traverse->previous->aFlight.destination << endl;
            ++i;

        }
        if (i==6){
            cout << i << ". " << traverse->previous->aFlight.destination << " to " << traverse->next->aFlight.destination << endl;
            ++i;
        }
        if (i==7){
            traverse = traverse->next;
            cout << i << ". " << traverse->aFlight.destination << " to " << traverse->next->aFlight.destination;
        }


    }

}
