import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

def count_lines(file_path):

  if not os.path.exists(file_path):
    return 0

  with open(file_path, 'r') as file:
    return len(file.readlines())

years = np.arange(2015, 2024)
days = np.arange(1, 25)

matrix = np.zeros((len(years), len(days)))

for y, year in enumerate(years):
  for d, day in enumerate(days):
    matrix[len(years) - y - 1][d] = count_lines(f'{year}/day{day:02}/solution.txt')

fig, ax = plt.subplots()

colours = [
  (0., 0., 0., 0.),
  (.6, .6, .6, 1.),
  (.8, .8, .8, 1.),
]

cmap = ListedColormap(colours)

im = plt.pcolormesh(matrix, edgecolors='gray', linewidth=1, cmap=cmap)
plt.clim(0, 3)
plt.gca().set_aspect('equal')

plt.yticks(np.arange(len(years)) + .5, years)
plt.xticks(np.arange(len(days)) + .5 , days)
plt.xticks(rotation=90)

plt.tick_params(axis='both', which='both', colors='gray')

ax.spines['bottom'].set_color('gray')
ax.spines['top'].set_color('gray')
ax.spines['right'].set_color('gray')
ax.spines['left'].set_color('gray')

plt.xlabel('day', color='gray')
plt.ylabel('year', color='gray')

out_file = 'progress.png'

plt.savefig(out_file, bbox_inches='tight', transparent='true')
