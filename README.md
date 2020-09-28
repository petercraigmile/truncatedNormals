## truncatedNormals

Written with <a href="http://www.stat.osu.edu/~hans/">Chris Hans</a>.

Email questions about the code to pfc &lt;AT&gt; stat.osu.edu

An R package with functions for univariate truncated normal distributions.

The R package itself is contained in the folder `truncatedNormals`.


### Installation

For Mac OS and Linux, make sure you have the C and fortran compilers
installed.  After installing the `devtools` R package type

```
devtools::install_github("truncatedNormals", user="petercraigmile", subdir="truncatedNormals") 
```

For windows, download the file <a href="https://github.com/petercraigmile/truncatedNormals/raw/master/releases/current/truncatedNormals.zip">truncatedNormals.zip</a> from the `releases` folder.    Then:

1. Open the R gui, by doubling clicking on the R icon.

2. Click on the `Packages` menu and select `Install package(s) from local zip files...`.  Find the zip file and press `Open`.

3. Your R package will be installed.


After installation, type `library(truncatedNormals)` to use the R library.


### References

- Section 2 of Geweke, J. (1991). "Efficient simulation from the
multivariate normal and student-t distributions subject to linear
constraints". In Keramidas, E. M., editor, Computing Science and
Statistics: Proceedings of the Twenty-Third Symposium on the
Interface, pages 571-578. Interface Foundation of North America,
Fairfax, VA.