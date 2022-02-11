#include "Graph.h"
#include <stdexcept>
#include <iostream>

Graph::Graph() {}

Graph::Graph(unordered_map<int, Airport> airports) {
    _airports = airports;
}
Graph::Graph(const string &airport_file, const string &route_file) {
    //Add Airports to _airport
    std::ifstream airport_ifs(airport_file);
    if(!airport_ifs.is_open()) {
        throw std::runtime_error("Airport file name invalid");
    }

    LoadAirports(airport_ifs);

    //Add Routes to matching Airports in _airport
    std::ifstream route_ifs(route_file);
    if(!route_ifs.is_open()) {
        throw std::runtime_error("Route file name invalid");
    }
    LoadRoutes(route_ifs);
    

}
void Graph::LoadAirports(ifstream &ifs) {
    string line;
    //Reads in one airport per line, adding each airport to _airports
    while(std::getline(ifs, line)) {
        Airport curr_airport;
        size_t idx = 0;
        curr_airport.SetID(std::stoi(SubStrCommaSeparated(line, idx)));
        curr_airport.SetName(SubStrSingleQuoteSeparated(line, idx));
        curr_airport.SetCity(SubStrSingleQuoteSeparated(line, idx));
        curr_airport.SetCountry(SubStrSingleQuoteSeparated(line, idx));
        curr_airport.SetLatitude(std::stod(SubStrCommaSeparated(line, idx)));
        curr_airport.SetLongitude(std::stod(SubStrCommaSeparated(line, idx)));
        AddAirport(curr_airport);
    }
}
void Graph::LoadRoutes(ifstream &ifs) {
    string line;
    while(std::getline(ifs, line)) {
        Route curr_route;
        size_t idx = 0;
        curr_route.SetSourceID(std::stoi(SubStrCommaSeparated(line, idx)));
        curr_route.SetDestID(std::stoi(SubStrCommaSeparated(line, idx)));
        curr_route.SetDistance(std::stod(SubStrCommaSeparated(line, idx)));
        AddRoute(curr_route);
    }
}
string Graph::SubStrCommaSeparated(const string &line, size_t &idx) {
    string substr;
    for(; idx < line.size(); ++idx) {
        if(line.at(idx) == ',') break;
        substr.push_back(line.at(idx));
    }
    idx++;
    return substr;
}
string Graph::SubStrSingleQuoteSeparated(const string &line, size_t &idx) {
    string substr;
    bool prev_quote = false; //use to ignore the second quote of a double quote
    idx++; //skip the first single quote
    
    for(; idx < line.size() - 1; ++idx) {
        //If the closing single quote is reached, break
        if(line.at(idx) == '\"' && line.at(idx+1) != '\"' && prev_quote == false) {
            break;
        }
        //If second quote " of double quote "", add it to substr and go to next idx
        else if(prev_quote == true) {
            substr.push_back(line.at(idx));
            prev_quote = false;
        } 
        //If first quote of double quote "", do nothing and go to next idx
        else if(line.at(idx) == '\"' && line.at(idx+1) == '\"') {
            prev_quote = true;
        }
        //Otherwise, add to substr
        else {
            substr.push_back(line.at(idx));
        }
    }
    idx+=2; //skip the idx of the single quote and the comma
    return substr;
}
//Adds airport to graph, using the airport's ID as the key
void Graph::AddAirport(Airport airport) {
    _airports[airport.GetID()] = airport;
}
void Graph::AddRoute(Route route) {
    //If airport's source ID is found, add route to source airport's list
    if(_airports.find(route.GetSourceID()) != _airports.end()) {
        _airports.find(route.GetSourceID())->second.AddRoute(route); 
    } 
    //The following should not be reached if using routes_clean.dat, since all routes
    //in that file have been confirmed to have a valid source and destination
    //airport.
    else {
        cout << "not found" << endl;
    }
}
unordered_map<int, Airport> Graph::GetAirports() {
    return _airports;
}

bool Graph::PathExists(Airport source, Airport dest) {
    //If either source or destination airport does not exist, return false
    if((_airports.find(source.GetID()) == _airports.end()) || (_airports.find(dest.GetID()) == _airports.end())) {
        return false;
    }
    unordered_set<int> visited; //adds to set if visited. find: O(1) average
    //Perform BFS:
    queue<Airport> q;
    int dest_id = dest.GetID();

    //Push the source airport and mark it as visited
    q.push(source);
    visited.insert(source.GetID());
    //Performs BFS until destination is reached
    while(!q.empty()) {
        Airport curr_airport = q.front();
        q.pop();
        if(curr_airport.GetID() == dest_id) return true;
        //Add every non-visited destination route to queue
        for(Route& r: curr_airport.GetRoutes()) {
            int next_id = r.GetDestID();
            if(next_id == dest_id) return true;
            //If not already visited, add next airport to queue
            if(visited.find(next_id) == visited.end()) {
                visited.insert(next_id); //set next airport as visited
                q.push(_airports.find(next_id)->second); //add next airport
            }

        }

    }
    return false;
}

