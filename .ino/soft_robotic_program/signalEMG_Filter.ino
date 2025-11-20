/** IIR Butterworth Notch Filter, 4th order.
 * Frequency Sampling 500 
 *  Written in second order sections.
 */
// Notch filter signal 1
int notch50_1( int input) {
 // SOS matrix, obtained from MATLAB
  const double sos[2][6] = {
    1, -1.6185, 1, 1, -1.5686, 0.9642,
    1, -1.6185, 1, 1, -1.6110, 0.99659
  };

  // Gain matrix, obtained from MATLAB
  const double gain[3] = {0.9824, 0.9824, 1};
  
  // Filter coefficients for the first section
  const double b1[3] = {sos[0][0], sos[0][1], sos[0][2]};
  const double a1[3] = {sos[0][3], sos[0][4], sos[0][5]};
  
  // Filter coefficients for the second section
  const double b2[3] = {sos[1][0], sos[1][1], sos[1][2]};
  const double a2[3] = {sos[1][3], sos[1][4], sos[1][5]};
  int x_n = input;
  
  { // First section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[0];
    y[0] = b1[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b1[i] * x[i] - a1[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  { // Second section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[1];
    y[0] = b2[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b2[i] * x[i] - a2[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  return x_n * gain[2];
}

// Notch 100 Hz
int notch100_1( int input) {
 // SOS matrix, obtained from MATLAB
  const double sos[2][6] = {
    1, -0.6182, 1, 1, -0.5740, 0.9649,
    1, -0.6182, 1, 1, -0.6405, 0.9653
  };

  // Gain matrix, obtained from MATLAB
  const double gain[3] = {0.9824, 0.9824, 1};
  
  // Filter coefficients for the first section
  const double b1[3] = {sos[0][0], sos[0][1], sos[0][2]};
  const double a1[3] = {sos[0][3], sos[0][4], sos[0][5]};
  
  // Filter coefficients for the second section
  const double b2[3] = {sos[1][0], sos[1][1], sos[1][2]};
  const double a2[3] = {sos[1][3], sos[1][4], sos[1][5]};
  int x_n = input;
  
  { // First section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[0];
    y[0] = b1[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b1[i] * x[i] - a1[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  { // Second section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[1];
    y[0] = b2[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b2[i] * x[i] - a2[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  return x_n * gain[2];
}

// Notch 150
int notch150_1( int input) {
 // SOS matrix, obtained from MATLAB
  const double sos[2][6] = {
    1, 0.6182, 1, 1, 0.5740, 0.9649,
    1, 0.6182, 1, 1, 0.6405, 0.9653
  };
  // Gain matrix, obtained from MATLAB
  const double gain[3] = {0.9824, 0.9824, 1};
  
  // Filter coefficients for the first section
  const double b1[3] = {sos[0][0], sos[0][1], sos[0][2]};
  const double a1[3] = {sos[0][3], sos[0][4], sos[0][5]};
  
  // Filter coefficients for the second section
  const double b2[3] = {sos[1][0], sos[1][1], sos[1][2]};
  const double a2[3] = {sos[1][3], sos[1][4], sos[1][5]};
  int x_n = input;
  
  { // First section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[0];
    y[0] = b1[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b1[i] * x[i] - a1[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  { // Second section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[1];
    y[0] = b2[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b2[i] * x[i] - a2[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  return x_n * gain[2];
}

//Notch 200 Hz
int notch200_1( int input) {
 // SOS matrix, obtained from MATLAB
  const double sos[2][6] = {
    1, 1.6185, 1, 1, 1.5686, 0.9649,
    1, 1.6185, 1, 1, 1.6110, 0.9659
  };
  // Gain matrix, obtained from MATLAB
  const double gain[3] = {0.9824, 0.9824, 1};
  
  // Filter coefficients for the first section
  const double b1[3] = {sos[0][0], sos[0][1], sos[0][2]};
  const double a1[3] = {sos[0][3], sos[0][4], sos[0][5]};
  
  // Filter coefficients for the second section
  const double b2[3] = {sos[1][0], sos[1][1], sos[1][2]};
  const double a2[3] = {sos[1][3], sos[1][4], sos[1][5]};
  int x_n = input;
  
  { // First section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[0];
    y[0] = b1[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b1[i] * x[i] - a1[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  { // Second section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[1];
    y[0] = b2[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b2[i] * x[i] - a2[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  return x_n * gain[2];
}

// Notch filter signal 2
int notch50_2( int input) {
 // SOS matrix, obtained from MATLAB
  const double sos[2][6] = {
    1, -1.6185, 1, 1, -1.5686, 0.9642,
    1, -1.6185, 1, 1, -1.6110, 0.99659
  };

  // Gain matrix, obtained from MATLAB
  const double gain[3] = {0.9824, 0.9824, 1};
  
  // Filter coefficients for the first section
  const double b1[3] = {sos[0][0], sos[0][1], sos[0][2]};
  const double a1[3] = {sos[0][3], sos[0][4], sos[0][5]};
  
  // Filter coefficients for the second section
  const double b2[3] = {sos[1][0], sos[1][1], sos[1][2]};
  const double a2[3] = {sos[1][3], sos[1][4], sos[1][5]};
  int x_n = input;
  
  { // First section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[0];
    y[0] = b1[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b1[i] * x[i] - a1[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  { // Second section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[1];
    y[0] = b2[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b2[i] * x[i] - a2[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  return x_n * gain[2];
}

int notch100_2( int input) {
 // SOS matrix, obtained from MATLAB
  const double sos[2][6] = {
    1, -0.6182, 1, 1, -0.5740, 0.9649,
    1, -0.6182, 1, 1, -0.6405, 0.9653
  };
  // Gain matrix, obtained from MATLAB
  const double gain[3] = {0.9824, 0.9824, 1};
  
  // Filter coefficients for the first section
  const double b1[3] = {sos[0][0], sos[0][1], sos[0][2]};
  const double a1[3] = {sos[0][3], sos[0][4], sos[0][5]};
  
  // Filter coefficients for the second section
  const double b2[3] = {sos[1][0], sos[1][1], sos[1][2]};
  const double a2[3] = {sos[1][3], sos[1][4], sos[1][5]};
  int x_n = input;
  
  { // First section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[0];
    y[0] = b1[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b1[i] * x[i] - a1[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  { // Second section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[1];
    y[0] = b2[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b2[i] * x[i] - a2[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  return x_n * gain[2];
}

// Notch 150
int notch150_2( int input) {
 // SOS matrix, obtained from MATLAB
  const double sos[2][6] = {
    1, 0.6182, 1, 1, 0.5740, 0.9649,
    1, 0.6182, 1, 1, 0.6405, 0.9653
  };
  // Gain matrix, obtained from MATLAB
  const double gain[3] = {0.9824, 0.9824, 1};
  
  // Filter coefficients for the first section
  const double b1[3] = {sos[0][0], sos[0][1], sos[0][2]};
  const double a1[3] = {sos[0][3], sos[0][4], sos[0][5]};
  
  // Filter coefficients for the second section
  const double b2[3] = {sos[1][0], sos[1][1], sos[1][2]};
  const double a2[3] = {sos[1][3], sos[1][4], sos[1][5]};
  int x_n = input;
  
  { // First section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[0];
    y[0] = b1[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b1[i] * x[i] - a1[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  { // Second section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[1];
    y[0] = b2[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b2[i] * x[i] - a2[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  return x_n * gain[2];
}

//Notch 200 Hz
int notch200_2( int input) {
 // SOS matrix, obtained from MATLAB
  const double sos[2][6] = {
    1, 1.6185, 1, 1, 1.5686, 0.9649,
    1, 1.6185, 1, 1, 1.6110, 0.9659
  };
  // Gain matrix, obtained from MATLAB
  const double gain[3] = {0.9824, 0.9824, 1};
  
  // Filter coefficients for the first section
  const double b1[3] = {sos[0][0], sos[0][1], sos[0][2]};
  const double a1[3] = {sos[0][3], sos[0][4], sos[0][5]};
  
  // Filter coefficients for the second section
  const double b2[3] = {sos[1][0], sos[1][1], sos[1][2]};
  const double a2[3] = {sos[1][3], sos[1][4], sos[1][5]};
  int x_n = input;
  
  { // First section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[0];
    y[0] = b1[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b1[i] * x[i] - a1[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  { // Second section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[1];
    y[0] = b2[0] * x[0];

    for (int i = 1; i < 3; i++) {
      y[0] += b2[i] * x[i] - a2[i] * y[i];
    }
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  return x_n * gain[2];
}

/** IIR Butterworth Bandpass Filter, 4th order.
 * Frequency Sampling 500 
 *  Written in second order sections.
 */

// Bandpass signal 1
int bandpass1(int input) {
  const double sos[2][6] = {
    1,            0,           -1,            1,      -1.4822,       0.6220,
    1,            0,           -1,            1,       0.2357,       0.2789
    // 1, -2, 1, 1, -1.9492, 0.95307,
    // 1, -2, 1, 1, -1.8866, 0.89034
  };
  // Gain matrix, obtained from MATLAB
  const double gain[3] = {0.5173, 0.5173, 1};

  // Filter coefficients for the first section
  const double b1[3] = {sos[0][0], sos[0][1], sos[0][2]};
  const double a1[3] = {sos[0][3], sos[0][4], sos[0][5]};
  
  // Filter coefficients for the second section
  const double b2[3] = {sos[1][0], sos[1][1], sos[1][2]};
  const double a2[3] = {sos[1][3], sos[1][4], sos[1][5]};
  int x_n = input;
  
  { // First section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[0];
    y[0] = b1[0] * x[0];

    for (int i = 1; i < 3; i++)
      y[0] += b1[i] * x[i] - a1[i] * y[i];
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  { // Second section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[1];
    y[0] = b2[0] * x[0];

    for (int i = 1; i < 3; i++)
      y[0] += b2[i] * x[i] - a2[i] * y[i];
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  return x_n * gain[2];
}

// Bandpass signal 2
int bandpass2(int input) {
  const double sos[2][6] = {
    1,            0,           -1,            1,      -1.4822,       0.6220,
    1,            0,           -1,            1,       0.2357,       0.2789
    // 1, -2, 1, 1, -1.9492, 0.95307,
    // 1, -2, 1, 1, -1.8866, 0.89034
  };

  // Gain matrix, obtained from MATLAB
  const double gain[3] = {0.5173, 0.5173, 1};

  
  // Filter coefficients for the first section
  const double b1[3] = {sos[0][0], sos[0][1], sos[0][2]};
  const double a1[3] = {sos[0][3], sos[0][4], sos[0][5]};
  
  // Filter coefficients for the second section
  const double b2[3] = {sos[1][0], sos[1][1], sos[1][2]};
  const double a2[3] = {sos[1][3], sos[1][4], sos[1][5]};
  int x_n = input;
  
  { // First section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[0];
    y[0] = b1[0] * x[0];

    for (int i = 1; i < 3; i++)
      y[0] += b1[i] * x[i] - a1[i] * y[i];
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  { // Second section
    static double x[3] = {};
    static double y[3] = {};

    x[0] = x_n * gain[1];
    y[0] = b2[0] * x[0];

    for (int i = 1; i < 3; i++)
      y[0] += b2[i] * x[i] - a2[i] * y[i];
    for (int i = 2; i > 0; i--) {
      x[i] = x[i - 1];
      y[i] = y[i - 1];
    }
    x_n = y[0];
  }
  return x_n * gain[2];
}