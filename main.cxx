#include <cstdint>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <omp.h>
#include "src/main.hxx"

using namespace std;




// Fixed config
#ifndef MAX_THREADS
#define MAX_THREADS 64
#endif




// PERFORM EXPERIMENT
// ------------------

template <class G>
void runExperiment(const G& x) {
  using K = typename G::key_type;
  if (x.empty()) return;
  size_t  N = x.order();
  auto degs = degrees(x);
  auto dist = degreeDistribution(x);
  auto dmax = max_element(degs.begin(), degs.end());
  // Compress the distribution to upto 256 entries
  size_t step = size_t(max(K(1), ceilDiv(*dmax + K(1), K(256))));
  vector<K> cdist(256);
  for (size_t d=0; d<=*dmax; ++d)
    cdist[d/step] += dist[d];
  // Print the compressed distribution
  for (size_t d=0; d<256; ++d)
    printf("{block: %zu, degrees: %zu-%zu, count: %zu}\n", d, d*step, (d+1)*step-1, size_t(cdist[d]));
}


int main(int argc, char **argv) {
  using K = uint32_t;
  char *file = argv[1];
  bool addSelfLoops   = argc>2? stoi(argv[2]) : false;
  bool makeUndirected = argc>3? stoi(argv[3]) : false;
  omp_set_num_threads(MAX_THREADS);
  printf("OMP_NUM_THREADS=%d\n", MAX_THREADS);
  printf("Loading graph %s ...\n", file);
  OutDiGraph<K, None, None> x;
  readMtxOmpW(x, file); println(x);
  auto ft = [](auto u) { return true; };
  if (addSelfLoops)   { selfLoopOmpU(x, None(), ft); print(x); printf(" (selfLoopAllVertices)\n"); }
  if (makeUndirected) { x = symmetricizeOmp(x);      print(x); printf(" (symmetricize)\n"); }
  runExperiment(x);
  printf("\n");
  return 0;
}
