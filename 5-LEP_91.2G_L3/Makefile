gen%: gen%.cc
#	compile script
	g++ -O $@.cc -o $@ \
	-I/home/muffin/0-software/pythia8312/include `root-config --cflags` \
	-I/home/muffin/0-software/fjcore-3.4.3/ \
	-lpythia8 -L/home/muffin/0-software/pythia8312/lib `root-config --glibs`
#	run the scipt
	./$@

# -I/home/muffin/0-software/fastjet-install/bin/fastjet-config `--cxxflags --libs --plugins`