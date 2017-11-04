import numpy as np
import matplotlib.pyplot as pl

data = np.genfromtxt('spikes.txt')

select= np.array([d for d in data if d[1] < 30])
data1= select.transpose()
backgroundcolor = 'white'
pl.figure(1)
pl.subplot(211)
pl.scatter(data1[0],data1[1],alpha=0.8, edgecolors='black', color='grey');
pl.axis([100, 150, 0, 30])
pl.title('neurons that spiked', fontsize=16, color='black', fontstyle='italic')
pl.xlabel('time [ms]', color = 'grey')
pl.ylabel('neuron number', color='grey')
pl.subplots_adjust(hspace=0.5)
pl.subplot(212)
n, bins, patches = pl.hist(data1[0], 50, normed=0, alpha=0.75, color='grey')
pl.axis([100, 150, 0, 30])
pl.title('histogram', fontsize=16, color='black',fontstyle='italic')
pl.xlabel('time (ms)', color = 'grey')
pl.ylabel('frequency', color = 'grey')


pl.show();

