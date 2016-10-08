{
    "targets": [
        {
            "target_name" : "addon",
            "sources" : ["addon5.cpp"],
            "include_dirs" : ["<!(node -e \"require('nan')\")"]
        }
    ]
}