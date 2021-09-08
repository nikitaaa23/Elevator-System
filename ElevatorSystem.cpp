#include <bits/stdc++.h>

using namespace std;

class Elevator{
    enum Direction{ Up, Down };
	Direction direction;

    vector<int>requests;
    int minFloor;
    int maxFloor;
    int currentFloor = 0;
    int passengers;
    int capacity = 0;

    public:
    Elevator(int minFloor, int maxFloor, int capacity){
        this->minFloor = minFloor;
        this->maxFloor = maxFloor;
        this->capacity= capacity;
    }

    ~Elevator(){}

    void startElevator();

    private:

    void setRequest();
    int checkRequest(int floor);
    int isValid(int floor);
    void setDirection(int floor);
};

int Elevator :: checkRequest(int floor){
    if(passengers!=0 && direction==Up && floor < currentFloor){
        return 1;
    }
    else if(passengers!=0 && direction==Down && floor > currentFloor){
        return 2;
    }
    else if(floor > maxFloor || floor < minFloor){
        return 3;
    }
    return 0;
}

int Elevator :: isValid(int floor){
    int num = checkRequest(floor);

    if(num==1){
        cout<<"Elevator is going Up.\n ";
    }
    else if(num==2){
        cout<<"Elevator is going Down\n";
    }
    else if(num==3){
        cout<<"This floor doesn't exist.\n";
    }
    return num;
}

void Elevator :: setDirection(int floor){
    if(floor > currentFloor){
        direction = Up;
    }
    else if(floor < currentFloor){
        direction = Down;
    }
}


void Elevator :: setRequest(){
    string allDestFloors;
    string DestFloor;
    int Dest;

    int numOfReq = capacity - passengers;
    cout<<" "<< numOfReq<<"Enter in the elevator now.\n";

    cout<<"Enter \"GO\" if no one enters from the floor \n Or exit the elevator if idle.\n";
    cout<<"Enter destination floor number: ";

    cin>>allDestFloors;
    stringstream sstream(allDestFloors);

    while(sstream >> DestFloor){
        if(DestFloor == "GO" || DestFloor=="Go" || DestFloor=="go" || DestFloor=="gO"){
            return;
        }
        else{
            Dest = stoi(DestFloor);
            if(passengers < capacity){
                int isV = isValid(Dest);
                if(!isV){
                    if(passengers==0){
                        setDirection(Dest);
                    }
                    requests.push_back(Dest);
                    passengers++;
                }
            }
            else if(passengers==capacity){
                cout<<"Elevator is full!!! Can't accept more requests"<<endl;
                return;
            }
        }
    }
}


void Elevator :: startElevator(){
    cout<<"FLOOR: "<<currentFloor<<endl;
    cout<<"Number of Occupants: "<<passengers<<endl;

    setRequest();
    sort(requests.begin(), requests.end());
    int nextFloor;

    while(!requests.empty()){
        if (direction == Up)
 		{
 			nextFloor = requests[0];
 		}
        else if(direction==Down){
            nextFloor = requests[requests.size()-1];
        }

        auto nextFloorReq = find(requests.begin(), requests.end(), nextFloor);
        while(nextFloorReq!=requests.end()){
            requests.erase(nextFloorReq);
            passengers--;
            nextFloorReq = find(requests.begin(), requests.end(), nextFloor);
        }
        currentFloor = nextFloor;

        string dir;
        if(direction==Up)
        {
            dir = "Up";
        }
        else{
            dir = "Down";
        }

        cout<<"\n-----------------------------------------------\n"<<endl;
        cout<<"FLOOR: "<<currentFloor<<endl;
        cout<<"Number of Occupants : "<<passengers<<endl;
        cout<<"Direction : "<<dir<<endl;
        cout<<"Total Capacity : "<<capacity <<endl;
        cout<<"Minimium Floor level: "<<minFloor<<endl;
        cout<<"Maximum Floor level: "<<maxFloor<<endl;
        cout<<"\n-----------------------------------------------\n"<<endl;
        
        if(currentFloor == maxFloor){
            direction = Down;
        }
        else{
            direction = Up;
        }
        setRequest();
        sort(requests.begin(), requests.end());
    }
}



int main(){

    string capacityS, minFloorNum, maxFloorNum;
    int minFloorN, maxFloorN;

    int capacity;

    cout<<"Enter minimium Floor level, maximum Floor level in the building \n";
    cin>>minFloorNum;
    cin>>maxFloorNum;

    minFloorN = stoi(minFloorNum);
    maxFloorN = stoi(maxFloorNum);

    cout<<"Enter capacity for the elevator: ";
    cin>>capacityS;
    cin.ignore();
    stringstream capStr(capacityS);
    capStr>>capacity;

    Elevator elevator(minFloorN, maxFloorN, capacity);
    elevator.startElevator();
    return 0;
}