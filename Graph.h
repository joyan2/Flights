#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <vector>
#include <list>
#include <unordered_map> 
#include <fstream>
#include <queue>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include "Airport.h"
using namespace std;
//This builds a direct, weighted graph where a HashMap of Airports is stored
//as vectors. Each Airport points to its own unique Linked List of Routes.
class Graph {
    public:
        Graph();
        Graph(unordered_map<int, Airport> airports);

        //Builds a graph using an Airport data file and a Route data file
        //Airport data file is in csv format, with the values:
        //[airport_id], [airport_name], [city], [country], [latitude], [longitude]
        //Route data file is in csv format, with the values:
        //[source_airport_id], [dest_airport_id], [distance]
        Graph(const string &airport_file, const string &route_file);
        void AddAirport(Airport airport); //Adds an airport to the map
        void AddRoute(Route route); //Adds a route to the appropriate airport's list
        unordered_map<int, Airport> GetAirports();
        /******************************************************************
         * BFS Traversal
         * ****************************************************************/
        bool PathExists(Airport source, Airport dest); //Determines if there is a path from source to destination airport
        //Takes a source and returns a vector of destination airport names, with number of stops
        //taken to get there. Includes the source airport (# of stops = 0)
        vector<pair<string, int>> BFS(Airport source); 
        //Similar traversal, but only stores the ID of airports that can
        //be reached from source
        vector<int> AirportsInPath(Airport source);

         /******************************************************************
         * Dijkstra's Algorithm to find the shortest path between two Airports.
         * ****************************************************************/
        vector<string> FindShortestPath(Airport source, Airport dest);
    private:
        //Takes an ifstream and creates airports, then places
        //them in the map _airports:
        void LoadAirports(ifstream &ifs);

        //Takes an ifstream and adds routes to the linkedlist
        //associated with the matching source airport ID
        void LoadRoutes(ifstream &ifs);
        //Takes a line and an index reference to the position in the line.
        //Returns a substring from the index to the next comma, updating
        //index to one past the comma
        //Use for numerical values in the csv
        string SubStrCommaSeparated(const string &line, size_t &idx);

        //Takes a line and an index reference to the position in the line.
        //Ignores the first single quote
        //Returns a substring from the index to the next single quote, updating
        //index to two past the single quote (skips the comma). This only works
        //with the specified file format for Airport.
        //Some strings have double quotes to indicate a nickname. These will be
        //trimmed to single quotes, and the rest of the string will be processed.
        //
        //Example string (quotes are part of string): "Bob","Fred"
        //Returns: Bob
        //Example string (quotes are part of string): "Robert ""Bob"" Fischer","Fred"
        //Returns: Robert "Bob" Fischer
        //Use for strings in the csv
        string SubStrSingleQuoteSeparated(const string &line, size_t &idx);
        unordered_map<int, Airport> _airports;
};


#endif