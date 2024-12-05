/**
 * @file Map.cpp
 * @author Phillip Eustace
 * @brief A map file that holds the map and movement functions of the entire game
 * @version 0.1
 * @date 2024-12-3
 * 
 */

#include "Map.h"
#include "Node.h"

Map::Map() {
    srand((time(0)));

    BuildRandomMap(_map);
}

void Map::BuildRandomMap(Node map[5][4]) {
    //Populate the map from the list of possible nodes
    for (int row = 0; row < 5; row++) {
        //for each column in this row
        for (int col = 0; col < 4; col++) {
            if (map[row][col].eventName == "not set") {
                //Try to pull a node. Will pull a dummy node if not enough nodes are present
                try {
                    map[row][col] = Map::PullRandomNode();
                }
                catch (...) {
                    //We don't care what the ID is because any dummy object is effectively useless
                    //and will not be included in the running game unless the entire thing is unplayable
                    map[row][col] = Map::ProvideDummy((row + col));
                    cout << "Error. Dummy supplied." << endl;
                }
            }
        }
    }
}

Node Map::PullRandomNode() {
    //Pull a random node from all possible nodes
    
    //cout << "Node List Size: " + to_string(NodesList.size()) << endl;
    int rand_pos = rand() % NodesList.size();
    
    if (rand_pos >= NodesList.size()) {
        cout << "Seeking Node: " + to_string(rand_pos) << endl;
        cout << "Error. Didn't find that node." << endl;
        throw std::runtime_error("rand_pos is out of bounds");
    }
    Node toReturn = NodesList[rand_pos];
    //cout << "Successful Node Acquisition: " + toReturn.eventName << " w/ Index: " << to_string(rand_pos) << endl;
    NodesList.erase(NodesList.begin() + rand_pos);

    return toReturn;
}


Node Map::ProvideDummy(int id) {
    Node DummyNode = Node(id, "Dummy", "Dummy Node.", "DummyVal", 0);
    return DummyNode;
}

string Map::TriggerRandomEvent() {
    int rand_pos = rand() % MapStrings.size();
    return MapStrings[rand_pos];
}
void Map::PrintMap() {
    for (int row = 0; row < 5; row++) {
        //for each column in this row
        for (int col = 0; col < 4; col++) {
            if (_map[row][col].isKnown) {
                cout << _map[row][col].eventName << " at |" << to_string(row) << " " << to_string(col)  << "|"<< endl;     
            }
        }
    }
}
void Map::NewLocation(int row, int col) {
    currentLeft = row;
    currentTop = col;
}
//Checks if all map spots are open
bool Map::NoStoneUnturned() {
    for (int row = 0; row < 5; row++) {
        //for each column in this row
        for (int col = 0; col < 4; col++) {
            if (_map[row][col].isKnown == false) {
                return false;
            }
        }
    }
    return true;
}