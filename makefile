
PACKAGE = truncatedNormals
VER     = 0.6

check:	;
	R CMD check $(PACKAGE)

build:	;
	R CMD INSTALL $(PACKAGE) 

clear:	;
	rm $(PACKAGE)/src/*.o $(PACKAGE)/src/*.so $(PACKAGE)/src/symbols.rds $(PACKAGE)/src/.DS_Store

