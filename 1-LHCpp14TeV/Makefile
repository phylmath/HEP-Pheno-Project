tut%: tut%.cc

#	compiling script file
	g++ -I/home/muffin/0-software/pythia8312/include $@.cc -o $@ -lpythia8 -L/home/muffin/0-software/pythia8312/lib

#	run the pythia code
	./$@

delete:

	rm tut_p101

gen_LHCpp14TeV: gen_LHCpp14TeV.cc
	
#	compiling script file
	g++ -I/home/muffin/0-software/pythia8312/include `root-config --cflags` $@.cc -o $@ -lpythia8 -L/home/muffin/0-software/pythia8312/lib `root-config --glibs`

#	run the pythia code
	./gen_LHCpp14TeV