vector<pair<string, int>> Graph::BFS(Airport source) {
    vector<pair<string, int>> destinations;

    //if source does not exist
    if((_airports.find(source.GetID()) == _airports.end())) {
        std::cout << "Invalid airport source" << std::endl;
        return destinations;
    }
    queue<Airport> q;
    unordered_map<int, int> visited; //adds to set if visited. visited.second keeps track of distance.
    //Add source airport name to vector. #of stops = 0
    destinations.push_back({source.GetName(), 0});
    q.push(source);
    visited[source.GetID()] = 0;
    //Perform BFS from source
    while(!q.empty()) {
        Airport curr_airport = q.front();
        q.pop();
        int curr_numstops = visited.find(curr_airport.GetID())->second; //# of stops for current airport
        //Add every non-visited destination route to queue. Pushes to destinations vector with #of stops.
        for(Route& r: curr_airport.GetRoutes()) {
            int next_id = r.GetDestID();

            //If not already visited, add next airport to queue
            if(visited.find(next_id) == visited.end()) {
                visited[next_id] = curr_numstops+1; //set next airport as visited
                //Add airport name and # of stops
                destinations.push_back({_airports.find(next_id)->second.GetName(), curr_numstops+1});
                q.push(_airports.find(next_id)->second); //add next airport
            }

        }
    }
    return destinations;
}

vector<int> Graph::AirportsInPath(Airport source) {
    vector<int> destinations;

    //if source does not exist
    if((_airports.find(source.GetID()) == _airports.end())) {
        std::cout << "Invalid airport source" << std::endl;
        return destinations;
    }
    queue<Airport> q;
    unordered_map<int, int> visited; //adds to set if visited. visited.second keeps track of distance.
    //Add source airport name to vector. #of stops = 0
    destinations.push_back(source.GetID());
    q.push(source);
    visited[source.GetID()] = 0;
    //Perform BFS from source
    while(!q.empty()) {
        Airport curr_airport = q.front();
        q.pop();
        int curr_numstops = visited.find(curr_airport.GetID())->second; //# of stops for current airport
        //Add every non-visited destination route to queue. Pushes to destinations vector with #of stops.
        for(Route& r: curr_airport.GetRoutes()) {
            int next_id = r.GetDestID();

            //If not already visited, add next airport to queue
            if(visited.find(next_id) == visited.end()) {
                visited[next_id] = curr_numstops+1; //set next airport as visited
                //Add airport ID
                destinations.push_back(next_id);
                q.push(_airports.find(next_id)->second); //add next airport
            }

        }
    }
    return destinations;
}

//Dijkstra's Algorithm to find the shortest path between two airports.
typedef pair<int, int> pairii;
vector<string> Graph::FindShortestPath(Airport source, Airport dest) {
    vector<string> stops;
    if((_airports.find(source.GetID()) == _airports.end())) {
        std::cout << "Invalid airport source" << std::endl;
        return stops;
    }
    if((_airports.find(dest.GetID()) == _airports.end())) {
        std::cout << "Invalid airport destination" << std::endl;
        return stops;
    }
    if(PathExists(source, dest) == false) {
        std::cout << "Path doesn't exist" << std::endl;
        return stops;
    }
    vector<int> destinations = AirportsInPath(source); //Get a vector of all airports in paths from source
    //int arr_size = destinations.size();
    unordered_map<int, int> dist; //Airport ID, distance from source
    unordered_map<int, int> prev; //Airport ID, previous airport visited
    unordered_set<int> visited; //Keeps track of visited nodes
    for(int& airport_id : destinations) {
        dist[airport_id] = 9999999; //initialize distance as unreachable number
        prev[airport_id] = -1; //initialize previous airport as unreachable airport
    }

    //Use a min-heap for pairs ordered by distance. 
    //pair.first is the distance, pair.second is the airport ID
    priority_queue <pairii, vector<pairii>, greater<pairii>> pq;
    dist[source.GetID()] = 0; // set distance of start to 0
    prev[source.GetID()] = -1;
    for(int& airport_id : destinations) {
        //Put in the priority queue
        pq.push(make_pair(dist[airport_id], airport_id));
    }
    //std::ofstream ofs("route_2965.dat");
    while(!pq.empty()) {
        pairii curr_airport = pq.top(); // get least distance Airport
        pq.pop();
        //cout << "Curr: " << _airports.find(curr_airport.second)->second.GetName() << endl;
        visited.insert(curr_airport.second); //set as visited
        //For every next stop connected to the airport
        for(Route & route : _airports.find(curr_airport.second)->second.GetRoutes()) {
            //If current distance at next airport B is larger than distance of current
            // + distance to B, update distance
            //Route destination must exist in possible destinations from source
            if(dist.find(route.GetDestID()) != dist.end()) {
                int temp_distance = dist[route.GetSourceID()] + route.GetDistance();
                if(dist[route.GetDestID()] >  temp_distance) {
                    dist[route.GetDestID()] = temp_distance;
                    prev[route.GetDestID()] = route.GetSourceID();
                }
            }
            
        }
        
    }
    //Now trace back path
   /* std::ofstream ofs("testing.dat");
    for(int& airport_id : destinations) {
        ofs << source.GetID() << " " << airport_id << " " << dist[airport_id] << " " << prev[airport_id] <<endl;
    }*/
    stack<int> s;
    int curr_id = dest.GetID();
    while(prev[curr_id] != -1) {
        s.push(curr_id);
        curr_id = prev[curr_id];
    }
    s.push(curr_id);
    while(!s.empty()) {
        stops.push_back(_airports.find(s.top())->second.GetName());
        s.pop();
    }
    return stops;

}


