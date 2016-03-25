
def read_keypoints(index, fname = "./COFW_Dataset/keypoints.txt"):

    with open(fname) as rf:
        lines = rf.readlines()

    data = lines[index].strip().split("\t")
    x, y = map(float, data[:29]), map(float, data[29:])
    return x, y