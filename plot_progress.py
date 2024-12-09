import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

years = np.arange(2015, 2025)
days = np.arange(1, 25)
langs = {
  2024: 'vim/C++',
  2023: 'C++',
  2022: 'AWK',
  2021: 'vimscript',
  2020: 'vim',
  2019: 'C++',
  2018: 'C',
  2017: 'bash',
}

def count_lines(file_path):

  if not os.path.exists(file_path):
    return 0

  with open(file_path, 'r') as file:
    return len(file.readlines())

matrix = np.zeros((len(years), len(days)))

for y, year in enumerate(years):
  for d, day in enumerate(days):
    matrix[y][d] = count_lines(f'{year}/day{day:02}/solution.txt')

fig, ax = plt.subplots()
colours = [
  (0., 0., 0., 0.),
  (.6, .6, .6, 1.),
  (.8, .8, .8, 1.),
]

cmap = ListedColormap(colours)

im = plt.pcolormesh(matrix, edgecolors='gray', linewidth=1, cmap=cmap)
plt.clim(0, 3)

ax.set_yticks(np.arange(len(years)) + .5, years)
ax.set_xticks(np.arange(len(days)) + .5 , days, rotation=90)

aspect = 'equal'

ax_right = ax.twinx()
ax_right.set_yticks(np.arange(len(years)) * 2., [langs[year] if year in langs else '?' for year in years]) # why * 2. ?
plt.gca().set_aspect(aspect)

ax.tick_params(axis='both', which='both', colors='gray')
ax_right.tick_params(axis='both', which='both', colors='gray')
plt.gca().set_aspect(aspect)

ax_right.spines['bottom'].set_color('gray')
ax_right.spines['top'].set_color('gray')
ax_right.spines['right'].set_color('gray')
ax_right.spines['left'].set_color('gray')

ax.set_xlabel('day', color='gray')
ax.set_ylabel('year', color='gray')

out_file = 'progress.png'

plt.savefig(out_file, bbox_inches='tight', transparent='true')
