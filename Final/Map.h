/**
 * @file Map.h
 * @author Phillip Eustace
 * @brief A map file that holds the map and movement functions of the entire game
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
#include "Node.h"

using namespace std;

class Map{
    private:
    
    public:
    Node _map[5][4];
    int currentLeft = 0;
    int currentTop = 0;
    string mapSetting = "\n\n\nYou are trapped in the murky dark at the very bottom of the until-now untouched deep ocean. \nThe only thing separating you from being crushed thus far is a fragile submarine wall. \nHowever, the machine protecting you has broken down, and most of the doors have closed to prepare against flooding.\nFood, water, and air soon begin to run out.\n=====";
    vector<string> MapStrings = {
        "You feel shaking as water pressure tests the bolts of the vessel... though it quickly subsides.",
        "A rumble, you think, comes from a creature surely not yet known to man...",
        "Are you alone?",
        "Another day, another dead zone. Actually, it's the same dead zone as yesterday. You're stuck here, after all.",
        "You had a dream last night that you were stuck on land, unable to go to sea. Topical. Tropical!",
        "You wonder if rescue will ever come.",
        "You glance at the depth gauge. No, that can't be right. It must be broken.",
        "Emergency shields sealed in the viewport. You're not sure you want to see what's out there, though.",
        "What was that?",
        "You thought you heard a voice. No anomalies on the camera audio at that time. The Geiger counter, however...",
        "You did some light exercise before bed. You feel good.",
        "Looks like you finally get some guilt-free time to pursue new hobbies.",
        "I know you're in there.",
        "A crackle on the radio. You can't seem to respond--the microphone was damaged in the crash. Is rescue coming?",
        "You're gaining a hefty amount of weight. Surely you haven't eaten that much? (You have.)",
        "The oxygen system reboots for maintenance. With the low amount of air, it momentarily makes you rather light-headed.",
        "ERROR: UNKNOWN LIFEFORM DETECTED BY STARBOARD EXTERIOR.",
        "It's too big a ship for only crew member, isn't it?",
        "Where did you put that book?",
        "You saw a roach! Oh, no, it's just some paint.",
        "You punch the wall. Not a good idea!",
        "Is there something you're forgetting?",
        "Beep beep beep. I'm a robot!",
        "You wonder if you'll see any divers out here?",
        "You wish you had a dog.",
        "You think of the funniest joke ever made. You don't have anyone to tell it to.",
        "You wonder if water is wet."
    };
    int currentMapDay = 0;
    vector<Node> NodesList = {

        //Structure of a node:
        //id number, name, body text, factor to change, factor change level
        Node(1, "Engineering Bay", "An engineering bay with tools. You optimize the oxygen system.", "air", 10),
        Node(2, "Weapons Room", "While you're not sure weapons are all that helpful here, you do find some rations.", "food", 10),
        Node(3, "Greenhouse", "A greenhouse growing plants. None edible, but you do find some water to drink.", "water", 10),
        Node(4, "Medical Bay", "You're not injured, so nothing really helps. You did find some vitamins, though.", "food", 10),
        Node(5, "Science Room", "Mostly useless, but you find some strange glowing liquid. It doesn't kill you, at least.", "water", 10),
        Node(6, "Bridge", "You'd think there'd be no need for a bridge in a solo vessel. \nYou unplug unnecessary life support for empty chairs.", "air", 10),
        Node(7, "Cargo Hold", "Plenty of water. All the food is spoiled, though.", "water", 10),
        Node(8, "Cryo Room", "The name is just a typo, it's actually daycare room for crying children and it's not cold at all. You find some Goldfish.", "food", 10),
        Node(9, "Fuel Storage", "This thing runs on internal water wheels (don't ask). Some is stuck in the system from before it shut down.", "water", 10),
        Node(10, "Observation Deck", "Air canisters are available in here to simulate going to get a 'breath of fresh air'.", "air", 10),
        Node(11, "Maintenance Tunnel", "The last engineer to work here left some candy.", "food", 10),
        Node(12, "Escape Pod Bay", "None of them work, but there are some bottles of water.", "water", 10),
        Node(13, "Robotics Lab", "You find a robot that recycles CO2 into O2. It's got some stored up.", "air", 10),
        Node(14, "Dormitory", "You had your own stash of snacks in your bedroom.", "food", 10),
        Node(15, "Hydro Room", "Water is gathered here for chemical reactions. Some remains unused.", "water", 10),
        Node(16, "Engine Room", "You fix up a flaw you noticed in the electrical system. Now there's more air!", "air", 10),
        Node(17, "Armory", "Rations were left behind in case of necessity.", "food", 10),
        Node(18, "Communication Hub", "Bottles of water saved up to keep people's whistles wet. Your water, now.", "water", 10),
        Node(19, "Quarantine Zone", "By deactivating the quarantine system, you save some air.", "air", 10),
        Node(20, "Cafeteria", "You find fancy meals you can only eat in their dehydrated form, because the hydrator is broken...", "food", 10),


    };
        Map();
        void BuildRandomMap(Node map[5][4]);
        Node PullRandomNode();
        Node ProvideDummy(int id);
        string TriggerRandomEvent();
        void PrintMap();
        void NewLocation(int row, int col);
        bool NoStoneUnturned();
        int mapSize;
};