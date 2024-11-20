tut%: tut%.cc
#	compiling script file
	g++ -I/home/muffin/0-software/pythia8312/include $@.cc -o $@ -lpythia8 -L/home/muffin/0-software/pythia8312/lib
#	run the pythia code
	./$@

delete:
	rm tut_p101

gen_LEPep209GeV: gen_LEPep209GeV.cc
#	compiling script file
	g++ -I/home/muffin/0-software/pythia8312/include `root-config --cflags` $@.cc -o $@ -lpythia8 -L/home/muffin/0-software/pythia8312/lib `root-config --glibs`
#	run the pythia code
	./$@

jet_LEPep209GeV: jet_LEPep209GeV.cc
#	compiling script file
	g++ $@.cc -o $@ `/home/muffin/0-software/fastjet-install/bin/fastjet-config --cxxflags --libs --plugins`
#	run fastjet code
	./$@