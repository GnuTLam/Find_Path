#include <bits/stdc++.h>
using namespace std;

double max_y,max_x,min_y,min_x;
struct {
    bool printGraph = false;
    bool drawRoute = true;
    int printLevel = 0;
    size_t k = 0;
} config;

void setMinMax(double x, double y){
    if(max_y<y){
        max_y=y;
    }
    if(max_x<x){
        max_x=x;
    }
    if(min_y>y){
        min_y=y;
    }
    if(min_x>x){
        min_x=x;
    }
}
struct point {
    double x;
    double y;
    point(double x,double y){
        this->x = x;
        this->y = y;
        setMinMax( x, y);
    }
    point(){

    }
    bool operator==(const point &other) const {
        return (this->x==other.x && this->y==other.y);
    }
};
struct lineSegment {
    point p;
    point q;
    lineSegment(point p,point q){
        this->p = p;
        this->q = q;
    };
    lineSegment(){

    }
    bool operator==(const lineSegment &other) const {
        return (this->p==other.p && this->q==other.q) ||
               (this->p==other.q && this->q==other.p);
    }
};

//Type used in the priority queue in the dijkstra function
typedef std::pair<double,std::pair<int,int> > pq_pair;

// Operator overloading for print Point
ostream& operator<<(ostream& os, const point& pt) {
    os << "(" << pt.x << " " << pt.y << ")";
    return os;
}

#include "naive.cpp"

int main(int argc, const char* argv[]){
    max_x=max_y=min_y=min_x=0;

    //Create variables for holding start and endpoint plus the test title
    point start, end;
    string testTitle;

    //Create vector for containing the line segments of the polygons
    vector< vector < lineSegment> > polygons;

    //Create vector for containing the points of the polygons
    vector<point> points;

    //Call function that parses the file input
    readInput(start, end, testTitle, polygons, points);

    vector< vector < int > > graph;
    vector< vector < double > > graphDistance;

    //Vector so we can backtrack the route
    vector<int> route;
    vector< vector < int > > crossesNumber;

    //Get how many points we have
    size_t numberOfPoints = points.size();

    //Create a two dimenstional vector for the graph
    size_t dimension = numberOfPoints*(config.k+1);
    graph.resize(dimension,vector<int>());
    graphDistance.resize(dimension,vector<double>());

    //Call function that calculate the distance
    calculateNumberOfCrossings(crossesNumber, polygons, points);

    makeVisabilityGraph(graph, graphDistance, crossesNumber, points);

    //The graph is constructed call dijksta to calculate the distance
    double distance = dijkstra(graphDistance,graph,route);

    int current = route.size()-1;
    while(current!=-1){
        point p =  points[current%points.size()];
        cout << p;
        current = route[current];
    }
}
