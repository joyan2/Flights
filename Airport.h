#ifndef AIRPORT_H
#define AIRPORT_H
#include <string>
#include <vector>
#include <list>

#include "Route.h"

using namespace std;
class Airport {

    public:
        Airport();
        Airport(int id, string name, string city, string country, double latitude, double longitude);
        list<Route> GetRoutes(); //Gets entire list of routes
        void AddRoute(Route route); //Adds a route to the list of routes

        int GetID();
        string GetName();
        string GetCity();
        string GetCountry();
        double GetLatitude();
        double GetLongitude(); 
        void SetID(int id);
        void SetName(string name);
        void SetCity(string city);
        void SetCountry(string country);
        void SetLatitude(double latitude);
        void SetLongitude(double longitude); 
    private:
        int _id; //airport ID
        string _name; //airport name
        string _city; 
        string _country;
        double _latitude;
        double _longitude;
        list<Route> _routes; //Linked list of routes with this airport as source
};

#endif