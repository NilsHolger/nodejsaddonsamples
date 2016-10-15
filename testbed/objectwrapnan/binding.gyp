{
    "targets" : 
    [
    {
        "target_name" : "addon",
        "sources" : ["polynomial.cpp"],
        "cflags": ["-Wall", "-std=c++11"],
        "include_dirs" : ["<!(node -e \"require('nan')\")"]
    }
    ]
}