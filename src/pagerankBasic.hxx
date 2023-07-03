#pragma once
#include <utility>
#include <algorithm>
#include <vector>
#include "_main.hxx"
#include "pagerank.hxx"

using std::vector;
using std::swap;
using std::max;




// PAGERANK LOOP
// -------------

/**
 * Perform PageRank iterations upon a graph.
 * @param a current rank of each vertex (updated)
 * @param r previous rank of each vertex (updated)
 * @param xt transpose of original graph
 * @param P damping factor [0.85]
 * @param E tolerance [10^-10]
 * @param L max. iterations [500]
 * @param EF error function (L1/L2/LI)
 * @returns iterations performed
 */
template <bool ASYNC=false, bool DEAD=false, class H, class V>
inline int pagerankBasicSeqLoop(vector<V>& a, vector<V>& r, const H& xt, V P, V E, int L, int EF) {
  using  K = typename H::key_type;
  size_t N = xt.order();
  int l = 0;
  while (l<L) {
    V C0 = DEAD? pagerankTeleport(xt, r, P) : (1-P)/N;
    pagerankCalculateRanks(a, xt, r, C0, P, E); ++l;  // update ranks of vertices
    V el = pagerankError(a, r, EF);  // compare previous and current ranks
    if (!ASYNC) swap(a, r);          // final ranks in (r)
    if (el<E) break;                 // check tolerance
  }
  return l;
}


#ifdef OPENMP
template <bool ASYNC=false, bool DEAD=false, class H, class V>
inline int pagerankBasicOmpLoop(vector<V>& a, vector<V>& r, const H& xt, V P, V E, int L, int EF) {
  using  K = typename H::key_type;
  size_t N = xt.order();
  int l = 0;
  while (l<L) {
    V C0 = DEAD? pagerankTeleportOmp(xt, r, P) : (1-P)/N;
    pagerankCalculateRanksOmp(a, xt, r, C0, P, E); ++l;  // update ranks of vertices
    V el = pagerankErrorOmp(a, r, EF);  // compare previous and current ranks
    if (!ASYNC) swap(a, r);             // final ranks in (r)
    if (el<E) break;                    // check tolerance
  }
  return l;
}
#endif




// STATIC/NAIVE-DYNAMIC PAGERANK
// -----------------------------

/**
 * Find the rank of each vertex in a graph.
 * @param xt transpose of original graph
 * @param q initial ranks
 * @param o pagerank options
 * @returns pagerank result
 */
template <bool ASYNC=false, bool DEAD=false, class H, class V>
inline PagerankResult<V> pagerankBasicSeq(const H& xt, const vector<V> *q, const PagerankOptions<V>& o) {
  using K = typename H::key_type;
  if  (xt.empty()) return {};
  return pagerankSeq<ASYNC>(xt, q, o, [&](vector<V>& a, vector<V>& r, const H& xt, V P, V E, int L, int EF) {
    return pagerankBasicSeqLoop<ASYNC, DEAD>(a, r, xt, P, E, L, EF);
  });
}


#ifdef OPENMP
template <bool ASYNC=false, bool DEAD=false, class H, class V>
inline PagerankResult<V> pagerankBasicOmp(const H& xt, const vector<V> *q, const PagerankOptions<V>& o) {
  using K = typename H::key_type;
  if  (xt.empty()) return {};
  return pagerankOmp<ASYNC>(xt, q, o, [&](vector<V>& a, vector<V>& r, const H& xt, V P, V E, int L, int EF) {
    return pagerankBasicOmpLoop<ASYNC, DEAD>(a, r, xt, P, E, L, EF);
  });
}
#endif
