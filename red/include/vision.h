/*vex-vision-config:begin*/
#include "v5.h"
#include "v5_vcs.h"
vex::vision::signature CUBEP = vex::vision::signature (1, 1391, 2071, 1731, 9879, 12923, 11401, 5.1, 0);
vex::vision::signature CUBEO = vex::vision::signature (2, 8191, 11221, 9706, -2723, -2335, -2529, 2.8, 0);
vex::vision::signature CUBEG = vex::vision::signature (3, -7007, -5087, -6047, -5835, -4083, -4959, 3.1, 0);
vex::vision::signature MATB = vex::vision::signature (4, -2227, -1801, -2014, 4809, 5761, 5285, 4.3, 0);
vex::vision::signature MATR = vex::vision::signature (5, 5123, 5825, 5474, -1, 491, 245, 3.2, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision1 = vex::vision (vex::PORT20, 50, CUBEP, CUBEO, CUBEG, MATB, MATR, SIG_6, SIG_7);
/*vex-vision-config:end*/