#include "Airport.h"

Airport::Airport() {}
Airport::Airport(int id, string name, string city, string country, double latitude, double longitude) {
    _id = id;
    _name = name;
    _city = city;
    _country = country;
    _latitude = latitude;
    _longitude = longitude;
}
list<Route> Airport::GetRoutes() {
    return _routes;
}
void Airport::AddRoute(Route route) {
    _routes.push_back(route);
}
int Airport::GetID() {
    return _id;
}
string Airport::GetName() {
    return _name;
}
string Airport::GetCity() {
    return _city;
}
string Airport::GetCountry() {
    return _country;
}
double Airport::GetLatitude() {
    return _latitude;
}
double Airport::GetLongitude() {
    return _longitude;
}
void Airport::SetID(int id) {
    _id = id;
}
void Airport::SetName(string name) {
    _name = name;
}
void Airport::SetCity(string city) {
    _city = city;
}
void Airport::SetCountry(string country) {
    _country = country;
}
void Airport::SetLatitude(double latitude) {
    _latitude = latitude;
}
void Airport::SetLongitude(double longitude) {
    _longitude = longitude;
}
