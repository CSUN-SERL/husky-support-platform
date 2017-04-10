/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Graph.h
 * Author: serl
 *
 * Created on March 31, 2017, 6:02 PM
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include "Path.h"

using namespace std;

typedef int vertex_t;
typedef double weight_t;


struct neighbor {
    vertex_t target;
    weight_t weight;
    Path::Point point;
    neighbor(vertex_t arg_target, weight_t arg_weight, Path::Point arg_point)
        : target(arg_target), weight(arg_weight), point(arg_point) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;

class Graph
{
    int V;
    adjacency_list_t  adj; //pointer to adjacency list
public:
    Graph();
    Graph(const Graph& orig);
    Graph(int V); // Constructor
    virtual ~Graph(){};
    
    void addEdge(int v, int w, double distance, Path::Point point); // function to add an edge to graph
    void DijkstraComputePaths(vertex_t source,
                        
                          std::vector<weight_t> &min_distance,
                          std::vector<vertex_t> &previous);
    
    std::list<vertex_t> DijkstraGetShortestPathTo(
    vertex_t vertex, const std::vector<vertex_t> &previous);
private:

};

#endif /* GRAPH_H */

