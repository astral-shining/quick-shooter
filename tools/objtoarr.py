import argparse

parser = argparse.ArgumentParser(description="Convert obj to buffer C++")
parser.add_argument("file", metavar="FILE", type=str, help="Path file")

args = parser.parse_args()

f = open(args.file, "r")
f_content = f.read().split("\n")[:-1]

name = "undefined"
verts = ""
faces = ""
for line in f_content:
    cols = line.split(" ")
    if cols[0] == "v":
        x = (', '.join(list(
            map(lambda x: x+"f", 
                map(str, 
                    cols[1:]
                )
            )
        )).replace(" -", "-"))
        if (x[0] != "-"):
            x = " " + x
        x = "\n    " + x
        verts += x + ","
    elif cols[0] == "o":
        name = cols[1]
    elif cols[0] == "f":
        faces += "\n    " + ', '.join(list(map(lambda x: str(int(x.split("/")[0])-1), cols[1:]))) + ","
        #indexes.append()

export_path = "src/models/" + name
f = open(export_path + ".hpp", "w")
f.write("""#pragma once
#include <initializer_list>
#include <cstdint>

extern std::initializer_list<float> {0}_verts;
extern std::initializer_list<uint32_t> {0}_faces;
""".format(name))
f = open(export_path + ".cpp", "w")
f.write("""#include "{0}.hpp"

std::initializer_list<float> {0}_verts {{ {1}
}};

std::initializer_list<uint32_t> {0}_faces {{ {2}
}};
""".format(name, verts, faces))
f.close()
