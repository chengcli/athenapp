# Regression test for self-gravity based on linear Jeans instability
# MG gravity + no MPI
# Runs a linear convergence test checks L1 errors (which
# are computed by the executable automatically and stored in the temporary file
# jeans-errors.dat)
# Roughly 15 second test

# Modules
import numpy as np
import scripts.utils.athena as athena


# Prepare Athena++
def prepare(**kwargs):
    athena.configure(prob='jeans',
                     grav='mg',
                     **kwargs)
    athena.make()


# Run Athena++
def run(**kwargs):
    # njeans = 1.5
    # period = 0.3
    # 1/omega = 0.046
    # amp 1e-6
    def arg_res(res):
        arguments = [
          'mesh/nx1=64', 'mesh/nx2=32', 'mesh/nx3=32',
          'meshblock/nx1=16',
          'meshblock/nx2=16',
          'meshblock/nx3=16',
          'problem/njeans=1.5',
          'output2/dt=-1', 'time/tlim=0.04', 'problem/compute_error=true',
          'time/ncycle_out=10']
        arguments[0] = 'mesh/nx1='+str(2*res)
        arguments[1] = 'mesh/nx2='+str(res)
        arguments[2] = 'mesh/nx3='+str(res)
        return arguments
    # 16 might not be good enough
    athena.run('hydro/athinput.jeans_3d', arg_res(32))
    athena.run('hydro/athinput.jeans_3d', arg_res(64))
    # 128 might be too expensive
    # athena.run('hydro/athinput.jeans_3d', arg_res(128))


# Analyze outputs
def analyze():
    # read data from error file
    filename = 'bin/jeans-errors.dat'
    data = np.loadtxt(filename)
    print(data)
    result = True
    # error
    for i in range(len(data)):
        if data[i][4] > 1.e-7:
            print("FFT Gravity Linear Jeans instability error is too large:", 32*2**i)
            result = False
    # compute overall convergence slope
    gslope = np.log(data[len(data)-1][4]/data[0][4])/np.log(4.0)
    # convergence to 2nd order, doubling resolution should decrease error by 4.0
    for i in range(len(data)-1):
        if data[i+1][4] > (1.5*data[i][4]/(4.0)):
            slope = np.log(data[i+1][4]/data[i][4])/np.log(2.0)
            print("Linear Jeans instability error is not converging at 2nd order")
            print("Order estimate:", slope, gslope)
            result = False
        elif data[i+1][4] > (1.1*data[i][4]/(4.0)):
            print("WARNING: Linear Jeans instability error is not converging at "
                  "2nd order within 1.1")

    return result
