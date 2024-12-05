/**
 * @file Node.h
 * @author Phillip Eustace
 * @brief A node file. The game map is made up of these.
 * @version 0.1
 * @date 2024-12-3
 * 
 */
#pragma once

#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <iostream>

using namespace std;

class Node{
    private:
    //The hidden ID of the item (format EVENT[number created])
    string typeID;
    int numInList;
    string nodeID = "EVENT" + to_string(numInList);
    
    

    
    public:
    bool isKnown = false;
    //The readable name
    string eventName;
    string eventBody;

    string factor;
    float level;
    Node() : numInList(0), eventName("not set"), eventBody(""), factor("DummyVal"), level(0), nodeID("EVENT0"), isKnown(false) {}

    // Constructor with parameters to initialize the node properly
    Node(int num, string eventName, string eventText, string factor, float level) 
        : numInList(num), eventName(eventName), eventBody(eventText), factor(factor), level(level), nodeID("EVENT" + to_string(num)), isKnown(false) {}
};