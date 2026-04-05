//
//  main.cpp
//  GroupProject-MazeRunner
//
//  Created by Joel Flanagan on 4/2/26.
//

#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include "racer.h"
#include "constants.h"

using namespace std;
bool mazeContains(const vector<point> &maze, const point &p) {
    for (point point : maze) {
        if (point == p) return true;
    }
    return false;
}

int main() {
    // Questions for Booth
    // Joel: Where does the maze begin and end in the maze.txt?
    // Joel: Is SDLPlotter_H not given?
    // Joel: How far can the racer go forward (can they go one bloack forward or two? Can they go diagonally)?
    Racer racer;
    stack<int> directions;
    stack<point> pointsVisited;
    vector<point> maze;
    ifstream inFile;
    
    inFile.open("maze.txt");
    if (!inFile) {
        cerr << "File not open" << endl;
        exit(1);
    }
    
    point p(0, 0);
    while (inFile >> p.x >> p.y) {
        maze.push_back(p);
    }
    
    // Assuming the last point at the end of the file is the exit
    point pExit(p.x, p.y);
    pointsVisited.push(point(0, 0));
    directions.push(EAST);
    cout << pointsVisited.top().x << endl;
    bool exit = false;
    while (!pointsVisited.empty() && !exit) {
        if (point(pointsVisited.top().x, pointsVisited.top().y) == pExit)  {
            exit == true;
        }
        
        cout << "In maze" << endl;
        cout << "Top: " << pointsVisited.top().x << " " << pointsVisited.top().y << endl;
        p = pointsVisited.top();
        int a = directions.top();
        switch(directions.top()) {
            case EAST:
                a = SOUTH;
                p = point(pointsVisited.top().x + 1, pointsVisited.top().y);
                directions.pop();
                directions.push(a);
                
                if (mazeContains(maze, p)) {
                    pointsVisited.push(p);
                    directions.push(EAST);
                }
                
                break;
            case SOUTH:
                a = WEST;
                p = point(pointsVisited.top().x, pointsVisited.top().y + 1);
                
                directions.pop();
                directions.push(a);
                if (mazeContains(maze, p)) {
                    pointsVisited.push(p);
                    directions.push(EAST);
                }
                break;
            case WEST:
                a = NORTH;
                p = point(pointsVisited.top().x - 1, pointsVisited.top().y);
                
                directions.pop();
                directions.push(a);
                if (mazeContains(maze, p)) {
                    pointsVisited.push(p);
                    directions.push(EAST);
                }
                break;
            case NORTH:
                a = 5;
                p = point(pointsVisited.top().x, pointsVisited.top().y - 1);
                
                directions.pop();
                directions.push(a);
                if (mazeContains(maze, p)) {
                    pointsVisited.push(p);
                    directions.push(EAST);
                }
                
                break;
            default:
                directions.pop();
                pointsVisited.pop();
                break;
            
        }
        
    }
    if (exit) {
        cout << "Exit found." << endl;
    }
    else {
        cout << "Exit not found." << endl;
    }
    // while stack not empty and exit not found
    
    return 0;
}
