{
    "targets": [
        {
            "target_name" : "addon",
            "sources" : ["addon3.cpp"],
            "include_dirs" : ["<!(node -e \"require('nan')\")"]
        }
    ]
}