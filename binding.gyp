{
    "targets": [
        {
            "target_name" : "addon",
            "sources" : ["addon4.cpp"],
            "include_dirs" : ["<!(node -e \"require('nan')\")"]
        }
    ]
}