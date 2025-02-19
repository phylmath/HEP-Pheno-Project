#	Running from personal laptop
# gen%: gen%.cc
# #	compile script
# 	g++ -O $@.cc -o $@ \
# 	-I/home/muffin/0-software/pythia8312/include `root-config --cflags` \
# 	-I/home/muffin/0-software/fjcore-3.4.3/ \
# 	-lpythia8 -L/home/muffin/0-software/pythia8312/lib `root-config --glibs`
# #	run the scipt
# 	./$@

#	Running from work computer
gen%: gen%.cc
#	compile script
	g++ -O $@.cc -o $@ \
	-I/home/pmathew/0-software/pythia8313/include `root-config --cflags` \
	-I/home/pmathew/0-software/fjcore-3.4.3/ \
	-lpythia8 -L/home/pmathew/0-software/pythia8313/lib `root-config --glibs`
#	run the scipt
	./$@