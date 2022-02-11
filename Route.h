#ifndef ROUTE_H
#define ROUTE_H
#include <string>
#include <vector>

using namespace std;
class Route {

    public:
        Route();
        Route(int source_id, int dest_id, double distance);
        int GetSourceID();
        int GetDestID();
        double GetDistance();
        void SetSourceID(int id);
        void SetDestID(int id);
        void SetDistance(double distance);
    private:
        int _source_id; //source airport ID
        int _dest_id; //destination airport ID
        double _distance; //destination between source and destination airports
};


#endif