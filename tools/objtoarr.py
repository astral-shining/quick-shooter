import argparse
import os

parser = argparse.ArgumentParser(description="Convert obj to buffer C++")
parser.add_argument("file", metavar="FILE", type=str, help="Path file")

args = parser.parse_args()

f = open(args.file, "r")
f_content = f.read().split("\n")[:-1]

name = os.path.basename(args.file).split(".")[0]
data = {
}
result = []

for line in f_content:
    cols = line.split(" ")
    #if cols[0] == "o":
    #    current_model = cols[1]
    #    models[current_model] = []
    if cols[0] == "f":
        f = [i.split("/") for i in cols[1:]]
        result.append([[data[list(data.keys())[j]][int(i[j])-1] for j in range(len(data.keys()))] for i in f])
    elif cols[0] in ["v", "vt", "vn"]:
        if not cols[0] in data:
            data[cols[0]] = []
        data[cols[0]].append(list(map(lambda x: str(float(x))+"f", cols[1:])))

hpp = """#pragma once
#include "model.hpp"

"""
cpp = "#include \"{}.hpp\"\n".format(name)

hpp += "extern Model " + name + "_model;\n"
cpp += "Model " + name + "_model {\n"
c = 0
for face in result:
    cpp += "{\n"
    for vert in face:
        cpp += "    glm::vec3{" + "},    {".join([", ".join(i) for i in vert]) + "},\n"
        c += 1
    cpp += "},\n"
cpp += "};\n"


export_path = "src/models/" + name
f = open(export_path + ".hpp", "w")
f.write(hpp)
f.close()
f = open(export_path + ".cpp", "w")
f.write(cpp)
f.close()

