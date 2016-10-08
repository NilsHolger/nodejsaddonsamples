{
    "targets": [
        {
            "target_name" : "addon",
            "sources" : ["addon7.cpp", "myobject.cpp"],
            "include_dirs" : ["<!(node -e \"require('nan')\")"]
        }
    ]
}