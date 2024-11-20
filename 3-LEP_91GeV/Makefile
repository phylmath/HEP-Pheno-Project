gen_LEP91GeV: gen_LEP91GeV.cc
#	compiling script file
	g++ -I/home/muffin/0-software/pythia8312/include `root-config --cflags` $@.cc -o $@ -lpythia8 -L/home/muffin/0-software/pythia8312/lib `root-config --glibs`
#	run the pythia code
	./$@

jet_LEP91GeV: jet_LEP91GeV.cc
#	compiling script file
	g++ $@.cc -o $@ \
	`/home/muffin/0-software/fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` -I/home/muffin/0-software/pythia8312/include `root-config --cflags` -lpythia8 -L/home/muffin/0-software/pythia8312/lib `root-config --glibs`
#	run fastjet code
	./$@