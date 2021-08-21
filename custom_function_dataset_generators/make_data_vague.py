
import csv
import re
import math
import numpy as np

def custom_func(ln_x, ln_q):
    x_val = (math.exp(1.5/( ( 0.1 * ((ln_x + 7)**2) ) + 1) )/(math.log(math.exp(ln_q) + 0.007) + 5) + math.exp(-1*(ln_x+12)/5) + 1)*((math.exp(0.5*ln_q))) + 5
    return x_val


employee_file = open('./vague_analysis/my_info.csv', mode='w')
employee_writer = csv.writer(employee_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)


employee_file_x = open('./vague_analysis/x.csv', mode='w')
employee_writer_x = csv.writer(employee_file_x, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

employee_file_q = open('./vague_analysis/q.csv', mode='w')
employee_writer_q = csv.writer(employee_file_q, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

employee_file_data = open('./vague_analysis/data.dat', mode='w')
employee_writer_data = csv.writer(employee_file_data, delimiter=' ', quotechar='"', quoting=csv.QUOTE_NONE)

x = []
# x = [1.000000e-08,1.214290e-08,1.474520e-08,1.790520e-08,2.174240e-08,2.640200e-08,3.206010e-08,3.893070e-08,4.727370e-08,5.740470e-08,6.970670e-08,8.464500e-08,1.027840e-07,1.248110e-07,1.515580e-07,1.840360e-07,2.234750e-07,2.713640e-07,3.295150e-07,4.001270e-07,4.858690e-07,5.899830e-07,7.164050e-07,8.699160e-07,1.056320e-06,1.282650e-06,1.557480e-06,1.892460e-06,2.297910e-06,2.790210e-06,3.387960e-06,4.113730e-06,4.995000e-06,6.065420e-06,7.365210e-06,8.943510e-06,1.086000e-05,1.318710e-05,1.601280e-05,1.944390e-05,2.361000e-05,2.866850e-05,3.481040e-05,4.226760e-05,5.132150e-05,6.231370e-05,7.565850e-05,9.185860e-05,1.115240e-04,1.353930e-04,1.643640e-04,1.995060e-04,2.421600e-04,2.939080e-04,3.566770e-04,4.327950e-04,5.250750e-04,6.369110e-04,7.726750e-04,9.367690e-04,1.135340e-03,1.375450e-03,1.665550e-03,2.015680e-03,2.437770e-03,2.945870e-03,3.556390e-03,4.288450e-03,5.164110e-03,6.208550e-03,7.450380e-03,8.921250e-03,1.065330e-02,1.268820e-02,1.506290e-02,1.781700e-02,2.098570e-02,2.461440e-02,2.873900e-02,3.338270e-02,3.857250e-02,4.433070e-02,5.066750e-02,5.758780e-02,6.509020e-02,7.316730e-02,8.180630e-02,9.099030e-02,1.006990e-01,1.109100e-01,1.215990e-01,1.327420e-01,1.443130e-01,1.562890e-01,1.686470e-01,1.813520e-01,1.944020e-01,2.077620e-01,2.214160e-01,2.353440e-01,2.495390e-01,2.639710e-01,2.786310e-01,2.935040e-01,3.085780e-01,3.238410e-01,3.392820e-01,3.548990e-01,3.706620e-01,3.865750e-01,4.026290e-01,4.188160e-01,4.351300e-01,4.515630e-01,4.681100e-01,4.847630e-01,5.015190e-01,5.183720e-01,5.353160e-01,5.523490e-01,5.694650e-01,5.866600e-01,6.039320e-01,6.212820e-01,6.386840e-01,6.561650e-01,6.737080e-01,6.913110e-01,7.089700e-01,7.266830e-01,7.444490e-01,7.622630e-01,7.801240e-01,7.980270e-01,8.159700e-01,8.339490e-01,8.519580e-01,8.699910e-01,8.880430e-01,9.060860e-01,9.240980e-01,9.420120e-01,9.596630e-01,9.764990e-01,9.901900e-01,9.965610e-01,9.985400e-01,9.993360e-01,9.997490e-01,1.000000e+00]
ln_x = []
q = []
# q = [1.300000e+00,1.501480e+00,1.754940e+00,2.077770e+00,2.494520e+00,3.040400e+00,3.766790e+00,4.750000e+00,6.133070e+00,8.090760e+00,1.092470e+01,1.512840e+01,2.153060e+01,3.156460e+01,4.778650e+01,7.491100e+01,1.219530e+02,2.068370e+02,3.667270e+02,6.822740e+02,1.337310e+03,2.773760e+03,6.116880e+03,1.441630e+04,3.651470e+04,1.000000e+05]
ln_q = []

i = 0.3
while(i<10):
    ln_q.append(i)
    q.append(math.exp(i))
    i+=0.5

i = -18
while(i<0):
    ln_x.append(i)
    x.append(math.exp(i))
    i+=0.2
# ln_q = np.log(q)
# ln_x = np.log(x)


print("length of x is ", len(x))
print("length of q is ", len(q))
# when interpolating on values
# employee_writer_q.writerow(q)
# employee_writer_x.writerow(x)

# when interpolating on log values
employee_writer_q.writerow(ln_q)
employee_writer_x.writerow(ln_x)

xf = []

# employee_writer.writerow(["xf","lnx","lnq"])
for val_x in ln_x:
    for val_q in ln_q:
        employee_writer.writerow([custom_func(val_x,val_q),"{:.2f}".format(val_x),"{:.2f}".format(val_q)])
        # employee_writer.writerow(["{:.2f}".format(custom_func(val_x,val_q))])

print("writing in data")

str1 = "PdfType: central"

employee_writer_data.writerow(["PdfType:","central"])
employee_writer_data.writerow(["Format:","lhagrid1"])
employee_writer_data.writerow(["---"])
employee_writer_data.writerow(x)
employee_writer_data.writerow(q)
employee_writer_data.writerow([-5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 21])

for val_x in ln_x:
    for val_q in ln_q:
        # print("writing")
        employee_writer_data.writerow([custom_func(val_x,val_q) for i in range(0,11)])
employee_writer_data.writerow(["---"])

print(ln_x)

print(ln_q)