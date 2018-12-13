import os, time

# TODO: Cull files that don't end in .c or .h

if __name__ == "__main__":
    # get path to script file
    pp = os.path.dirname (os.path.realpath (__file__))

    # get files in script folder
    files = os.listdir (pp)
    # convert to file full paths
    files = [os.path.join (pp, f) for f in files]
    # remove items that arent files
    files = [f for f in files if os.path.isfile (f)]

    # get mod times of files
    times = {}
    for f in files:
        times[f] = os.stat (f).st_mtime

    quit = False
    while not quit:
        for f in files:
            # compare file times
            if os.stat (f).st_mtime != times[f]:
                quit = True
                break
        time.sleep (0.3)
