#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include "Map.h"
#include <thread>

using namespace std;

int main()
{
    //starting values
    int food = 50;
    int water = 50;
    int air = 50;

    bool gameOver = false;
    Map map = Map();

    cout << map.mapSetting << endl;

    while (!gameOver) {
        map.currentMapDay += 1;
        cout << "Day " + to_string(map.currentMapDay) << endl;
        cout << "Resources: \nFood: " << to_string(food) << " (-10/day)\nWater: " << to_string(water) << " (-10/day)\nOxygen: " << to_string(air) << " (-10/day)" << endl;
        //Interrupt to trigger an event (i.e. flavor text) on every day after the first.
        if (map.currentMapDay != 1) {
            cout << map.TriggerRandomEvent() << endl << "=======" << endl;
            std::this_thread::sleep_for(2s);
        }
        bool validResponse = false;
        string response;
        cout << "What will you do today?: " << endl;
        cout << "1. Inspect new area\n2. Take from environment\n3. VIEW MAP\n4. Pass time" << endl;
        cin >> response;
        while (!validResponse) {
            if (response == "1") {
                cout << "Inspecting new areas will grant you more resources and potentially help you escape. \nHowever, there is a chance things go wrong.\nWould you like to continue? (y/n) : " << endl;
                cin >> response;
                if (response == "y") {
                    //Select a direction to go.
                    string directionResponse;
                    int setDirection = 0;
                    bool validDirection = false;
                    string direction = "default";
                    while (setDirection == 0) {
                        cout << "Which direction? \n(1) Left\n(2) Right\n(3) Forward.\n(4) Backward:\n";
                        cin >> directionResponse;
                        if (stoi(directionResponse) == 1 || stoi(directionResponse) == 2 || stoi(directionResponse) == 3 || stoi(directionResponse) == 4) {
                            if (stoi(directionResponse) == 1 || stoi(directionResponse) == 2) {
                                cout << "Current Horizontal Coordinate: " << map.currentLeft << endl;
                                direction = "leftRight";
                                setDirection = stoi(directionResponse);
                                if (setDirection == 2) {
                                    //Setting the direction to the intended on the map
                                    setDirection = 1;
                                    //Doing a check to see if the player can move that direction. If they can't, let them know and back out.
                                    if (map.currentLeft < 5) {
                                        validDirection = true;
                                    }
                                }
                                else if (setDirection == 1) {
                                    setDirection = -1;
                                    //row count used
                                    if (map.currentLeft > 0) {
                                        validDirection = true;
                                    }
                                }
                            }
                            else {
                                cout << "Current Vertical Coordinate: " << map.currentLeft << endl;
                                direction = "upDown";
                                setDirection = stoi(directionResponse);
                                if (setDirection == 3) {
                                    setDirection = 1;
                                    if (map.currentTop < 4) {
                                        validDirection = true;
                                    }
                                }
                                else if (setDirection == 4) {
                                    setDirection = -1;
                                    if (map.currentTop > 0) {
                                        validDirection = true;
                                    }
                                }
                            }

                            
                        }
                        else {
                            cout << "Invalid choice.";
                        }
                    }
                    //run node discovery with a chance of failure
                    int pass = rand() % 5;
                    if (pass == 0 && validDirection) {
                        //0 is the failure  
                        cout << "The door refuses to budge. You spent all day on it, too... time to rest." << endl; 

                    }
                    else if (pass >= 1 && validDirection) {
                        //over 1 is a pass
                        cout << "You succeeded!" << endl;
                        //reveal the new point on the map and set your position
                        if (direction == "upDown") {
                            map.currentTop += setDirection;
                        }
                        else if (direction == "leftRight") {
                            map.currentLeft += setDirection;
                        }
                        map._map[map.currentLeft][map.currentTop].isKnown = true;

                        Node location = map._map[map.currentLeft][map.currentTop];
                        string locationName = location.eventName;
                        string locationText = location.eventBody;
                        cout << "New Location:" << endl;
                        cout << "==============================" << endl;
                        cout << locationName << endl;
                        cout << locationText << endl;
                        cout << "==============================" << endl;

                        //Apply location values.
                        if (location.factor == "air") {
                            air += location.level;
                        }
                        else if (location.factor == "water") {
                            water += location.level;
                        }
                        else if (location.factor == "food") {
                            food += location.level;
                        }
                    }
                    else {
                        cout << "Can't go that way. You sure waste time trying, though." << endl;
                    }
                    //valid choice
                    validResponse = true;
                }
                else if (response == "n") {
                    //back out
                    cout << "You decide against this. What else can you do?" << endl;
                }
                else {
                    cout << "Error. Please respond with 'y' or 'n'." << endl;
                }
            }
            else if (response == "2") {
                cout << "You attempt to bolster your resources with items you find on the submarine.\nToday's haul: " << endl;
                int pass;
                pass = rand() % 2;
                if (pass == 0) {
                    pass = rand() % 3;
                    if (pass == 0) {
                        cout << "You found food!" << endl;
                        food += 10;
                    }
                    else if (pass == 1) {
                        cout << "You found water!" << endl;
                        water += 10;
                    }
                    else if (pass == 2) {
                        cout << "You found some spare oxygen canisters!" << endl;
                        air += 10;
                    }
                }
                else if (pass == 1) {
                    cout << "You didn't manage to find anything." << endl;
                }
                validResponse = true;
            }
            else if (response == "3") {
                cout << "You take the day to scan the vessel.\nThe following is a list of known coordinates on the submarine.\nEnhance your knowledge by uncovering more: " << endl;
                map.PrintMap();
                cout << "End of Map." << endl;
                validResponse = true;
            }
            else if (response == "4") {
                cout << "You kill time, for whatever reason. The day passes." << endl;
                validResponse = true;
            }
            else {
                cout << "Invalid response. Please select using the number of the choice you desire: " << endl;
                cin >> response;
            }
        }
        //Before the next day, check and update values. End game if values are not valid for continuing.
        air -= 5;
        food -= 5;
        water -= 5;

        if (air <= 0 || food <= 0 || water <= 0) {
            cout << "You ran out of vital resources. Your time under the sea has come to a close.\n But maybe this was for the best? There are far, far worse things than death in these depths." << endl;
            gameOver = true;
        }
        else if (map.NoStoneUnturned()) {
            cout << "You secured the entire submarine and found a final, vast stash of emergency supplies.\n Now able to wait it out in relative comfort, eventually rescue comes.\n For the rest of your life, however, you feel paranoid. \nAs if... something is always hiding within the hidden corners of your mind.";
            gameOver = true;
        }
        else if (map.currentMapDay >= 40) {
            cout << "You've come to live a comfortable life in the depths for quite a while.\nThough help never comes, you don't seem to mind.\nThis must be the price for a lack of curiosity." << endl;
            gameOver = true;
        }
    }
}