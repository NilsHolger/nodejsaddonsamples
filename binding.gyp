{
    "targets": [
        {
            "target_name" : "addon",
            "sources" : ["addon6.cpp", "myobject.cpp"],
            "include_dirs" : ["<!(node -e \"require('nan')\")"]
        }
    ]
}