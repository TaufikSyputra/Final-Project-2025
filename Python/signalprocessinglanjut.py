"""
This script processes data EMG that has been filtered
Created on May 2025
@author: Taufik Syahputra
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Load the data from a txt file
#data = pd.read_csv('subjek1.tx')
# data = data.dropna()
a = 5*500
fs = 500
time = np.array(i/fs for i in range(0, a))
print(time, type(time))