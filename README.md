# Base Computational Biology

This `C` repository, developed during the course of
[IN470 Computational Methods for Biology - A.A.2020/21](http://www.mat.uniroma3.it/users/castiglione/IN470.2020/index.html),
is a collection of programs for biological application.

The repository is _exercise-oriented_; each exercise, with progressive difficulties,
introduces the student to computational biology problems.

## Dependecies

Even if it is not necessary, an useful tool is GnuPlot, always used to present a graphical
solution to exercises.
The path to GnuPlot binary executabe can be set by manually changing the value
of `GP_BIN` macro located in `src/graphics/graphics.h`.

## Structure of the Repository

BaseComputationalBiology
- exercises: Hold the exercises, all referenced by `exercise.h`
- gnuplot-scripts: Holds `GnuPlot` scripts called from the code.
- inputs: Holds the inputs for the exercises (one directory per exercise)
- products: Std target directory where data are stored.
- src: Sources folder
  - biology: genotype generation, mutation and encoding functions
  - graphics: `GnuPlot` related functions
  - patternRecognition: String pattern recognition algorithms
    - knut-Morris-Pratt
    - boyer-Moore
  - randomWalks: random walks on `\mathbb{Z}^D` algorithms
  - utils
    - `allocations.c`
    - `informationTheory.c`
    - `operands.c`
    - `random.c`

## About the Author

[Elia Onofri](https://github.com/eOnofri04)
[e-mail](eonofri@uniroma3.it)
[in](https://www.linkedin.com/in/elia-onofri-80b403173/?locale=en_US)
[ORCID](https://orcid.org/0000-0001-8391-2563)

Applied Mathematics in Computer Security represents my main field of interest.
In particular I am mostly interested in Cryptography (from a theoretical point of view)
and Cryptanalysis (from a computer science point of view).

During my education I have also studied many field about Computer Science that vary
from the Computability and Complexity Analysis to the most recent logical theories
(like λ-calculus, Linear Logic, . . . ).

More recently I have broaden my horizons by confront myself with new perspectives
of the Applied Mathematics like Graph Theory, Computational Biology and Topology,
Machine Learning and Big Data Analysis.


## Bibliography

#### Suggested Books
- M.H. Citterich, F. Ferrè,G. Pavesi. Fondamenti di bioinformatica (2018) Zanichelli.
- E.S. Allman, J.A. Rhodes. Mathematical Models in Biology: An Introduction (2004) Cambridge University Press.
- W.J. Ewens, G.R. Grant. Statistical Methods in Bioinformatics, An Introduction (2005) Springer Verlag.
- R. Durbin, S. Eddy, A. Krogh, G. Mitchison. Biological sequence analysis - Probabilistic models of proteins and nucleic acids (1998) Cambridge University Press.
- C. Bishop. Pattern Classification and Machine Learning (2006) Springer Verlag.
- B.H. Junker, F. Schreiber (eds). Analysis of biological networks (2008) John Wiley & Sons.

#### Indepth Books
- H. Kitano. Foundations of Systems Biology. (2001) The MIT Press
- J.D. Murray. Mathematical Biology (I: An Introduction + II: Spatial Models and Biomedical Applications). (2007) Springer.
- J. Keener, J. Sneyd. Mathematical Physiology (I: Cellular Physiology + II: Systems Physiology). (2009) Springer.
- Z. Szallasi, J. Stelling and V. Periwal (eds.) System Modeling in Cellular Biology. (2006) The MIT Press
- A. Ilachinski. Cellular Automata. A Discrete Universe. (2001) World Scientific.

#### Related Articles
- A.M. Turing. On computable numbers, with an application to Entdcheidungsproblem (1936)
- T. Gardner, J. Faith. Reverse-engineering transcription control networks. Elsevier (2005)
- K. Khoshmanesh, A. Kouzani, S. Nahavandi, S. Baratchi, J.R. Kanwar. At a Glance: Cellular biology for Engineers. Elsevier (2008)
- C.E. Shannon. Prediction and Entropy of Printed English. (1950)
