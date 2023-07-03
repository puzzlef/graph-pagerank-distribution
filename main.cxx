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

template <class G, class H>
void runExperiment(const G& x, const H& xt) {
  using  K = typename G::key_type;
  vector<double> *init = nullptr;
  if (x.empty()) return;
  size_t N = x.order();
  auto   a = pagerankBasicOmp(xt, init, {1});
  vector<double>& ranks = a.ranks;
  double maxr = *max_element(ranks.begin(), ranks.end());
  // Compress the distribution to upto 256 entries.
  double step = maxr/256;
  vector<K> cdist(256);
  x.forEachVertexKey([&](auto u) {
    size_t b = min(size_t(ranks[u]/step), size_t(255));
    ++cdist[b];
  });
  // Print the compressed distribution
  for (size_t b=0; b<256; ++b)
    printf("{block: %zu, ranks: %.6e -> %.6e, count: %zu}\n", b, b*step, (b+1)*step, size_t(cdist[b]));
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
  if (addSelfLoops)   { selfLoopOmpU(x, None(), ft); print(x);  printf(" (selfLoopAllVertices)\n"); }
  if (makeUndirected) { x = symmetricizeOmp(x);      print(x);  printf(" (symmetricize)\n"); }
  auto xt = transposeWithDegreeOmp(x);               print(xt); printf(" (transposeWithDegree)\n");
  runExperiment(x, xt);
  printf("\n");
  return 0;
}
