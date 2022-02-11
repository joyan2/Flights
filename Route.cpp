#include "Route.h"

Route::Route() {
    _distance = 0;
}

Route::Route(int source_id, int dest_id, double distance) {
    _source_id = source_id;
    _dest_id = dest_id;
    _distance = distance;
}
int Route::GetSourceID() {
    return _source_id;
}
int Route::GetDestID() {
    return _dest_id;
}
double Route::GetDistance() {
    return _distance;
}
void Route::SetSourceID(int id) {
    _source_id = id;
}
void Route::SetDestID(int id) {
    _dest_id = id;
}
void Route::SetDistance(double distance) {
    _distance = distance;
}