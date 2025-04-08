Obtain the PageRank distribution of a static graph (in MTX format).

In this experiment, we measure the **PageRank distribution** of a number of
**static graph datasets**. As with [degrees], logging all the rank value of a
graph is *not* *feasible*. Therefore, we *compress the rank distribution* into
**blocks** (or *bins*) such that there are a total of **256 blocks**, starting
from `0` to the `MAX_RANK` of a vertex in the graph (this is a value smaller
than `1`). The PageRank distribution is then measured by counting the number of
nodes in each block.

The results show that web graphs have a *significantly skewed* **dual power-law**
**PageRank distribution**, i.e., as with the [degree distribution][degrees],
the PageRank distribution follows a power-law distribution in the **low-rank**
**region** and another power-law distribution in the **moderate-rank region**. The
transition point between the two power-law regions can be called the **knee** of
the PageRank distribution. Very few vertices in the **web graphs** have a high
PageRank value, and they appear to be randomly sprinkled. The PageRank distribution
in **social networks** is *less skewed*, and the *knee* is less pronounced.

The PageRank distribution is however completely different in **road networks**
and **protein k-mer graphs**. Here, we appear to be forming *mountain ranges*,
with sharp peaks, steep slopes on the left side, and a long tail on the right
side. This likely due to such real-world graphs being undirected (along with
social networks), as well as being unformly connected overall (in contrast to
digital-world web graphs). Does this mean that digital networks exaggerate the
rich vs poor divide?

All outputs are saved in a [gist] and a small part of the output is listed here.
Some [charts] are also included below, generated from [sheets].

<br>

[![](https://i.imgur.com/MsGBTkF.png)][sheets]<br>
[![](https://i.imgur.com/jkI5Zeg.png)][sheets]<br>
[![](https://i.imgur.com/hl6csda.png)][sheets]<br>
[![](https://i.imgur.com/hmck1xe.png)][sheets]<br>
[![](https://i.imgur.com/Aok44N1.png)][sheets]<br>
[![](https://i.imgur.com/pPF8Y5n.png)][sheets]<br>
[![](https://i.imgur.com/LB1xXQj.png)][sheets]<br>
[![](https://i.imgur.com/6USeZG5.png)][sheets]<br>
[![](https://i.imgur.com/f6GfbaB.png)][sheets]<br>
[![](https://i.imgur.com/7C2EoQo.png)][sheets]<br>
[![](https://i.imgur.com/dUNsVCW.png)][sheets]<br>
[![](https://i.imgur.com/s9GwmlC.png)][sheets]<br>
[![](https://i.imgur.com/n1PENht.png)][sheets]<br>

<br>
<br>


[![](https://img.youtube.com/vi/E8WaFvwtphY/maxresdefault.jpg)](https://www.youtube.com/watch?v=E8WaFvwtphY)<br>
[![ORG](https://img.shields.io/badge/org-puzzlef-green?logo=Org)](https://puzzlef.github.io)
[![DOI](https://zenodo.org/badge/661505932.svg)](https://zenodo.org/badge/latestdoi/661505932)
![](https://ga-beacon.deno.dev/G-KD28SG54JQ:hbAybl6nQFOtmVxW4if3xw/github.com/puzzlef/graph-pagerank-distribution)

[degrees]: https://github.com/puzzlef/graph-degree-distribution
[gist]: https://gist.github.com/wolfram77/aba4755b75b46313ffe75c225fbdae2b
[charts]: https://imgur.com/a/CHc6wKM
[sheets]: https://docs.google.com/spreadsheets/d/1ybRyxH5-87FqEvKgA6N9jf8lwjMHKtw7rWvLbQ_77mc/edit?usp=sharing
