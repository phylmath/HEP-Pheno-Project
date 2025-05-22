from matplotlib import pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages
pp   = PdfPages('fig381.pdf')
tmp1 = plt.figure(1)
tmp1.set_size_inches(8.00,6.00)
plot = open('fig381-0.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
vale = [float(x[2]) for x in plot]
plt.hist( valx, vale, weights = valy, histtype='step', color='black', label=r"all events")
plot = open('fig381-1.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
vale = [float(x[2]) for x in plot]
plt.hist( valx, vale, weights = valy, histtype='step', color='red', label=r"Higgsstrahlung")
plot = open('fig381-2.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
vale = [float(x[2]) for x in plot]
plt.hist( valx, vale, weights = valy, histtype='step', color='blue', label=r"WW fusion")
plot = open('fig381-3.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
vale = [float(x[2]) for x in plot]
plt.hist( valx, vale, weights = valy, histtype='step', color='olive', label=r"ZZ fusion")
plot = open('fig381-4.dat')
plot = [line.split() for line in plot]
valx = [float(x[0]) for x in plot]
valy = [float(x[1]) for x in plot]
vale = [float(x[2]) for x in plot]
plt.hist( valx, vale, weights = valy, histtype='step', color='magenta', label=r"$\gamma\gamma$ fusion")
plt.xlim( -1.000e+00, 9.900e+01)
plt.ylim( 0.000e+00, 6.749e-02)
plt.ticklabel_format(axis='y', style='sci', scilimits=(-2,3))
plt.legend(frameon=False,loc='best')
plt.title(r"Charged multiplicity for Higgs production in a 500 GeV e$^+$e$^-$ collider")
plt.xlabel(r"$n_{\mathrm{charged}}$")
plt.ylabel(r"Probability")
pp.savefig(tmp1,bbox_inches='tight')
plt.clf()
pp.close()
