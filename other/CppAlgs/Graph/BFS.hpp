#pragma once
#include "../public/public.hpp"

void BFSTest();
pair<vector<int>, vector<int>> BFSInterface(vector<vector<bool>> graph, int start);
vector<int> ReconstructPathBFS(int st, int tar, vector<int> prev);
pair<vector<int>, vector<int>> multipleBFSInterface(vector<vector<bool>> graph, vector<int> start);
vector<int> ReconstructPathmBFS(int tar, vector<int> prev);
