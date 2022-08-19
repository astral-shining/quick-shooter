import argparse
import os

parser = argparse.ArgumentParser(description="Convert obj to buffer C++")
parser.add_argument("file", metavar="FILE", type=str, help="Path file")

args = parser.parse_args()

f = open(args.file, "r")
f_content = f.read().split("\n")[:-1]

name = os.path.splitext(args.file)[0]
n = ["v", "vt", "vn"]
m = {}
current_m = ""
for line in f_content:
    cols = line.split(" ")
    if cols[0] == "o":
        current_m = cols[1]
        m[current_m] = {
            "data": []
        }
        for i in n:
            m[current_m][i] = []

    elif cols[0] == "f":
        f = [i.split("/") for i in cols[1:]]
        m[current_m]["data"].append([[m[current_m][n[j]][int(i[j])-1] for j in range(len(n))] for i in f])
        #[m[current_m][n[i]][int()] for i in range(len(n))])
        #m[current_m]["data"].append()
    elif cols[0] in n:
        #m[current_m][cols[1]].append(cols[1:])
        m[current_m][cols[0]].append(list(map(lambda x: x+"f", cols[1:])))

#print(m)

hpp = """#pragma once
#include "model.hpp"

"""
cpp = "#include \"{}.hpp\"\n".format(name)

for k,v in m.items():
    hpp += "extern Model " + k + "_model;\n"
    cpp += "Model " + k + "_model {{\n"
    c = 0
    for face in v["data"]:
        for vert in face:
            cpp += "    " + ",    ".join([", ".join(i) for i in vert]) + ",\n"
            c += 1
        cpp += "\n"
    cpp += "},\n\n"
    cpp += "    {}\n}};".format(c)


export_path = "src/models/" + name
f = open(export_path + ".hpp", "w")
f.write(hpp)
f.close()
f = open(export_path + ".cpp", "w")
f.write(cpp)
f.close()

