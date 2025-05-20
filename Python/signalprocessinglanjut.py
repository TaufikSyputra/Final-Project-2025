"""
This script processes data EMG that has been filtered
Created on May 2025
@author: Taufik Syahputra
"""

import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Load the data from a txt file
signal = pd.read_csv("subject1.txt", sep="\t", header=None)